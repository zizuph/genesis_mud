/*
   Pax Tharkas, Wall level, chainchamber, chain dissapears int a narrower
   tunnel. 

   chainchamber5.c
   ---------------

   Coded ........: 95/02/16
   By ...........: Jeremiah

   Latest update : 95/02/16
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
   set_short("Chain chamber at shaft");
   set_long("You are standing in a cavernous tunnel stretching to the " +
            "east from here. A huge chain runs from the tunnel east " + 
            "over a huge wooden cogwheel to another wooden cogwheel, " +
            "and then it disappears into a narrower tunnel going west. " + 
            "Both cogwheels are mounted on an iron axle, anchored in " +
            "solid stone. The links of the chain fit over teeth big " +
            "as tree trunks. The chain stretches out, disappearing " +
            "into the tunnel east from here.\n");

   INSIDE;
   add_prop(ROOM_I_LIGHT, 0);

   add_item("chain", "A huge chain made of steel links. Each chain " +
            "link is as high as a grown human, and thicker than a leg.\n");

   add_item("cogwheel", "A large wooden cogwheel with teeth as big as " +
            "tree trunks. It is mounted on a iron axle.\n");
 
   add_item("axle", "The axle around which the cogwheel can turn. It " +
            "keeps the cogwheel in place, solidly anchored into the " +
            "stone walls of the tunnel.\n");

   add_item("tunnel", "A narrow tunnel leading west. Its narrowness " +
            "and the presence of the huge cogwheels makes it impossible " +
            "to enter this tunnel.\n");

   add_exit(WALL_LEVEL + "chainchamber4", "east", 0);
}      


construction()
{
   write("Sorry this are is under construction.. you can't go there.\n");
   return 1;
}

