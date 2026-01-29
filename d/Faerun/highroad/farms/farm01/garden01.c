/*
 * Farm flower garden
 * By Finwe, October 2006
 */
 
#pragma strict_types
 
#include "/d/Faerun/defs.h"
#include "/d/Faerun/flowers/flowers.h"
#include "defs.h"

inherit BASE_GARDEN;
inherit BASE_COMMON;

void
create_garden_room()
{
    add_prop(ROOM_S_MAP_FILE, "farm_e_map.txt");

    set_short("A large flower garden");

    set_extraline("The flower garden hugs the farmhouse, and full of " +
        "blossoms and color. The garden is lush and fills the air with " +
        "sweet fragrance. A gravel path wanders through the garden. A " +
        "large stone wall surrounds the garden and the orchard north " +
        "of the garden.\n");

    remove_item("wall");
    remove_item("stone wall");

    add_item(({"farmhouse", "house"}),
        "The farmhouse is large and surrounded flowerbeds. It is whitewashed " +
        "and sits at the southern edge of the garden.\n");      
    add_item(({"wall", "stone wall"}),
        "It is about waist high and made of flat stones piled on top of " +
        "each other. There is a closed gate set in it, connecting to an " +
        "orchard north of the garden.\n");
    add_item(({"gate"}),
        "The gate is made of iron. It is closed and locked. On the other " +
        "side is an abandoned orchard.\n");
    add_item(({"orchard", "abandoned orchard"}),
        "The orchard grows north of the garden. It looks abandoned and not " +
        "well cared for.\n");
    add_item(({"fruit trees"}),
        "The trees look old and twisted. They grow in what looks to be " +
        "an abandoned orchard beyond the stone wall.\n");

    reset_room();    
    set_flowers(FARM1_FLOWERS);
    add_exit(FARM1_DIR + "garden02", "southeast");
    
}

void reset_room()
{
    ::reset_room();
}
