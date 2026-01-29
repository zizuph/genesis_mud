/* This armour is cloned in /d/Emerald/caverns/npc/pguard2.c
*/
inherit "/std/armour";

#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>

void
create_armour()
{
   set_name("platemail");
   add_name("mail");
   set_adj("dented");
   add_adj("dingy");
   set_short("dingy dented platemail");
   set_long(break_string(
         "Although this platemail is dirty and dented, it "+
         "is still fairly good armour.\n",74));
   set_ac(30);
   set_at(A_BODY);
   set_am(({-1,1,1}));
   add_prop(OBJ_I_WEIGHT, 350); 
   add_prop(OBJ_I_VOLUME,  157); 
   add_prop(OBJ_I_VALUE, 550 - 50 + random(100));
}

string
query_recover()
{
   return MASTER + ":" + query_arm_recover();
}

void
init_recover(string arg)
{
   init_arm_recover(arg);
}
