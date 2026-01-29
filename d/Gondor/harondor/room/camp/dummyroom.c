/*
 *	/d/Gondor/harondor/room/road04.c
 *  This file is a base file for the harad road

 *
 */
#pragma strict_types

#include "/d/Gondor/defs.h"
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <tasks.h>

//#include  "local.h"

inherit "/d/Gondor/common/lib/area_room.c";
inherit "/d/Gondor/harondor/base_road.c";

int alarm_id, the_measure = 18 - (TP->query_prop(CONT_I_HEIGHT)*5/90);

int measure_it(string str);
void stepit(object who, int my_step);


public void
create_area_room()
{
    FIXEUID;
    set_areatype(0);
    set_areadesc("arid land");
    set_area("barren");
    set_areaname("southern Gondor");
    set_land("Harondor");
    set_extraline("Thin grasses grow alongside the road. They are dried " +
        "and brown, and grow in clumps in the sand.");

    add_desert();
    add_road();
    add_ephel_duath("northeast"); /* where they are in relation to the road */
    
    add_exit(HAR_RM_DIR + "road04s", "north");
    add_exit(HAR_RM_DIR + "road06s", "south");
    
}

public void
init()
{
   ::init();

   add_action("measure_it", "measure", 0);
}

int
measure_it(string str)
{
   int alarm_id;   

   set_this_player(this_interactive());

   notify_fail("What?\n");

   if(!str)
      return 0;

   notify_fail("Measure what? The road? Or the width of the road?\n");

   if(str == "width" || str == "road")
   {
      notify_fail("Without the daylight to see all the fine details it is impossible " +
         "get an accurate measure!\n");

      if(this_object()->query_prop(ROOM_I_LIGHT) < 1)
         return 0;

      // Add support if player is already measuring

      write("Stepping to the side of the road you prepare to begin measuring the width of the road.\n");
      say(QCTNAME(TP) +
	          " steps to one side of the road looking at the ground as if taking it all in, " +
	          "scrutinizing it closely.\n", TP);
	
      alarm_id = set_alarm(10.0, 0.0, &stepit(TP, 0));
       	
      return 1;
   }
   
   return 0;
}

void
stepit(object who, int my_step)
{
   if(my_step == 0)
   {
      who->catch_msg("Watching the road, you take a first step across as you begin to measure it.\n");
      say(QCTNAME(TP) +
          " takes a step slowly across the road and then another as if measuring.\n", who);
   }
   else
   {
      who->catch_msg("You take one more step and keep count.\n");
      say(QCTNAME(TP) +
          " takes a step slowly across the road and then another as if measuring.\n", who);
   }

   if(my_step < 3)
      alarm_id = set_alarm(8.0, 0.0, &stepit(who, ++my_step));
   else
   {
      who->catch_msg("You have reached the other side of the road and your measuring is complete. " +
                "You estimate the width to " + the_measure + " paces.\n");
      say(QCTNAME(TP) +
          " steps to the side of the road completing a long stride from across.\n", who);

      who->add_prop("_have_measured_road_");
   }

   

}

