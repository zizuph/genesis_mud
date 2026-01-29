inherit "/std/room";
#include <stdproperties.h>
#include "../local.h"

void
create_room()
{
    set_short("In the open sea");
    set_long("You are out on the open sea, but to the south you can make " +
	     "out some high mountains further inland and a bay with " +
	     "calmer waters opens up in between the hills, which make up " +
	     "the coastline.\n");
    add_prop(ROOM_I_TYPE, ROOM_IN_WATER);

    add_item(({"mountains","mountain"}),
	     "These are high mountains indeed, how high you will only be " +
	     "able to tell once you've been there yourself.\n");
    add_item("hills",
	     "These hills are not as high as the mountains, but they still " +
	     "leave the coastline ragged and dangerous.\n");
    
}
