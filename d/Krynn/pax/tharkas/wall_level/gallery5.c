/*
   Pax Tharkas, wall level, Gallery, entrance from ground_level.

   gallery5.c
   -----------

   Coded ........: 95/02/08
   By ...........: Jeremiah

   Latest update : 95/03/01
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

#define NGALL \
   ({   \
      WALL_LEVEL + "gallery1", \
   })


int    hidden_door_found = 0;   /* 0 = Hidden door NOT found */
object other_room = WALL_LEVEL + "chainchamber1";


void
create_pax_room()
{
   set_short("Stair landing in gallery");
   set_long("@@room_descr");
	
   INSIDE;

   add_item(({"painting", "paintings"}), "This painting shows a " +
            "high mountain pass glittering in the light of the sun. " +
            "Snowfields flash among the peaks, and thick forests " +
            "cover the lower slopes. Many streams, swollen by ponds " +
            "and waterfalls, wind into the lowlands.\n");

   add_item(({"wall", "walls", "south wall"}), "@@wall_descr");

   add_search("south wall", 3, "find_door", 1);

   add_exit(WALL_LEVEL + "gallery1", "north", 0);
   add_exit(GROUND_LEVEL + "stair_to_wl2", "down", 0);
}


string
wall_descr()
{
   string ret_str;

   ret_str = "The walls are made of almost equal sized blocks of " +
             "stones. They have been fitted very close together " +
             "giving the walls an appearance as if they are solid.";

   if (TP->query_skill(110) > 40)
   {
      ret_str += " There's something about that south wall.... ";
   }
   ret_str += "\n";
   return ret_str;
}


mixed
find_door(object searcher, string what)
{
   if (hidden_door_found)
      return 0;

   if (searcher->query_skill(110) > 45)
   {
      add_exit(WALL_LEVEL + "chainchamber1", "south", 0);
      say(QCTNAME(searcher) + " discovers a hidden door in the " +
          "south wall.\n");
      hidden_door_found = 1;
      other_room->door_found();
      return "You discover a secret door in the south wall.\n";
   }

   return 0;
}


void
door_found()
{
   tell_room(TO, "Suddenly, with a scraping sound, " +
             "a hidden door in the south wall opens.\n");   
   hidden_door_found = 1;
   add_exit(WALL_LEVEL + "chainchamber1", "south", 0);
}


string
ngall_descr()
{
   string *roomfiles;
   object *inv, *live, room;
   int i;

   roomfiles = NGALL;
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
        return ("Looking north, along the gallery, you can see " +
                 COMPOSITE_LIVE(live) + ". ");
   }
   return ("The gallery to the north of you is empty. ");
}


string
room_descr()
{
   return "You are standing in the southeast corner of a very huge " +
          "gallery. A flight of stairs leads down to a lower level. " +
          "The large room is chilly, exposed to the draft " +
          "from the outside by a number of very narrow slit windows " +
          "along the walls. " + ngall_descr() + "The " +
          "entire outer wall of the gallery is covered with large " +
          "paintings.\n";
}


int
query_hidden_door()
{
   return hidden_door_found;
}

