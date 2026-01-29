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
string this_room = "park05";
 
void
create_town_room()
{
    set_short("Eastern side of the park in Green Oaks");
    set_long(short() + ". " + s_desc_sky_outside_sky() + "A gentle breeze " +
        "blows through the park, and a sweet frangrance fills the air from " +
        "the flowers growing around the area. A stone building is to " +
        "the east and another to the southeast.\n");
        
    set_add_park();
    set_add_road();

    add_item(({"stone buildings", "stone building", "building", "buildings"}),
        "The buildings are square with domed roofs. They are beautifully" +
        "sculpted from white stone, revealing an inner beauty that " +
        "seems to make the buildings alive.\n"); 
    add_item(({"east building", "eastern building"}),
        "This building has two stories. Windows are set into the building " +
        "allowing fresh air to blow inside. Sounds of elves working out " +
        "drift from the windows.\n");
    add_item(({"windows"}),
        "They are set into the northeast building. The windows are open, " +
        "allowing fresh air to blow in. The sounds of elves working " +
        "out can be heard from the windows.\n");
    add_item(({"southeast building", "southeastern building"}),
        "The building is one story and appears quiet. There aren't " +
        "any visible windows in the building.\n");
                                    
    
    add_exit(GO_DIR + "park03", "north");
    add_exit(GO_DIR + "park08", "south");
    add_exit(GO_DIR + "square", "west");

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
            elves[index]->set_power(80 + random(15));
            elves[index]->set_restrain_path(({GO_DIR, ORCHARD_DIR}));
            elves[index]->set_random_move(3);
            elves[index]->set_monster_home(GO_DIR + this_room);
            elves[index]->move(TO);
        }
    }

}