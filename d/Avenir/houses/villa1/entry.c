/*
 * villa1/entry.c
 *
 * Lilith, Nov 2021
 *
 */

#pragma strict_types

#include "villa1.h"

inherit V1 +"housebase";

/*
 * Function name:        create_house_room()
 * Description  :        Creates a house room from from the base file
 *                       "housebase.c"
 */

void 
create_house_room()
{
    add_exit(MAIN_ACCESS, "south");

    //    room_add_object(DOOR +"v1_door_out", 1);

    set_short("private tunnel");
    set_long("This is a tunnel whose walls and ceiling are "+
      "stacked with stone blocks. "+
      "At the south end of the tunnel is a stairwell "+
      "that spirals downwards, while at the north end "+
      "is a large wooden door with steel studs and an "+
      "intricate lock. A small sign is affixed to the " +
      "door.\n");


    add_cmd_item("sign", "read", "@@sign_desc@@");
    add_item(({"sign", "small sign"}), "@@sign_desc@@");

    add_item(({"east"}), "A tunnel wall.\n");
    add_item(({"west"}), "A tunnel wall.\n");
    add_item(({"north"}), "A heavy door.\n");
    add_item(({"south"}), "Stairs lead down.\n");


}

string
sign_desc()
{
    return
    "Gold letters have been painted on a black-lacquered "+
    "rectangle of wood:\n\n"+
    "                V I L L A   O N E   \n";		
    "\n";
}
