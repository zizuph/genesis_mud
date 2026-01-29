/*
   Pax Tharkas, Wall level, chainshaft, leading down to the chainroom, 
   in Sla Mori. Upwards to the chainchamber.

   chainshaft3.c
   -------------

   Coded ........: 95/02/16
   By ...........: Jeremiah

   Latest update : 95/03/08
   By ...........: Jeremiah

*/


#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/pax/local.h"

inherit PAXINROOM;

object up_room = WALL_LEVEL + "chainshaft4";
object down_room = WALL_LEVEL + "chainshaft2";


create_pax_room()
{
   set_short("Chain shaft");
   set_long("You are hanging in a narrow shaft, clinging to a large chain " +
            "link. The shaft continues up, and down, into darkness. You " +
            "notice that the shaft slants downward to the east.\n");

   INSIDE;
   add_prop(ROOM_I_LIGHT, 0);

   add_item("shaft", "The walls of the shaft are solid. You realize, " +
            "that you are in a narrow tunnel somehow drilled into the " +
            "mountain.\n");

   add_item("chain", "A huge chain made of steel links. each chain " +
            "link as high as a grown human, and thicker than a leg.\n");
}      


void
init()
{
   ::init();
   add_action("climb_chain", "climb");
}


int
climb_chain(string dir)
{
   if (dir == "down" || dir == "down chain" || dir == "down the chain")
   {
      write("You climb carefully down the chain.\n");
      say(QCTNAME(TP) + " climbs down the chain.\n");
      down_room->someone_arrrives(TP,0);
      TP->move_living("M", WALL_LEVEL + "chainshaft2", 0, 0);
      return 1;
   }

   if (dir == "up" || dir == "up chain" || dir == "up the chain")
   {
      write("You climb carefully up the chain.\n");
      say(QCTNAME(TP) + " climbs up the chain.\n");
      up_room->someone_arrives(TP,1);
      TP->move_living("M", WALL_LEVEL + "chainshaft4", 0, 0);
      return 1;
   }

   NF("Climb where?.\n");
   return 0;
}


void
someone_arrives(object who, int from)
{
   string *from_where = ({"down", "up"});

   tell_room(TO, QCTNAME(who) + " arrives, climbing " + from_where[from] +
             " the chain.\n");
}
