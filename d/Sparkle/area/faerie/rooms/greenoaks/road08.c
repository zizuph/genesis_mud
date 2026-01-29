/*
 * Outdoor room in Green Oaks
 * By Finwe, August 2004
 */

#pragma strict_types

#include "defs.h"
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

inherit TOWN_BASE;

#define MAX_ELVES 3

static object *elves = allocate(MAX_ELVES);
string this_room = "road08";

void
create_town_room()
{
    set_short("A road in central Green Oaks");
    set_long(short() + ". " + s_desc_sky_outside_sky() + "It runs " +
        "through the middle of Green Oaks. Tall trees line other sides " +
        "of the road. Hidden on the north and south side of the road " +
        "other sides of the trees are plain buildings. To the southwest " +
        "is a serene park.\n");

    set_add_road();
    set_add_park();
    set_add_trees();

    set_add_plain_bldgs("There is a sturdy building is to the north and " +
        "a noisy building is to the south.");
    add_item(({"sturdy building", "northern building", "north building"}),
        "The building is hidden in the trees to the north. It appears " +
        "rectangular shaped and strong looking.\n");
    add_item(({"noisy building", "southern building", "south building"}),
        "This stone building is hidden between tall trees. Noises echo " +
        "from it of nosy travellers.\n");
    add_item(({"large building", "northeast building", "northeast building"}),
        "It is difficult to see what this building is, but it is square " +
        "shaped and two stories tall.\n");

    add_exit(GO_DIR + "road09", "east");
    add_exit(GO_DIR + "park03", "west");

    reset_room();

}

/*
 * Function name:	init
 * Description	:
 */
public void
init()
{
    ::init();

}

void
reset_room()
{
    int index;

    /* Do this first, since we may need to clone. */
    setuid();
    seteuid(getuid());

    /* Loop over all elements in the array. */
    for(index = 0; index < MAX_ELVES; index++)
    {
        if (!objectp(elves[index]))
        {
            elves[index] = clone_object(ELFMAKER);
            elves[index]->set_type(YOUNG);
            elves[index]->set_power(50 + random(15));
            elves[index]->set_restrain_path(({GO_DIR, ORCHARD_DIR}));
            elves[index]->set_random_move(3);
            elves[index]->set_monster_home(GO_DIR + this_room);
            elves[index]->move(TO);
        }
    }

}
