/* 
 * Xak Tsaroth - Lower level
 * Originally coded by Percy
 * Revamped by Rastlin
 */
#pragma strict_types

#include "../../local.h"

inherit INROOM;

public void
create_xak_room()
{
    set_short("The store room");
    set_long("You find yourself in an old deserted store room. " +
	     "Bags of flour lie strewn about the room, and everything " +
	     "is absolutly covered in the fine white powder. An old " +
	     "sewer pipe leads up out of the room.\n");

    add_exit(HALL + "northtmpl", "up", "@@up");
    add_exit(MIDDLE + "sidestreet1", "east");
    
    add_item(({"pipe", "sewer pipe", "floor"}), "The cataclysm seems to " +
	     "have forced the old sewer pipe up through one of " +
	     "the walls.\n");
    add_item(({"flour", "bags", "powder", "white powder"}), "It looks just " +
	     "like ordinary flour to you.\n");
}

public int
up()
{
    write("The pipe is too slippery to climb.\n");
    return 1;
}
