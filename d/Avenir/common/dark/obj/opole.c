/*
 * Random polearm for the L5 Ogres
 *   Cirion, May 1996
 *   Taken from the random weapons by Boriska
 */
#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"
#include <macros.h>

inherit "/d/Avenir/inherit/weapon";

static string *adjs = ({ "long", "heavy", "concave", "hooked", "blooded" });
static string *materials = ({"copper", "bronze", "iron", "steel", "alloy", "adamantine" });
public int adj, mat;

varargs void configure_me(int num);

void create_weapon()
{
  set_name("gisarme");
  add_name("polearm");
  add_item("hook", "The hook on the gisarme curves back from the spear-head, "
          +"designed to snag hold of the enemies armour.\n");
  add_adj ("ogre");
  adj = random(sizeof(adjs));
  mat = random(3);
  configure_me();
}

varargs void configure_me(int num)
{
  int   hit = 27,   // per weapon_guide explanation of a gisarme
        pen = 32;

  if(num)
   mat = MIN(num, sizeof(materials) - 1);

  add_adj(adjs[adj]);
  add_adj(materials[mat]);
  set_short(adjs[adj] + " " + materials[mat] + " gisarme");
  set_pshort(adjs[adj] + " " + materials[mat] + " gisarmes");

  set_long("It is a long " + materials[mat] + " polearm with a concave "
    +"blade that is smeared with dried blood. The shaft terminates at "
    +"a spear head, and opposite it is a nasty, curved hook.\n");

  hit += (mat - 3);
  pen += (mat - 3);
  set_default_weapon(hit, pen, W_POLEARM, W_IMPALE | W_SLASH, W_BOTH);

  add_prop(OBJ_I_WEIGHT, 3000 + 2000 * mat );
  add_prop(OBJ_I_VALUE,  400 + (200 * mat));
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
