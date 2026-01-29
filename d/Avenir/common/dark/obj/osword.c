/*
 * Random sword for the L5 Ogres
 *   Cirion, May 1996
 *   Taken from the random weapons by Boriska
 */
#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"
#include <macros.h>

inherit "/d/Avenir/inherit/weapon";

static string *adjs = ({ "short", "heavy", "double-bladed", "sharp" });
static string *materials = ({"copper", "bronze", "iron", "steel", "alloy", "adamantine" });
public int adj, mat;

varargs void configure_me(int num);

void create_weapon()
{
  set_name("gladius");
  set_pname("gladiuses");
    add_adj ("ogre");
    add_pname("weapons");
  add_name(({ "sword", "shortsword", "weapon" }));

  adj = random(sizeof(adjs));
  mat = random(3);
  configure_me();
}

varargs void configure_me(int num)
{
  int   hit = 21,   // per weapon_guide explanation of a gladius
        pen = 16;

  if(num)
   mat = MIN(num, sizeof(materials) - 1);

  add_adj(adjs[adj]);
  add_adj(materials[mat]);
  set_short(adjs[adj] + " " + materials[mat] + " gladius");
  set_pshort(adjs[adj] + " " + materials[mat] + " gladiuses");

  set_long("It is a double-bladed shortsword made from " + materials[mat] + ", with "
     +"a very sharp any nasty blade. It is designed to be used for impaling "
     +"an enemy, rather than slashing with.\n");

  hit += (mat - 3);
  pen += (mat - 3);
  set_default_weapon(hit, pen, W_SWORD, W_IMPALE, W_ANYH);

  add_prop(OBJ_I_WEIGHT, 2000 + 1000 * mat );
  add_prop(OBJ_I_VALUE,  400 + (100 * mat));
  add_prop(OBJ_I_VOLUME, 5000 ); 
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
