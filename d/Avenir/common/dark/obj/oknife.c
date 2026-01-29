/*
 * Random knife for the L5 Ogres
 *   Cirion, May 1996
 *   Taken from the random weapons by Boriska
 */
#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"
#include <macros.h>

inherit "/d/Avenir/inherit/weapon";

static string *adjs = ({ "sharp", "nasty", "big", "long-bladed" });
static string *materials = ({"copper", "bronze", "iron", "steel", "alloy", "adamantine" });
public int adj, mat;

varargs void configure_me(int num);

void create_weapon()
{
  set_name("knife");
    add_adj ("ogre");
  set_pname(({ "knives", "weapons" }));
  adj = random(sizeof(adjs));
  mat = random(3);
  configure_me();
}

varargs void configure_me(int num)
{
  int   hit = 14,   // per weapon_guide explanation of a dirk
        pen = 13;

  if(num)
   mat = MIN(num, sizeof(materials) - 1);

  add_adj(adjs[adj]);
  add_adj(materials[mat]);
  set_short(adjs[adj] + " " + materials[mat] + " knife");
  set_pshort(adjs[adj] + " " + materials[mat] + " knives");

  set_long("It is a long and nasty knife made from " + materials[mat] + ". It has "
     +"a very large grip made from wood banded with metal, and has a wide "
     +"handguard.\n");

  hit += (mat - 3);
  pen += (mat - 3);
  set_default_weapon(hit, pen, W_KNIFE, W_IMPALE | W_SLASH, W_ANYH);

  add_prop(OBJ_I_WEIGHT, 3000 + 1000 * mat );
  add_prop(OBJ_I_VALUE,  100 + (100 * mat));
  add_prop(OBJ_I_VOLUME, 3000 ); 
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
