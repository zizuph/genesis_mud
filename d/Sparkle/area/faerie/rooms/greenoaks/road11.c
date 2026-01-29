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
string this_room = "road11";

void
create_town_room()
{
    set_short("A eastern road in Green Oaks");
    set_long(short() + ". " + s_desc_sky_outside_sky() + "The road " +
        "widens into a small square here. A group of buildings surround " +
        "the square to the west and south. A feeling of peace and order " +
        "fills the area. A wide archway leads south into a wide building.\n");

    set_add_road();
    set_add_trees();
    set_add_forest();
    set_add_sign(ACADEMY_NAME + " of Green Oaks");
    set_add_plaza();
    set_add_arch("It is an opening into a building to the south.");

    set_add_plain_bldgs("There is a tall building to the west and a " +
        "wide building to the south.");
    add_item(({"tall building", "west building", "western building"}),
        "The building is hidden in the trees to the west. It is tall; " +
        "groans and shouts echo from it.\n");
    add_item(({"wide building", "south building", "southern building"}),
        "It stands at the southern end of the square. A sign hangs above " +
        "the door.\n");

//set_add_plain_bldg("");

    add_exit(GO_DIR + "road09", "north");
    add_exit(GO_DIR + "ac_boardrm", "south");
    add_exit(GO_DIR + "road13", "southeast");

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
            elves[index]->set_type(ADULT);
            elves[index]->set_power(70 + random(15));
            elves[index]->set_restrain_path(({GO_DIR, ORCHARD_DIR, FOREST_DIR}));
            elves[index]->set_random_move(3);
            elves[index]->set_monster_home(GO_DIR + this_room);
            elves[index]->move(TO);
        }
    }

}