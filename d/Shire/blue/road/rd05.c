/*
 * Road to Blue Mountains
 * - Finwe, July 2002
 */

#include "local.h"

inherit BASE_ROAD;

void
create_blue_road()
{
   area = "on a bridge over";
   areaname = "the river";
   land = "Eriador";
   areatype = 0;
   areadesc = "path";


    extraline = "The bridge runs northwest and southeast as it crosses " +
        "the river. It is sturdy and made of stone. Its craftsmanship is " +
        "obviously elvish as it doesn't look to be old at all. The river flows rapidly beneath the bridge, and fills the air with gentle sounds.";
   
    add_item(({"grass"}),
        "The grass is tall, growing on either side of the river in the large meadow. It is green and tall, and bends gently in the breeze.\n");
    add_item(({"path", "road"}),
        "The path runs straight across the bridge. Even though countless travellers have gone this way, there is no mark or trail evident on the bridge.\n");
    add_item(({"blue mountains", "mountains", "mountains of the lune", 
            "ered luin"}),
        "The Blue Mountains rise in the distance to the northwest. They are " +
        "a large chain of mountains that run north and south for as far " +
        "as the eye can see. They are made up of tall, rugged peaks that " +
        "reach to the sky.\n");
    add_item(({"wild flower", "wildflowers", "flowers", "blossoms", "cherry blossoms"}),
        "The area is dotted with wild flowers and their cheery blossoms. They are thick " +
        "and colourful, providing bright spots of color in the otherwise " +
        "lush green grass.\n");
    add_item(({"peaks", "mountain peaks"}),
        "They are large, almost seeming to touch the sky. They are hard " +
        "to examine from afar, but appear craggy and jagged.\n");
    add_item(({"stone bridge", "bridge"}),
        "Finely cut stones make up the bridge. They are white and expertly assembled, forming a beautiful white bridge.\n");
    add_item(({"stones", "fine stones", "white stones"}),
        "The fine stones are squared and expertly cut. There is a look " +
        "of elvish quality about them as the bridge looks brand new, even " +
        "though it is probably ages old.\n");
    add_item(({"river", "river lune", "river lhun"}),
        "The river Lhun rushes southeast, under the bridge and out to " +
        "the sea. It flows from the mountains and looks perilous. A white " +
        "bridge has been constructed and crosses the river.\n");

   add_exit(ROAD_DIR + "rd06","northwest");
   add_exit(ROAD_DIR + "rd04","southeast");

}
