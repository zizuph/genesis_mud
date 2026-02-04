/*
    A room inside the wall (or closet). Mortricia 920909
 */
inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include "/d/Terel/common/terel_defs.h"

#define BS(message)    break_string(message, 70)
#define TP             this_player()
#define TO             this_object()

object skeleton;

reset_room()
{
    if (skeleton) {
        skeleton -> update_skeleton();
        return;
    }

    skeleton = clone_object(MANSION + "chapel/skeleton");
    skeleton -> move(TO);
}

void
create_room()
{

    object door;
    set_short("Inside wall");
    set_long(BS(
        "You are standing in a secret room located in the wall.\n"));

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, 0);

    door = clone_object(MANSION + "chapel/closet_door1");
    door -> move(TO);

    add_exit(MANSION + "chapel/chapel", "north", 0);

    reset_room();
}
