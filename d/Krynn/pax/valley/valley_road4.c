/*
   Pax Tharkas, Valley.....

   valley_road5.c
   --------------

   Coded ........: 95/04/09
   By ...........: Jeremiah

   Latest update : 95/05/15
   By ...........: Jeremiah

*/


#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/pax/local.h"
#include <filter_funs.h>                 /* filter functions */
#include <composite.h>

inherit PAXOUTROOM;

object enter_room = VALLEY + "forest1";

void
create_pax_room()
{
   set_short("Road in valley");
   set_long("You are standing on a road in a narrow valley. The valley, " +
            "and the road, goes northeast to southwest here. The distance " +
            "between the mountains bordering this valley gets smaller " +
            "towards the southwest and larger to the northeast. To both " +
            "sides of the road the valley floor gently slopes upwards " +
            "towards the mountain ranges bounding the valley. South the " +
            "view of the lower slopes of the mountains is obstructed by " +
            "a small forest, almost reaching all the way down to the " +
            "road.\n");

   OUTSIDE;

   add_item("road", "A simple dusty road, running through a small " +
            "valley.\n");

   add_item("valley", "You are standing in it. A small valley cutting " +
            "into the mountains.\n");

   add_item(({"forest", "Forest"}), "This is a light forest covering the " +
            "slopes of the southern mountains. You wonder what might be " +
            "hidden in that forest. Maybe it's possible, somehow, to enter " +
            "the light forest and investigate it.\n");
	
   add_item("slopes", "The lower slopes of the mountains bordering " +
            "the southside of the valley are covered by a small forest. " +
            "The forest is almost reaching all the way down to the road.\n");

   add_item(({"mountain", "mountains"}), "Mountains rising high into the " +
            "sky, bordering this valley, north and south. The slopes of " +
            "the southern mountain reaches are covered with a light " +
            "forest, obscuring the view to these.\n");

   add_exit(VALLEY + "valley_road5", "northeast", 0, 2);
   add_exit(VALLEY + "valley_road3", "southwest", 0, 2);

   add_cmd_parse("[the] 'forest' / 'Forest'", "enter", "@@enter_forest");
}

int
enter_forest()
{
      set_dircmd("forest");
      write("You enter the light forest south of the road.\n");
      say(QCTNAME(TP) + " enters the forest south of the road.\n");
      enter_room->someone_arrives(TP);
      TP->move_living("M", VALLEY + "forest1", 0);
      return 1;
}

