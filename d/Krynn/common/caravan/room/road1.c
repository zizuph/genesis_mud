/*
*    Created by Vencar 13/08/2003
*
*    Copyright by Peter Bech Lund (Vencar)
*    08/2003
*
*    A room on the road to heaven
*    purely for testing reasons to the
*    new caravan.
*
*    Again, thanks to Aridor for the original
*    code that this resembles.
*/

#pragma strict_types
#include "../local.h"

inherit ROOM_BASE

void
init()
{
    ::init();
}


void
create_vin_mount_room()
{

    set_short("A wide road");
    set_special_short("A wide road");
    set_long("You are on a wide road winding through the mountains. " +
      "There is a set of roadtrails along the road, as if it is heavily " +
      "travelled by wagon.\n");

    add_exit(ROOM + "road2","north",0);
    /*
    (WAGON + "wagonadmin")->StartCaravan(ROOM + "road1");
    */

    (WAGON + "caravan")->StartCaravan(ROOM + "road1");


}

