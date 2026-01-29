/*
   Wayreth.

   studyrooms.c
   ------------

   Coded ........: 95/06/02
   By ...........: Jeremiah

   Latest update : 95/06/02
   By ...........: Jeremiah

*/

#include "/d/Krynn/wayreth/local.h"
inherit TOWERROOM;


void
create_tower_room()
{
   set_short("The southern study");
   set_long("You are standing in a very quiet room. This looks most " +
            "of all like a study area.\n");

   add_exit(WTOWER + "study", "north", 0);
}
