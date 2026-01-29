inherit "/std/room";
#include <stdproperties.h>

create_room()
{
    set_short("In shallow Waters");
    set_long("You are in shallow waters. East you spy the coastline of " +
	"Sparkle.\n");
    add_prop(ROOM_I_TYPE, ROOM_IN_WATER);
}

