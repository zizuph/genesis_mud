/* This armour is cloned by /d/EMerald/caverns/npc/pguard.c
*/
inherit "/std/armour";

#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>

void
create_armour()
{
   set_name("jerkin");
   set_short("studded leather jerkin");
   set_adj("studded");
   add_adj("leather");
   set_long("Looks like something a goblin would wear.\n");
   set_adj("leather");
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
