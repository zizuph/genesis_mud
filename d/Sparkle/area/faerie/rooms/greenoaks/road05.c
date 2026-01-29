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
string this_room = "road05";

void
create_town_room()
{
    set_short("A northern road in Green Oaks");
    set_long(short() + ". " + s_desc_sky_outside_sky() + "It is wide " +
        "and runs beneath the tall oaks of the forest. The road is " +
        "often busy with travellers and elves that pass this way. To " +
        "the south is a park.\n");
        
    set_add_road();
    set_add_forest();
    set_add_park();
    set_add_trees();
       
    add_exit(GO_DIR + "road01", "north");
    add_exit(GO_DIR + "park01", "south");
    add_exit(GO_DIR + "road06", "east");

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
            elves[index]->set_type(GUARD);
            elves[index]->set_power(90 + random(15));
            elves[index]->set_restrain_path(({GO_DIR, ORCHARD_DIR, FOREST_DIR}));
            elves[index]->set_random_move(3);
            elves[index]->set_monster_home(GO_DIR + this_room);
            elves[index]->move(TO);
 
        }
    }

}