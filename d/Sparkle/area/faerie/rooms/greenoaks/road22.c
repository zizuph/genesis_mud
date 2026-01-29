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
string this_room = "road22";

void
create_town_room()
{
    set_short("A southwestern road in Green Oaks");
    set_long(short() + ". " + s_desc_sky_outside_sky() + "It is busy " +
        "with elves that travel along it. The forest grows along the " +
        "southern edge of the road. Buildings are scattered among the " +
        "trees. There is a wide building northeast of the road.\n");

    set_add_road();
    set_add_trees();
    set_add_forest();
    set_add_sign("Pub of Green Oaks");

    set_add_plain_bldg("It is square and sits northeast of the road. A " +
        "sign hangs above the door.\n");

    add_item(({"northeastern building", "northeast building", "wide building"}),
        "The building is large and square. Unlike other buildings, " +
        "there aren't to many trees around it. A sign hangs above the door.\n");


    add_exit(GO_DIR + "road23", "east");
    add_exit(GO_DIR + "road18", "northwest");
    add_exit(GO_DIR + "pub", "northeast");

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
            elves[index]->set_type(GUARD);
            elves[index]->set_power(90 + random(15));
            elves[index]->set_restrain_path(({GO_DIR, ORCHARD_DIR, FOREST_DIR}));
            elves[index]->set_random_move(3);
            elves[index]->set_monster_home(GO_DIR + this_room);
            elves[index]->move(TO);
        }
    }

}