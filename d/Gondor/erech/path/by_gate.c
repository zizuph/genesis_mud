/*
 * by_gate.c
 * By Skippern
 */
#pragma strict_types

#include "../erech.h"

inherit E_STD + "path.c";
inherit "/lib/unique";

#include <stdproperties.h>

#include TERRAIN_TYPES

/* Prototypes */
public void      create_gondor();
public void      reset_room();

/* Global variables */
object ob;
object *ghost;
int    nr;

/*
 * Function name:    create_gondor()
 * Description  :    Creates the room.
 */
public void
create_gondor()
{
    set_short("Inside a tunnel.");
    set_long("You are inside a tunnel. To the north you can see the faint " +
        "light from the gate. The tunnel continues south, deeper " +
	"into the White Mountains. The air feels dry.\n");

    tunnel_items();
    add_item("light", "A faint light shines through the gate opening to " +
	"the north.\n");

    add_prop(ROOM_I_LIGHT, -2);
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_HIDE, 1);
    add_prop(ROOM_I_NO_ALLOW_STEED, 1);
    add_prop(ROOM_S_DARK_LONG, DARK_ROOM_LONG);
    add_prop(ROOM_I_TERRAIN_TYPE, TERRAIN_ERECH_TUNNEL);

    nr = 2;
    ghost = allocate(nr);

    reset_room();

    add_exit(TO_ROHAN, "north", 0, 2, 0);
    add_exit(E_PATH + "north1.c", "south", "@@dis_test", 2, 0);
}

public void
reset_room()
{
    object o;

    reset_ghosts(ghost, nr);

    o = clone_unique(E_NPC + "ghost2", 3);
    o->move(this_object());
}

/*
 * Function name:    dis_test()
 * Description  :    Tests if the players are brave enough to pass the exit.
 * Returns      :    0 = Success.
 *                   1 = Failure.
 */
int
dis_test()
{
    int dis = this_player()->query_stat(5);
    if (dis < 25 )
    {
        write(NO_DIS);
	return 1;
    }
    return 0;
}
