/*
 * Road to Blue Mountains
 * - Finwe, July 2002
 */

#include "local.h"

inherit BASE_ROAD;

void
create_blue_road()
{
   area = "near the top of a ridge in";
   areaname = "the Blue Mountains";
   land = "Eriador";
   areatype = 5;
   areadesc = "path";


    extraline = "A rocky path leads north and south between jagged peaks " +
        "and broken boulders. The peaks block your view, yet to the north, " +
        "it appears they are more distant than anywhere else. Some grass " +
        "and wild flowers grow in the cracks of the boulders.";
   
    add_item(({"green grass", "grass", "matted grass"}),
        "It is sparse and brown. It grows in the cracks of the boulders " +
        "alongside the path. Some wildflowers grow alongside the grass.\n");
    add_item(({"path", "road", "rocky path", "rocky road"}),
        "The path is rocky as it twists between large boulders. It runs " +
        "generally north into the mountains and south towards the lowlands.\n");
    add_item(({"blue mountains", "mountains", "mountains of the lune", 
            "ered luin"}),
        "The Blue Mountains are a tall chain of mountains. They run " +
        "north and south with tall, rugged peaks that reach to the sky.\n");
    add_item(({"wild flower", "wildflowers", "flowers"}),
        "Wildflowers grow scattered between the cracks of the boulders. They dot the " +
        "area with their cheery blossoms.\n");
    add_item(({"peaks", "mountain peaks"}),
        "The peaks are craggy and obviously very ancient. They are " +
        "various heights, some rising above you, looking like broken towers.\n");
    add_item(({"boulders", "cracked boulders", "rocks", "large rocks"}),
        "They are different sizes and colors, ranging in size from twice your " +
        "height down to small enough to sit on. Not many are large enough to " +
        "lift, but most are cracked and jagged. Some grasses and " +
        "wildflowers grow between them, with a twisting path bending its " +
        "way between the rocks.\n");

   add_exit(ROAD_DIR + "rd11","north");
   add_exit(ROAD_DIR + "rd09","south");

}
