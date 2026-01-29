/* File: slip */
/* The room where you slip down the tube in the volcano */

inherit "/std/room";

#include <stdproperties.h>

#include "track_room.h"

void
create_room()
{
    set_short("Tube");
    set_long("You're slipping down a dark tube.\n");
    add_prop(ROOM_I_LIGHT,0);
}

/*****************************************************************************/

void
init()
{
    ::init();
    call_out("land",50,TP);
}

/*****************************************************************************/

/*
 * Function name: land
 * Description:   The player lands after slipping down the tube at the
                  bottom of the volcano.
 * Arguments:     player (The player who slips)
 * Returns:       nothing
 */

void
land(object player)
{
    if (present(player)){
        tell_object(player, "Finally your reach the end of the tube.\n"
            + "You fall down from a hole in the wall.\n\n"
            + "                 !  !  !  B  O  I  N  G  !  !  !\n\n");
        player->move_living("the tube through its end", TRACKDIR + "bottom");
    }
    return;
}
