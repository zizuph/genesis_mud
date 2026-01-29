/*
   Wayreth.

   public_library.c
   ----------------

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
   set_short("Public library");
   set_long("You find yourself in a library. Here you can read " +
            "about the mages of Wayreth. It is however only possible " +
            "to gain limited information about the mages here. " +
"Deeper knowledge can only be acquired if you are a mage " +
            "yourself.\n"); 

   add_exit(WTOWER + "guestroom", "east", 0);
}
