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
string this_room = "road07";
 
void
create_town_room()
{
    set_short("A northeastern road in Green Oaks");
    set_long(short() + ". " + s_desc_sky_outside_sky() + "It is situated " +
        "on the edge of Green Oaks. North is a large orchard that borders " +
        "the town. The road runs northwest and southwest " +
        "and connects to another road that leads northeast. There is a " +
        "building to the west and south, hidden in the trees that line " +
        "the road.\n");
        
    set_add_road();
    set_add_orchard();
    set_add_trees();
    set_add_forest();

    set_add_plain_bldgs("A large building is to the west, and plain " +
        "building to the south.");
    add_item(({"plain building", "southern building", "south building"}),
        "The building is hidden in the tall trees. It is plain looking " +
        "and doesn't look very important.\n");
    add_item(({"large building", "west building", "west building"}),
        "It is hidden in the trees. The building is square " +
        "shaped with two stories\n");
    
    add_exit(ORCHARD_DIR + "orchard16", "north");
    add_exit(GO_DIR + "road04", "northwest");
    add_exit(GO_DIR + "road07n1", "northeast");
    add_exit(GO_DIR + "road09", "southwest");

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
