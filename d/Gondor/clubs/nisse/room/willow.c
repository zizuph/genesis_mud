/*
 *  /d/Gondor/clubs/nisse/room/willow.c
 *
 *  On the willow tree inside the Nisse Ohtar camp.
 *
 *  Deagol, March 2003
 */

#pragma save_binary
#pragma strict_types

inherit "/d/Gondor/std/room";

#include <stdproperties.h>
#include <macros.h>
#include <filter_funs.h>

#include "/d/Gondor/defs.h"
#include "../nisse_defs.h"

/*
 *  Prototypes
 */
int	climb_down();

void
create_gondor()
{
    ::create_gondor();

    set_short("On the large willow tree in the Nisse Ohtar camp");
    set_long("You are sitting in the branches of a large willow tree in " +
        "the Nisse Ohtar camp. There are a lot of branches, and the leaves " +
        "block your view of the camp. It is quiet here, and you sense " +
        "water somewhere below.\n");

    add_item(({"camp"}),
        "You cannot see the camp through the lush green leaves.\n");
    add_item(({"leave", "leaves"}), "You glance at the leaves quickly. " +
        "You do not find anything special. They block your view of the " +
        "camp.\n");
    add_item(({"tree", "willow", "willow tree"}), "You are sitting on it. " +
        "You guess it must be at least one hundred years old.\n");
    add_item(({"branch", "branches"}), "You touch the branches briefly. " +
        "They are quite stout and are able to carry at least one more " +
        "person of your weight.\n");

    add_exit(NISSE_ROOM_DIR + "o_pool", "down", climb_down, 0, 0);
}

/*
 *  Function name: climb_down
 *  Description  : It's called when a player leaves the tree.
 *  Returns      : always 1
 */
int
climb_down()
{
    write("You climb down the large willow tree.\n");
    say(QCTNAME(TP) + " climbs down the large willow tree.\n");
    tell_room(NISSE_ROOM_DIR + "o_pool", QCNAME(TP) + " comes climbing " +
        "down the large willow tree.\n");
    TP->move_living("M", NISSE_ROOM_DIR + "o_pool", 1, 0);
    return 1;
}

/*
 *  Function name: query_livings
 *  Description  : It's called in o_pool.c when a player wants to enter
 *                 this room.
 *  Returns      : the number of livings in this room
 */
int
query_livings()
{
    return sizeof(FILTER_LIVE(all_inventory(TO)));
}
