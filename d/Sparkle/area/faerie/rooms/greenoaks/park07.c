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
string this_room = "park07";
 
void
create_town_room()
{
    set_short("Southern side of the park in Green Oaks");
    set_long(short() + ". " + s_desc_sky_outside_sky() + "The park " +
        "is unusually busy yet still maintains a calm feeling. Wisteria " +
        "grow along a trellis that marks the edge of the park. Tall " +
        "oaks shade the park. A stone building stands to the south of " +
        "the park.\n");
        
    set_add_park();
    set_add_road();

    add_item(({"stone building", "building",}),
        "The building is square with a domed roof. It is beautifully " +
        "sculpted from white stone, revealing an inner beauty that " +
        "seems to make the building alive.\n");         
    add_item(({"south building"}),
        "This building is one story and seems very quiet. There are no " +
        "visible windows and no loud noises echo from it.\n");
    
    add_exit(GO_DIR + "square", "north");
    add_exit(GO_DIR + "qm_office", "south");
    add_exit(GO_DIR + "park08", "east");
    add_exit(GO_DIR + "park06", "west");

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
            elves[index]->set_type(ELDER);
            elves[index]->set_power(70 + random(15));
            elves[index]->set_restrain_path(({GO_DIR, ORCHARD_DIR}));
            elves[index]->set_random_move(3);
            elves[index]->set_monster_home(GO_DIR + this_room);
            elves[index]->move(TO);
        }
    }

}