/*
 * Road to Blue Mountains
 * - Finwe, July 2002
 */

#include "local.h"

inherit BASE_ROAD;

void
create_blue_road()
{
   area = "somewhere in a";
   areaname = "large field";
   land = "Eriador";
   areatype = 1;
   areadesc = "path";


    extraline = "The field spreads out in all directions. The grass is " +
        "tall with a path that meanders through the field. The Blue " +
        "Mountains rise in the northwest ";
   
    add_item(({"grass"}),
        "The grass is tall, almost blocking your view. It waves in " +
        "the breeze and has a path that runs through it.\n");
    add_item(({"path", "road", "rocky path", "rocky road"}),
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

   add_exit(ROAD_DIR + "rd08","northwest");
   add_exit(ROAD_DIR + "rd06","southeast");

}
