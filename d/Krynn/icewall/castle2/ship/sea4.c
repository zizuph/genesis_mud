inherit "/std/room";
#include <stdproperties.h>

create_room()
{
    set_short("In icy waters");
    set_long("You are in shallow, icy waters. Sharp blocks of ice drift everywhere, " +
        "and as you peer out, you can see the grey-white shape of icewall plains " +
	"to the south. The coast is bare and wind-bitten, except for a small, " +
        "sheltered bay.\n");
    add_prop(ROOM_I_TYPE, ROOM_IN_WATER);
}

