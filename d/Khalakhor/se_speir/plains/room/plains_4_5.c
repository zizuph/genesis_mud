/**********************************************************************
 * - Added a laying function so players can lay upon grass or some  - *
 * - other player.                                                  - *
 * - Modified by Damaris@Genesis 02/2005                            - *
 * - Added a stream (foundation for the Distillers guild)           - *
 * -- Tapakah 04/2021                                               - *
 **********************************************************************/
#include "plains.h"
#include <macros.h>


inherit PLAINBASE;
#include "laying.c"
public void
create_khalakhor_room()
{
    proxim = (["shore":({1, "west"}),
               "t_hills":({3, "north"})]);

    extra = "A swift stream is flowing from the north, rapidly expanding towards the south. A small bridge has been built over it, There is a strange pillar next to the bridge.";
    create_plain();
    add_my_desc(lay_desc, this_object());
    
    add_item(
             ({"stream", "current", "water"}),
             "A fast-running stream, about eight feet wide and a five feet deep rushes from the north and into the south. It is very swift.\n"
             );
    add_item("bridge", "A sturdy, simple wooden bridge about a foot above the water. A strange pillar stands next to it.\n");
    add_item("pillar", "The pillar is about eight to nine feet tall and seems to be bottle shaped. It seems to be made out wood as well.\n");
    add_cmd_item(
                 ({"stream", "current", "water"}),
                 ({"swim", "drink"}),
                 ({"It's too small to swim in.\n", "You drink from the stream and feel refreshed.\n"})
                 );
    add_cmd_item(
		 ({"bridge", "down", "down bridge", "up",  "pillar"}),
		 ({"climb"}),
		 ({"You cannot really climb there.\n"})
		 );
    add_exit(PLAINS + "plains_4_4", "north");
    add_exit(PLAINS + "plains_5_4", "northeast");
    add_exit(PLAINS + "plains_5_5", "east");
    add_exit(PLAINS + "plains_5_6", "southeast");
    add_exit(PLAINS + "plains_4_6", "south");
    add_exit(PLAINS + "plains_3_5", "west");
    add_exit(PLAINS + "plains_3_4", "northwest");
}
public void
init()
{
    ::init();
    init_lay();
}
