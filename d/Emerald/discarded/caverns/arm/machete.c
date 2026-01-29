/* This weapon is cloned by /d/Emerald/caverns/npc/prisoner3.c
*/
inherit "/std/weapon";

#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>

void
create_weapon()
{
   set_name("machete");
   set_adj("curved");
   set_short("curved machete");
   set_long(break_string("This machete looks like a very " +
         "powerful weapon. Its curavture gives it a wicked "+
         "appearance. After long diliberation on what kind of "+
         "weapon this is, you decide it is a short wide-bladed sword "+
         "rather than a big knife.\n",74));
   
   set_default_weapon(40, 35, W_SWORD, W_SLASH | W_IMPALE,
      W_ANYH,  0);
   add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(35,40) + random(200) - 100);
   add_prop(OBJ_I_WEIGHT,1500);
   add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(40, 34) + random(100) - 10);
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
