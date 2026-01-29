/*
   Pax Tharkas, wall level, Northeast part of barracks

   ne_barrack.c
   ------------

   Coded ........: 95/03/03
   By ...........: Jeremiah

   Latest update : 95/05/06
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

#define BARRACK \
   ({   \
      WALL_LEVEL + "nw_barrack", \
      WALL_LEVEL + "se_barrack", \
      WALL_LEVEL + "sw_barrack", \
   })

object guard1, guard2, guard3, guard4;

void
load_barr_room(object room)
{
    room->load_me();
}


void
load_other_rooms()
{
   int i;
   object *roomfiles;

   roomfiles = BARRACK;

    for (i = 0; i < sizeof(roomfiles); i++)
    {
        set_alarm(itof(i*3), 0.0, &load_barr_room(roomfiles[i]));
    }
}


void
reset_pax_room()
{
   if((!P("sivak", TO)) && (!P("kapak",TO)))
   {
      guard1 = clone_object(PMONSTER + "sivak");
      guard2 = clone_object(PMONSTER + "kapak");
      guard3 = clone_object(PMONSTER + "kapak");
      guard4 = clone_object(PMONSTER + "kapak");       

      guard2->set_leader(guard1);
      guard3->set_leader(guard1);
      guard4->set_leader(guard1);

      guard1->team_join(guard2);
      guard1->team_join(guard3);
      guard1->team_join(guard4);

      guard2->add_descr("mending his armour");
      guard3->add_descr("sharpening his sword");

      guard1->move_living("arrives",TO);
      guard2->move_living("arrives",TO);
      guard3->move_living("arrives",TO);
      guard4->move_living("arrives",TO);
   }
}


void
create_pax_room()
{
   load_other_rooms();
   reset_pax_room();

   set_short("Northeast corner of barrack");
   set_long("@@room_descr");
	
   INSIDE;

   add_item(({"bed", "beds"}), "The beds are simple beds made of a wooden " +
            "rack, with a plain mattress. You estimate that there's " +
            "probably more than a hundred beds in here.\n");

   add_item(({"table", "tables"}), "Large wooden tables, each lined with " +
            "a pair of benches. The tables are very scarred by the " +
            "handling of heavy, or sharp, equipment on them. There is " +
            "ample room for about thirty persons around each of the six " +
            "tables in here.\n");



   add_exit(WALL_LEVEL + "nw_barrack", "west", 0);
   add_exit(WALL_LEVEL + "se_barrack", "south", 0);
   add_exit(WALL_LEVEL + "sw_barrack", "southwest", 0);
   add_exit(WALL_LEVEL + "stair_to_wtow1", "up", 0, 1);
   add_exit(GROUND_LEVEL + "stair_to_barr", "down", 0);
}


string
barrack_descr()
{
   string *roomfiles;
   object *inv, *live, room;
   int i;

   roomfiles = BARRACK;
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
        return ("Looking across this big room you see " +
                 COMPOSITE_LIVE(live) + ". ");
   }
   return ("Looking across the room you see that there's nobody here. ");
}


string
room_descr()
{
   return "You are standing in the northeast corner of a very huge room. " +
          "This room is so big, that it probably covers this entire level " +
          "of the tower. In the middle of the room, six large tables have " +
          "been placed. Along each side of each table there is a long " +
          "bench. From the tables, in the middle, and out to the walls of " +
          "the room, beds are arranged in lines, with equal interspace " +
          "between each line of beds, and each bed. " + barrack_descr() + 
          "\n";
}
