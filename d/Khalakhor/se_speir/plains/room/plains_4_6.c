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
    proxim = (["shore":({0, "west"}),
               "t_hills":({4, "north"})]);

    extra = "A river flows into the sea from the north here. It is almost fifteen feet wide and deep enough to drown.";
    add_item(
             ({"stream", "current", "water", "river"}),
             "A small, but swift river, joining the Lear Min, almost fifteen feet wide and deep enough to drown, rushes from the north and into the south.\n"
             );
    add_cmd_item(
                 ({"stream", "current", "water", "river"}),
                 ({"swim", "drink"}),
                 ({"It's too swift to swim in.\n", "You drink from the river and feel refreshed.\n"})
                 );
    
    create_plain();
    add_my_desc(lay_desc, this_object());
    
    add_exit(PLAINS + "plains_4_5", "north");
    add_exit(PLAINS + "plains_5_5", "northeast");
    add_exit(PLAINS + "plains_5_6", "east");
    add_exit(PLAINS + "plains_5_7", "southeast");
    add_exit(PLAINS + "plains_3_5", "northwest");
}
public void
init()
{
    ::init();
    init_lay();
}
