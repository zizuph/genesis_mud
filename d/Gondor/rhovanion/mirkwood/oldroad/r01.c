/*
 * Room of the Old Road in Mirkwood.
 * Varian - Nov, 2012
 *
 */

#include "../defs.h"
#include <stdproperties.h>

inherit MIRKWOOD_OLDROAD_DIR + "base";

string warning();

/*
 * Function name: create_mirkwood_road_room
 * Description  : Create this room of the old road
 */
void create_mirkwood_road_room()
{
    // Force the randomized messages to always be the same for roads
    set_room_seed(1);
    set_mirkwood_location(LOCATION_WEST_EDGE);
        
    ::create_mirkwood_road_room();
    
    set_add_wildlife();

    set_short("You are on the Old Road somewhere " +
        "near the western edge of Mirkwood Forest");

    // Customized local long descriptions

    add_long("Just west of here, you can see the tangled maze of " +
        "underbrush and trees begin to dwindle and fade away as " +
        "the rocky path of the road winds gently down into the " +
        "lush, green vale of the Anduin. ",
        ({LIGHT_DUSKDAWN, LIGHT_MIDDAY, LIGHT_BRIGHT}));
    add_long("Out of the corner of your eye, you notice a small tree " +
        "with some sort of markings carved into it. ", ({LIGHT_MIDDAY,
        LIGHT_BRIGHT }));
    
    add_item_light(({"anduin","vale","vale of anduin", "valley", "river"}), 
        "Twisting your head as you try to peek through " +
        "the trees to the west, you think you can make out the " +
        "silvery ribbon of the great river, Anduin, sparkling in " +
        "the @@light_type@@, as it hides in its valley.\n",
        ({LIGHT_DUSKDAWN, LIGHT_MIDDAY, LIGHT_BRIGHT}));
    add_item_light(({"tree","small tree"}), "A small tree is growing " +
        "near the edge of the road. It has some markings carved deep " +
        "into the truck, which have obviously faded with age. You " +
        "might want to examine them closely.\n",
        ({LIGHT_DUSKDAWN, LIGHT_MIDDAY, LIGHT_BRIGHT}));
    add_item_light(({"marking", "markings"}), warning,
        ({LIGHT_DUSKDAWN, LIGHT_MIDDAY, LIGHT_BRIGHT}));


    add_exit("r02", "east");
    add_exit("/d/Shire/anduin/east/rd05.c", "west");

    add_forest_entrance(MIRKWOOD_CENTRAL_FOREST_DIR + "r00/f07", "northeast");
    add_forest_entrance(MIRKWOOD_SOUTH_FOREST_DIR + "r00/f06", "south");
    add_forest_entrance(MIRKWOOD_SOUTH_FOREST_DIR + "r00/f07", "southeast");
}

string warning() {
    MIRKWOOD_MASTER->set_received_warning(this_player(), WARNING_ROAD);
    return "These markings are in fact words which have been carved into "
        + "the trunk of this tree. They read \n" 
        + "- GREENWOOD THE GREAT - \n"
        + "STAY ON THE ROAD AND BEWARE OF SPIDERS!\n";
}