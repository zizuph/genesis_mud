/*
 * Road to Blue Mountains
 * - Finwe, July 2002
 *
 *  2006.09.05, Toby; Added add_item in accordance to bug reports
 */

#include "local.h"

inherit BASE_ROAD;

void
create_blue_road()
{
   area = "south of";
   areaname = "the river";
   land = "Eriador";
   areatype = 0;
   areadesc = "path";


    extraline = "The field surrounds you, obscuring your view of most " +
        "everything nearby. A bridge stretches across the river, permitting " +
        "travellers to easily cross to the other side safely.";
   
    add_item(({"tall grass","grass"}),
        "It is tall and green. It hides the ground and waves lazily in " +
        "the breeze in all places except for where it is trampled from " +
        "travellers who come this way.\n");
    add_item(({"path", "road"}),
        "The path runs through the field, almost hidden by the long grass.\n");
    add_item(({"gulf of lune", "gulf of lhun", "lune", "lhun"}),
        "The Gulf of Lune sparkles in the distance, like a thin, blue " +
        "ribbon. It is rumoured the gulf was formed long ago when the " +
        "world was remade and that that elves still live near it, some " +
        "leaving forever, never to be seen.\n");
    add_item(({"path", "road", "trampled grass"}),
        "The path meanders through the grassy field. It is nothing more " +
        "than trampled grass from travellers who come this way.\n");
    add_item(({"blue mountains", "mountains", "mountains of the lune", 
            "ered luin"}),
        "The Blue Mountains rise in the distance to the northwest. They are " +
        "a large chain of mountains that run north and south for as far " +
        "as the eye can see. They are made up of tall, rugged peaks that " +
        "reach to the sky.\n");
    add_item(({"wild flower", "wildflowers", "flowers"}),
        "They dot the area with their cheery blossoms. They are thick " +
        "and colourful, providing bright spots of color in the otherwise " +
        "lush green grass.\n");
    add_item(({"peaks", "mountain peaks"}),
        "They are large, almost seeming to touch the sky. They are hard " +
        "to examine from afar, but appear craggy and jagged.\n");
    add_item(({"stone bridge", "bridge", "white bridge"}),
        "This bridge is made of fine stones. It spans the river and " +
        "appears large enough to allow quite a few travellers to walk " +
        "abreast across it. The bridge looks durable and elvish in design " +
        "and construction. The stones are perfectly set together and " +
        "look very new.\n");
    add_item(({"stones", "fine stones"}),
        "The fine stones are squared and expertly cut. There is a look " +
        "of elvish quality about them as the bridge looks brand new, even " +
        "though it is probably ages old.\n");
    add_item(({"river", "river lune", "river lhun"}),
        "The river Lhun rushes southwest, under the bridge and out to " +
        "the sea. It flows from the mountains and looks perilous. A white " +
        "bridge has been constructed and crosses the river.\n");


   add_exit(ROAD_DIR + "rd05","northwest");
   add_exit(ROAD_DIR + "rd03","southeast");
}
