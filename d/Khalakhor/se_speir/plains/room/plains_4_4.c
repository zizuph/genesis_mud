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
    extra = "A small swift stream is flowing from the northwest, rapidly expanding towards the south.";

    create_plain();
    add_my_desc(lay_desc, this_object());

    add_item(
             ({"stream", "current", "water"}),
             "A fast-running stream, about five feet wide and a three feet deep rushes from the northwest into the plains. It is very swift.\n"
             );
    add_cmd_item(
                 ({"stream", "current", "water"}),
                 ({"swim", "drink"}),
                 ({"It's too small to swim in.\n", "You drink from the stream and feel refreshed.\n"})
                 );
    add_exit(PLAINS + "plains_4_3", "north");
    add_exit(PLAINS + "plains_5_4", "east");
    add_exit(PLAINS + "plains_5_5", "southeast");
    add_exit(PLAINS + "plains_4_5", "south");
    add_exit(PLAINS + "plains_3_5", "southwest");
    add_exit(PLAINS + "plains_3_4", "west");
    add_exit(PLAINS + "plains_3_3", "northwest");
}
public void
init()
{
    ::init();
    init_lay();
}
