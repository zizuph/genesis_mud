/*
 * Drowning Object - Well in Kalad
 * /d/Kalad/common/wild/pass/obj/water_death
 *
 * Created by Antharanos
 *
 * Modified by Mirandus to check for MAGIC_I_BREATH_WATER so that
 * undeads and folks with that prop won't still die.
*/

inherit "/std/object";
inherit "/lib/commands";
#include <stdproperties.h>
#include <ss_types.h> 
#include <macros.h>
#include <filter_funs.h>
#include <options.h>
#include "/d/Kalad/defs.h"

create_object()
{
   set_name("water_death");
   set_long("A watery death.\n");
   add_prop(OBJ_I_INVIS,100);
   set_no_show();
   set_alarm(60.0,0.0,"drowning");
}
drowning()
{
  int magic = TP->query_prop(MAGIC_I_BREATH_WATER);
	if (magic)
	{
    TP->catch_msg("You are breathing water just fine\n");
    return 1;
  }
    
   TP->catch_msg("You can hold your breath no longer!\n");
   TP->catch_msg("Water rushes into your lungs, causing an excruciating "+
      "amount of pain!!\n");
   TP->heal_hp(-1000);
   if(TP->query_hp() <= 0)
      TP->do_die(TO);
   set_alarm(30.0,0.0,"drowned");
   return 1;
}
drowned()
{
   TP->catch_msg("Water rushes once again into your lungs, burning you "+
      "like fire!!!\n");
   TP->heal_hp(-2000);
   if(TP->query_hp() <= 0)
      TP->do_die(TO);
   set_alarm(15.0,0.0,"dying");
   return 1;
}
dying()
{
   TP->catch_msg("Your lungs continue to fill with water, soon you will die!\n");
   TP->heal_hp(-4000);
   if(TP->query_hp() <= 0)
      TP->do_die(TO);
   set_alarm(5.0,0.0,"dead");
   return 1;
}
dead()
{
   TP->catch_msg("Water has completely filled your lungs!!\n");
   TP->do_die(TO);
}
