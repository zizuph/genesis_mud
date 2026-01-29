/*
   Pax Tharkas, Low level, storage room.

   store_room1.c
   -------------

   Coded ........: 95/01/10
   By ...........: Jeremiah

   Latest update : 95/02/03
   By ...........: Jeremiah

*/


#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/pax/local.h"

inherit PAXINROOM;

void
create_pax_room()
{
   set_short("Storage room");
   set_long("You are standing in a small storage room. Shelves " +
            "are lined up along all the walls. Most of the top shelves " +
            "look pretty empty. There are some things on the lower " +
            "shelves though. Some large sacks are standing against " +
            "one of the shelves. A doorway leads south, into another " +
            "storage room.\n");

   INSIDE;
   add_prop(ROOM_I_LIGHT,1);

   add_item("shelves", "Most of the shelves are empty. You don't see " +
            "anything on the top shelves. It does look as if there's " +
            "something on the lower shelves.\n");


   add_item("top shelves", "These shelves are all empty.\n");

   add_item(({"low shelves", "lower shelves"}), "There isn't much here. " +
            "You see a small supply of lamp oil in cans. Someone has put " +
            "some dead rats on the shelves next to the oil.\n");

   add_item(({"oil", "lamp oil", "cans"}), "Old rusty cans of lamp oil.\n");

   add_item(({"dead rats", "rats"}), "Yuck! It's a small pile of neatly " +
            "stacked dead rats.\n");

   add_item(({"sack", "sacks"}), "Some of these are filled with flour, " +
            "and others are filled with oatmeal.\n");


   set_alarm(30.0,360.0,"do_gully_thing");

   add_exit(LOW_LEVEL + "corridor3", "east", 0);
   add_exit(LOW_LEVEL + "store_room2", "south", 0);
}

void
do_gully_thing()
{
   tell_room(TO, "A small dirty gully dwarf arrives.\n");
   tell_room(TO, "The small dirty gully dwarf peers quizzically at you.\n");
   tell_room(TO, "The small dirty gully dwarf takes a dead rat from the " +
                 "shelf.\n");
   tell_room(TO, "The small dirty gully dwarf chews briefly on the dead " +
                 "rat.\n");
   tell_room(TO, "The small dirty gully dwarf nods contentedly.\n");
   tell_room(TO, "The small dirty gully dwarf leaves east.\n");
}
