/* This weapon is cloned by /d/Emerald/caverns/npc/chef.c
*/
inherit "/std/weapon";

#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>

void
create_weapon()
{
   set_name("peeler");
   set_short("potato peeler");
   set_adj(({"sharp","potato"}));
   set_long(break_string(
         "It is like a knife with a sharp point and two blades. "+
         "Unfortunately the blades face each other making "+
         "this a very poor weapon.\n",74));
   set_default_weapon(8, 15, W_KNIFE, W_SLASH | W_IMPALE,
      W_ANYH,  0);
   add_prop(OBJ_I_WEIGHT, 1790); 
   add_prop(OBJ_I_VOLUME,  1860);
   add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(8, 1) +random(20));
}

string
query_recover()
{
   return MASTER + ":" + query_wep_recover();
}

void
init_recover(string arg)
{
   init_wep_recover(arg);
}
