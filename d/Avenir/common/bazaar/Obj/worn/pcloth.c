//               Torch Peddler's parcel (/bazaar/Obj/pcloth.c) 
// creator(s):   Tepisch  August 1994
// last update:  
// purpose:      cosmetic; left-over when peddler is killer
// note:         
// bug(s):
// to-do:
inherit "/std/armour";
#include "../../bazaar.h"

void
create_armour()
{
  set_name("parcel");
  add_name("cloth");
  add_name("armour");
  set_adj("peddler");
  set_adj("brown");
  set_adj("heavy");
  set_adj("dark");
  SHORT("length of heavy brown cloth");
  LONG("Somehow the peddler made a sack of sorts from this length "+
     "of dark cloth.\n");
  set_default_armour(3, A_ROBE, (({ 0, 0, 0})), 0);
  add_prop(OBJ_I_WEIGHT, 360);   /* 360 gram */
  add_prop(OBJ_I_VOLUME, 250);   /* 0,25 liter */
  add_prop(OBJ_I_VALUE,   25);
}

string query_recover() { return MASTER+":"+query_arm_recover(); }
void init_recover(string arg) { init_arm_recover(arg); }
      
