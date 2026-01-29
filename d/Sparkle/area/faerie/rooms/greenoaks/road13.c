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
string this_room = "road13";

void
create_town_room()
{
    set_short("A southeast road in Green Oaks");
    set_long(short() + ". " + s_desc_sky_outside_sky() + "It veers " +
        "northwest and south around a wide and a tall building to the " +
        "west. It passes beneath wide branches of many trees. A forest " +
        "grows on the eastern edge of the town.\n");

    set_add_road();
    set_add_trees();
    set_add_forest();

    set_add_plain_bldgs("There is a tall building to the west and a " +
        "wide building to the southwest.");
    add_item(({"tall building", "southwestern building", "southwest building"}),
        "The building is hidden in the trees to the southwest. It is tall. " +
        "The sounds of groans and shouts echo from it.\n");
    add_item(({"wide building", "western building", "west building"}),
        "It is hidden in the trees west of the road. The building is " +
        "one story and appears to be important.\n");


    add_exit(GO_DIR + "road17", "south");
    add_exit(GO_DIR + "road11", "northwest");

    reset_room();
}

/*
 * Function name:    init
 * Description    :
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
