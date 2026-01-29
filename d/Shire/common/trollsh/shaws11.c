/* File: /d/Shire/common/trollsh/trollsh11.c */

#include "defs.h"
inherit "/d/Shire/common/trollsh/shawrom";	/*master object*/

create_shawrom()
{

    set_short("A hidden ridge in the Trollshaws");
    set_extraline("You are standing on a ridge of the hill far " +
        "from the safety of the road. The forest is dense, blocking " +
        "your view in all directions. The ground is littered with " +
        "forest debris. North is a narrow slope that runs up over " +
        "a ridge.\n");

    add_item(({"eastroad","road","east road","slope", "great east road"}),
        "Down the slope to the southeast you see the Great East Road. " +
        "It is too steep to climb down there though.\n");

    NORTH("shaws12");
}
