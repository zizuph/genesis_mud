/*
 * Random mace for the L5 Ogres
 *   Cirion, May 1996
 *   Taken from the random weapons by Boriska
 */
#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"
#include <macros.h>

inherit "/d/Avenir/inherit/weapon";

static string *adjs = ({ "heavy", "large", "wide-headed", "winged", "long-handled" });
static string *materials = ({"copper", "bronze", "iron", "steel", "alloy", "adamantine" });
public int adj, mat;

varargs void configure_me(int num);

void create_weapon()
{
  set_name("mace");
  add_name("club");
    add_adj ("ogre");
  adj = random(sizeof(adjs));
  mat = random(3);
  configure_me();
}

varargs void configure_me(int num)
{
  int   hit = 29,   // per weapon_guide explanation of a mace
        pen = 20;

  if(num)
   mat = MIN(num, sizeof(materials) - 1);

  add_adj(adjs[adj]);
  add_adj(materials[mat]);
  set_short(adjs[adj] + " " + materials[mat] + " mace");
  set_pshort(adjs[adj] + " " + materials[mat] + " maces");

  set_long("It is a long-handled club with a thick wooden handle, ending "
    +"in a winged head made from " + materials[mat] + ".\n");

  hit += (mat - 3);
  pen += (mat - 3);
  set_default_weapon(hit, pen, W_CLUB, W_BLUDGEON, W_ANYH);

  add_prop(OBJ_I_WEIGHT, 3000 + 3000 * mat );
  add_prop(OBJ_I_VALUE,  400 + (100 * mat));
  add_prop(OBJ_I_VOLUME, 9000 ); 
}

string
query_recover()
{
  return MASTER + ":" + query_wep_recover() + "OGRE#" + adj + "#" + mat;
}

void init_recover(string arg)
{
  string foo;
  
  sscanf (arg, "%sOGRE#%d#%d", foo, adj, mat);
  init_wep_recover(arg);
  configure_me();  
}
