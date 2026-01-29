/*
   Wayreth.

   hatrack.c
   ------------

   Coded ........: 970510
   By ...........: Karath

   Latest update : 
   By ...........: 

*/

#include "/d/Krynn/wayreth/local.h"
inherit TOWERROOM;


void
create_tower_room()
{
   set_short("The northern study");
   set_long("You are standing in a very quiet room. This looks most " +
            "of all like a study area. Benches lining the walls, " + 
            "a few chairs and small study tables, placed at " +
            "regular intervals across the floor, makes it possible " +
            "to sit in here undisturbed studying your spellbook. A " +
            "thick carpet is covering the floor, silencing your steps.\n");

   add_item("floor", "The floor is covered with a thick carpet.\n");

   add_item(({"carpet", "thick carpet"}), "A thick carpet covering " +
            "the entire floor, silencing your every step.\n");

   add_item(({"bench", "benches"}), "Comfortable cushioned benches, " +
            "standing along the walls of this room.\n");

   add_item(({"table", "tables"}), "Sturdy tables made of the finest " +
            "Vallenwood.\n");

   add_item(({"chair", "chairs"}), "Sturdy looking chairs made of " +
            "the finest Vallenwood. There is a chair for each table " +
            "in here.\n");

   set_wall_type(2);
   add_prop(ROOM_I_NO_CLEANUP, 1);

   add_exit(WTOWER + "studyn", "south", 0);
}
