/*
 * Outdoor room in Green Oaks
 * By Finwe, August 2004
 */
 
//#pragma strict_types

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
    set_short("A northern road in Green Oaks");
    set_long(short() + ". " + s_desc_sky_outside_sky() + "The road " +
        "passes along the southern border of an orchard. Trees line " +
        "both sides of the road, which shade all who pass this way. A " +
        "strong building is to the southwest. A large building stands " +
        "to the southeast with a smaller building connected to it. There is " +
        "a sign hanging above the door.\n");
    
    add_item(({"southeast building", "southeastern building"}),
        "The exquisite building is made of stone. It is made from stone " +
        "and carved with exquisite designs. The building seems alive. " +
        "A smaller building is connected to it.\n");        

    add_item(({"south building", "southern building", "small building",
            "smaller building"}),
        "The stone building is carved with beautiful designs and is " +
        "south of the road. It seems alive and is annexed to the " +
        "southeastern building. Soft, chittering sounds echo from within.\n");

    add_item(({"southwest building", "southwestern building"}),
        "The building is made of stone. It is square and carved with " +
        "exquisite designs. The building looks alive. It appears sturdier " +
        "than most other buildings. Periodically, travellers stream in " +
        "and out of it.\n");
    
    set_add_road();
    set_add_trees();
    set_add_orchard();
    set_add_sign("Green Oak's Bank");
    reset_room();
    
    add_exit(ORCHARD_DIR + "orchard11", "north");
    add_exit(GO_DIR + "bank", "south");
    add_exit(GO_DIR + "road04", "east");
    add_exit(GO_DIR + "road02", "west");

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
            elves[index]->set_restrain_path(({GO_DIR, ORCHARD_DIR}));
            elves[index]->set_random_move(3);
            elves[index]->set_monster_home(GO_DIR + this_room);
            elves[index]->move(TO);
 
        }
    }

}
