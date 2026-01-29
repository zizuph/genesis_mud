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
string this_room = "road14";

void
create_town_room()
{
    set_short("A southwestern road in Green Oaks");
    set_long(short() + ". " + s_desc_sky_outside_sky() + "It widens " +
        "here as roads from all over Green Oaks meet here. The road runs " +
        "north and southeast as it surrounds the town. The park to the " +
        "northeast is quiet and peaceful. A wide building stands to " +
        "the east with a sign hanging over the door.\n");

    set_add_road();
    set_add_park();
    set_add_trees();
    set_add_forest();
    set_add_plain_bldg("It stands hidden in the trees to east.\n");
    set_add_sign("Leather Shop of Green Oaks");
    set_add_arch("It leads east into a square building.");

    add_item(({"eastern building", "square building", "east building"}),
        "It is perfectly square and is set between the trees. The building " +
        "is one story and has a sign hanging above the door.\n");

    add_exit(GO_DIR + "road12", "north");
    add_exit(GO_DIR + "lshop", "east");
    add_exit(GO_DIR + "road18", "southeast");
    add_exit(GO_DIR + "park06", "northeast");
    
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