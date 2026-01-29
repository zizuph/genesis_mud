/* This weapon is cloned by /d/Emerald/caverns/npc/prisoner2.c
 */
inherit "/std/weapon";

#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>

void
create_weapon()
{
   set_name("shiv");
   set_adj("serpentine");
   set_adj("evil");
   set_short("evil serpentine shiv");
   set_long(break_string("This black obsidian blade writhes "+
         "back and forth from the handle to the tip. If you look "+
         "closely, you can see your reflection being twisted and "+
         "contorted from the evil presence within the blade.\n",76));
   
set_default_weapon(21, 32, W_KNIFE, W_SLASH | W_IMPALE,
      W_ANYH,  0);
   add_prop(OBJ_I_WEIGHT, 1790); 
   add_prop(OBJ_I_VOLUME,  1860);
   add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(27, 32) + random(50) - 10);
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
