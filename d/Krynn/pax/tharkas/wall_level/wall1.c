/*
   Pax Tharkas, Wall level, On the parapets of the great Tharkadan wall 
                entrance to east tower.

   wall1.c
   -------

   Coded ........: 95/03/06
   By ...........: Jeremiah

   Latest update : 95/03/11
   By ...........: Jeremiah

*/


#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/pax/local.h"
#include <filter_funs.h>                 /* filter functions */
#include <composite.h>

inherit PAXINROOM;

#define WWALL \
   ({   \
      WALL_LEVEL + "wall2", \
      WALL_LEVEL + "wall3", \
   })

object guard1, guard2, guard3;


reset_pax_room()
{
   if(!P("sivak",TO) && !P("bozak",TO))
   {
      guard1 = clone_object(PMONSTER + "sivak");
      guard2 = clone_object(PMONSTER + "sivak");
      guard3 = clone_object(PMONSTER + "bozak");

      guard2->set_leader(guard1);
      guard3->set_leader(guard1);
      guard1->team_join(guard2);
      guard1->team_join(guard3);

      guard1->set_aggressive(1);
      guard2->set_aggressive(1);
      guard3->set_aggressive(1);

      guard1->move(TO);
      guard2->move(TO);
      guard3->move(TO);
   }
}


void
create_pax_room()
{
   reset_pax_room();

   set_short("Entrance to east tower");
   set_long("@@room_descr");
	
   INSIDE;

   add_exit(WALL_LEVEL + "wall2", "west", 0);
   add_exit(WALL_LEVEL + "stair_to_etow1", "east", 0);
}


string
wwall_descr()
{
   string *roomfiles;
   object *inv, *live, room;
   int i;

   roomfiles = WWALL;
   inv = ({});

   for (i = 0; i < sizeof(roomfiles); i++)
   {
      if ((room = find_object(roomfiles[i])) != 0)
         inv += all_inventory(room);
   }

   if (inv && sizeof(inv) > 0)
   {
     live = FILTER_LIVE(inv);
     if (sizeof(live) > 0)
        return ("Looking west you can see " + COMPOSITE_LIVE(live) + ". ");
   }
   return ("The west part of the wall looks empty. ");
}


string
room_descr()
{
   return "You are standing on the battlements of the great Tharkadan " +
          "wall. The wall links the two towers of Pax Tharkas. The wall " +
          "stretches west towards the west tower. " + wwall_descr() + 
          "The entrance to the east tower is here. Looking north you see " +
          "the narrow valley leading up to the fortress. South you see " +
          "the court yard, lying in the shadows of the Kharolis " +
          "mountains rising into the sky.\n"; 
}
