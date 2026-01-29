/* this weapon cloned by /d/Emerald/caverns/npc/pguard2.c
*/

inherit "/std/weapon";

#include "/sys/stdproperties.h"
#include "/sys/wa_types.h"
#include "/sys/formulas.h"
#include "/sys/macros.h"


void
create_weapon()
{
   
   if(!IS_CLONE)
      return;
   
   set_name("axe");
   set_short("long-handled gleaming axe");
   set_adj("long-handled");
   set_adj("gleaming");
   add_name("ax");
   set_long(break_string(
         "The long teak handle supports a shiny steel head.\n",74));
   set_adj("rusty");
   
   set_hit(21);
   set_pen(19);
   set_pen(13);
   
   set_wt(W_AXE);
   set_dt(W_SLASH);
   set_dt(W_BLUDGEON);
   
   set_hands(W_ANYH);
   
   
   add_prop(OBJ_I_VOLUME,1000);
   add_prop(OBJ_I_WEIGHT,2000);
   add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(9,13) - 30);
}

