inherit "/std/room";
#include <stdproperties.h>

create_room()
{
    set_short("In the Ergothian Seas");
    set_long("You are somewhere near South and North Ergoth. You see a\n" +
	"few islands around the ship.\n");
    add_prop(ROOM_I_TYPE, ROOM_IN_WATER);
}
