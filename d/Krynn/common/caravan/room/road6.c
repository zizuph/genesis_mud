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

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

void
init()
{

    ::init();
}


void
create_vin_mount_room()
{
    set_short("A wide road, close to a wagonstation");
    set_special_short("A wide road, close to a wagonstation.");
    set_long("You are on a wide road winding through the mountains. " +
      "There is a set of roadtrails along the road, as if it is heavily " +
      "travelled by wagons. " +
      "Nearby to the west rises a few wooden buildings near the end" +
      " of the road, a sign on the side of one of the buildings creaks" +
      "in the wind.\n");

 //   add_exit(ROOM + "wagonstation","west",0);
    add_exit(ROOM + "road5","east","@@east");

}
