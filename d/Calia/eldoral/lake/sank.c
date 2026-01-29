#include <stdproperties.h>
inherit "/std/room";

public void
create_room()
{
    set_short("sunk room");
    set_long("This is a 'dud' room to move objects that " +
        "have sunken in lake eldoral. Players " +
        "should never be in here, and if you " +
       "are here and are a player, commune " +
        "a wiz to trans you out.\n");
    add_prop(ROOM_I_TYPE, ROOM_UNDER_WATER);
}
