/*
   Pax Tharkas, Wall level, chainchamber.

   chainchamber4.c
   ---------------

   Coded ........: 95/02/16
   By ...........: Jeremiah

   Latest update : 95/03/08
   By ...........: Jeremiah

*/


#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/pax/local.h"

inherit PAXINROOM;

create_pax_room()
{
   set_short("Chain chamber");
   set_long("You are standing in a cavernous tunnel stretching to the " +
            "east and the to the west from here. A huge chain runs " +
            "though the room. Everything in here is covered in a thick " +
            "layer of dust.\n");

   INSIDE;
   add_prop(ROOM_I_LIGHT, 0);

   add_item("chain", "A huge chain made of steel links. each chain " +
            "link as high as a grown human, and thicker than a leg.\n");

   add_item("dust", "A thick layer of greyish dust, covering everything " +
            "in here.\n");


   add_exit(WALL_LEVEL + "chainchamber2", "east", 0);   
   add_exit(WALL_LEVEL + "chainchamber4", "west", 0);
}      


construction()
{
   write("Sorry this are is under construction.. you can't go there.\n");
   return 1;
}

