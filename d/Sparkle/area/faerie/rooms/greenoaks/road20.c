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
string this_room = "road20";

void
create_town_room()
{
    set_short("A southern road in Green Oaks");
    set_long(short() + ". " + s_desc_sky_outside_sky() + "It runs " +
        "along the edge of the forest, heading east and west. Buildings " +
        "are scattered around the road.\n");

    set_add_road();
    set_add_trees();
    set_add_forest();

    set_add_plain_bldgs("There is a tall building to the northeast and " +
        "another to the west.\n");

    add_item(({"northeastern building", "tall building", "northeast building"}),
        "The building is taller than the others around it. Groans echo " +
        "from it.\n");

    add_item(({"western building", "wide building", "west building"}),
        "The building is large and square. Unlike most other buildings, " +
        "there aren't to many trees around it.\n");


    add_exit(GO_DIR + "road16", "north");
    add_exit(GO_DIR + "road21", "east");
    add_exit(GO_DIR + "road23", "southwest");

    reset_room();
}

/*
 * Function name: init
 * Description:
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
            elves[index]->set_type(ELDER);
            elves[index]->set_power(80 + random(15));
            elves[index]->set_restrain_path(({GO_DIR, ORCHARD_DIR}));
            elves[index]->set_random_move(3);
            elves[index]->set_monster_home(GO_DIR + this_room);
            elves[index]->move(TO);
        }
    }

}