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
string this_room = "road15";

void
create_town_room()
{
    set_short("A road in central Green Oaks");
    set_long(short() + ". " + s_desc_sky_outside_sky() + "It runs " +
        "along the southern edge of the park, and past a square building " +
        "south of the road. Branches spread out and shade everything " +
        "beneath them.\n");

    set_add_road();
    set_add_trees();
    set_add_sign("Pub of Green Oaks");
    set_add_park();

    set_add_plain_bldg("It is square and sits south of the road. A " +
        "sign hangs above the door.\n");

    add_item(({"southern building", "square building", "south building"}),
        "The building is large and square. Unlike other buildings, " +
        "there aren't to many trees around it. A sign hangs above the door.\n");


    add_exit(GO_DIR + "pub", "south");
    add_exit(GO_DIR + "road16", "east");
    add_exit(GO_DIR + "road19", "southwest");
    
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
            elves[index]->set_type(ADULT);
            elves[index]->set_power(70 + random(15));
            elves[index]->set_restrain_path(({GO_DIR, ORCHARD_DIR, FOREST_DIR}));
            elves[index]->set_random_move(3);
            elves[index]->set_monster_home(GO_DIR + this_room);
            elves[index]->move(TO);
         }
    }

}