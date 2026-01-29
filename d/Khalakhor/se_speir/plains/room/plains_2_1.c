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
               "t_hills":({0, "north"})]);
    extra = "A small swift stream is flowing from the hills in the " +
      "north southwards.";
    mountains_hidden = 1;

    create_plain();
    
    add_my_desc(lay_desc, this_object());
    
    add_exit(PLAINS + "plains_3_1", "east");
    add_exit(PLAINS + "plains_3_2", "southeast");
    add_exit(PLAINS + "plains_2_2", "south");
    add_exit(PLAINS + "plains_1_2", "southwest");
    add_exit(PLAINS + "plains_1_1", "west");
    /*    add_my_desc(
		"A small swift stream is flowing from the hills in the " +
		"north southwards.\n",
		this_object()
		); */
    add_item(
             ({"stream", "current", "water"}),
             "A small stream, about a foot wide and a foot deep rushes from the hills into the plains. It is very swift.\n"
             );
    add_cmd_item(
                 ({"stream", "current", "water"}),
                 ({"swim", "drink"}),
                 ({"It's too small to swim in.\n", "You drink from the stream and feel refreshed.\n"})
                 );
}
		
public void
init()
{
    ::init();
    init_lay();
}
