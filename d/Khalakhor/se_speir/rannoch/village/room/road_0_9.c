/* File         : /d/Khalakhor/se_speir/rannoch/village/room/road_0_9.c
 * Creator      : Darragh@Genesis
 * Date         : 00-10-05      
 * Purpose      : Map room file of the Loch Rannoch area.
 * Related Files: 
 * Comments     :
 * Modifications: Changed structure to coord system (Darragh 2003-07-25) 
 */

#pragma strict_types

#include "room.h"
#include <macros.h>
#include <stdproperties.h>
#include <language.h>
#include <ss_types.h>
#include "/d/Khalakhor/sys/defs.h"

inherit VILLAGE_BASEFILE;

int open_gate();
int ring_bell();

int
open_gate()
{
   write("The gate is closed for the time being, you will need " +
         "someone to open it for you.\n"); 
}
int
ring_bell()
{
   write("You ring the bell, and the guard that was leaning against "
       + "the wall unlocks the gate, opens it, and lets you out.\n");
   say(QCTNAME(this_player())+ " rings the bell, and the " +
                               "guard on duty opens the gate.\n");
   TP->move_living("out through the gate.\n" +
                   "The gate closes again","road_0_9.c",1,0);
   write("The gate closes again behind you.\n");
   return 1;
}
public void
create_road()
{
    add_item(({"gate","village gate","door","exit","entrance"}),
               "The gate, like the walls, is made of wooden poles. "
             + "It serves its purpose, but would break easily to "
             + "determined invaders. A bell hangs in a rope next "
             + "to the gate.\n");
    add_item(({"bell","rope"}),
               "A bell hangs from a rope on the gate's right side, "
             + "and ringing it should make some guard let you out.\n"); 
    add_item(({"guard","gatekeeper"}),
               "A tall man wielding a short spear and carrying a huge "
             + "shield is leaning against the wall, on the gate's left "
             + "side. He is part of the few guards of the village, and "
             + "by the look on his face, guarding the gate is not an "
             + "exciting assignment.\n"); 

    add_cmd_item("gate","open",open_gate);
    add_cmd_item("bell","ring",ring_bell);

    add_exit(ROOM + "road_0_8.c","north",0,1,0);
    add_exit(ROOM + "road_1_9.c","east",0,1,0);
    add_exit(ROOM + "road_0_10.c","south",0,1,0);

    set_short("Inside the village gate");
    set_long("Exit west.\n"
           + "Wall goes N and S.\n");
}

