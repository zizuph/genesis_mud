/*
   Wayreth. Stairwell in tower.

   stairwell01.c
   -------------

   Coded ........: Oct 2016
   By ...........: Arman

   Latest update : Oct 2016
   By ...........: Arman

*/

#include "/d/Krynn/wayreth/local.h"
#include "/d/Krynn/guilds/wohs/defs.h"

inherit TOWERROOM;


void
create_tower_room()
{
   set_short("a small chamber within the Tower of High Sorcery");
   set_long("You are standing within a small chamber that serves as the " +
       "entry to the Tower of High Sorcery. To your northwest an " +
       "intersection takes you to the North Tower, where the wizards " +
       "who reside here rest, train and study. To your southwest is " +
       "the entry to the South Tower and the Hall of Mages.\n"); 

   set_wall_type(1);

   add_item(({"chamber","small chamber"}),"Residing within the foretower, " +
       "this room provides entry to the North and South Towers, and " +
       "a portal to the court yard outside.\n");

   add_item(({"northwest","north tower","intersection"}),
       "To your northwest is an intersection that takes you to the " +
       "North Tower, where the wizards who reside here rest, train and " +
       "study.\n");

   add_item(({"southwest","south tower","entry"}),"To your southwest " +
       "is the entry to the South Tower. Here you will find the Hall " +
       "of Mages - a vast chamber where the Test is conducted with " +
       "aspirants of High Sorcery.\n");

   add_item(({"hall of mages","hall"}),"Through the southwest entry " +
       "you will find the Hall of Mages where the Test of High Sorcery " +
       "is conducted.\n");

   add_item(({"portal","court yard"}), "An open portal leading out " +
       "into the court yard in front of the tower. Even though the " +
       "portal is open, you don't feel the influence of the weather " +
       "outside.\n");
   
   add_exit(WTOWER + "yard02", "east", 0);
   add_exit(WTOWER + "stairwell01", "northwest", 0);
   add_exit(WTOWER + "hall_of_mages","southwest","@@aspirant_entry");
}

int
aspirant_entry()
{
   if(WOHS_MANAGER->query_invited_wohs_test(TP) || TP->query_wiz_level() 
      || TP->query_guild_member("Wizards of High Sorcery"))
   return 0;

   write("The Hall of Mages is closed to you. Only Aspirants who have " +
       "been invited by the Conclave of the Wizards of High Sorcery to " +
       "take the Test may enter.\n");
   return 1;
}
