/*
   Pax Tharkas, Low level, storage room.

   store_room2.c
   -------------

   Coded ........: 95/01/10
   By ...........: Jeremiah

   Latest update : 95/05/08
   By ...........: Jeremiah

*/


#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/pax/local.h"

inherit PAXINROOM;

#define I_FOUND_LADDER "_i_found_pax_ladder"


int ladder_found = 0; /* 0 = ladder NOT found */

reset_pax_room()
{
   ladder_found = 0;
} 


create_pax_room()
{
   reset_pax_room();

   set_short("Store room");
   set_long("You are in what looks to be a store room. It looks much " +
            "like the one you just came from. Empty shelves " +
            "line the walls to all sides. A table has been placed in " +
            "one corner of the room. Some wooden barrels are standing " +
            "in another corner. Some sacks are standing next to the " +
            "barrels.\n");

   INSIDE;
   add_prop(ROOM_I_LIGHT,1);

   add_item(({"shelf", "shelves"}), "@@shelf_descr");

   add_item("table", "This is a plain wooden table. It looks like it " +
                     "has been pushed close to the shelves. Maybe " +
                     "acting as a platform to reach the higher shelves.\n");

   add_item(({"barrel", "barrels", "wooden barrels"}), "Large wooden barrels " +
            "used to store salted meat. They're empty now.\n");

   add_item(({"sack", "sacks"}), "Large sacks containing flour or oatmeal.\n");

   add_exit(LOW_LEVEL + "store_room1", "north", 0);
}


string
shelf_descr()
{
   string ret_str = "These are simple shelves made of wood. It would " +
                    "probably be possible to store large amounts of " +
                    "supplies on them. Now they are all empty.\n";
    
   if (!present("ladder",TO) && ladder_found == 0)
   {
      ret_str += "You discover a ladder leaning against one of the shelves.\n";
      say(QCTNAME(TP) + " discovers a ladder.\n");
      clone_object(POBJ + "ladder")->move(TO);
      TP->add_prop(I_FOUND_LADDER, 1);
      ladder_found = 1;
   }
   return ret_str;
}
