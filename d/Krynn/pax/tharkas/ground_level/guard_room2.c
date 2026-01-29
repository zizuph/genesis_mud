/*
   Pax Tharkas, Ground level, Guard room in west tower.

   guard_room2.c
   -------------

   Coded ........: 95/03/02
   By ...........: Jeremiah

   Latest update : 95/07/28
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

#define EROOM \
   ({   \
      GROUND_LEVEL + "guard_room1", \
   })

object guard1, guard2, guard3;

void
reset_pax_room()
{
   if(objectp(guard1) || objectp(guard2) || objectp(guard3))
      return;

   guard1 = clone_object(PMONSTER + "sivak");
   guard2 = clone_object(PMONSTER + "bozak");
   guard3 = clone_object(PMONSTER + "bozak");

   guard2->set_leader(guard1);
   guard3->set_leader(guard2);

   guard1->team_join(guard2);
   guard1->team_join(guard3);

   guard1->add_descr("lying on the bed");
   guard2->add_descr("polishing his sword");

   guard1->move_living("arrives", TO, 0);
   guard2->move_living("arrives", TO, 0);
   guard3->move_living("arrives", TO, 0);
}


void
create_pax_room()
{
   reset_pax_room();

   set_short("West end of guard room");
   set_long("@@room_descr");
	
   INSIDE;

   add_item(({"stools", "camp stools"}), "These stools are constructed of " +
            "a cheap wood, and have no value other than to rest one's foot " +
            "upon.\n");

   add_item(({"bed", "beds"}), "These are plain beds, with worn down " +
            "and dirty mattresses.\n");

   add_item(({"table", "small table"}), "This is just a small round " +
            "the same size of a large cart wheel. There's nothing on it.\n");

   add_item(({"tapestry", "tapestries"}), "These are very old tapestries " +
            "You can hardly see the motives anymore, but they look like " +
            "battlescenes from some battle fought long ago.\n");

   add_exit(GROUND_LEVEL + "guard_room1", "east", 0);
   add_exit(GROUND_LEVEL + "supply_room2", "north", 0);
}


string
eroom_descr()
{
   string *roomfiles;
   object *inv, *live, room;
   int i;

   roomfiles = EROOM;
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
        return ("In the other end of the guard room you see " +
                 COMPOSITE_LIVE(live) + ". ");
   }
   return ("The other end of the guard room is empty. ");
}


string
room_descr()
{
   return "You enter the west end of very large room, a guard room by " +
          "the look of it. Beds line the walls in this end. A small " +
          "table, and a few camp stools stands here. very old and " +
          "dusty looking tapestries decorate the walls here. " +
          eroom_descr() + "\n";
} 
