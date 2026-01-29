/*
   Pax Tharkas, Ground level, storage room.

   store_room.c
   ------------

   Coded ........: 95/01/25
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
   set_long("You are standing in a small storage room. Shelves line the " +
            "the walls all the way around in this room, leaving only a " +
            "small gap open for the exit. The shelves are pretty empty " +
            "except for a few blankets and a couple of unlabelled boxes. " +
            "Judging by the lack of dust on the shelves, the contents " +
            "must have been removed recently.\n");
	
   INSIDE;

   add_item(({"blanket", "blankets"}), "Grey blankets of heavy material. " +
            "Most of these look very old.\n");

   add_item(({"box", "boxes"}), "Looking closer at the boxes you discover " +
            "that they contain heaps of hard, dry pieces of something " + 
            "looking like biscuits. You decide to leave them here.\n");

   add_item("shelves", "The shelves are old wooden shelves. There isn't " +
            "much dust on them, indicating that their contents has been " +
            "removed recently.\n");

   add_exit(GROUND_LEVEL + "playroom", "west",0);
}


