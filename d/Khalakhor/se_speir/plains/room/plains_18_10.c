/**********************************************************************
 * - Added a laying function so players can lay upon grass or some  - *
 * - other player.                                                  - *
 * - Modified by Damaris@Genesis 02/2005                            - *
 **********************************************************************/
#include "plains.h"
#include <macros.h>


inherit PLAINBASE;
#include "laying.c"
public void
create_khalakhor_room()
{
    proxim = (["village": ({1, "west"}),
               "harbour": ({1, "south"})]);

    create_plain();
    
    add_my_desc(lay_desc, this_object());
    
    add_exit(PLAINS + "plains_18_9", "north");
    add_exit(PLAINS + "plains_19_9", "northeast");
    add_exit(PLAINS + "plains_19_10", "east");
    add_exit(PLAINS + "plains_19_11", "southeast");
    add_exit(PLAINS + "plains_18_11", "south");
    add_exit(PLAINS + "plains_17_11", "southwest");
    add_exit(PLAINS + "plains_17_10", "west");
    add_exit(PLAINS + "plains_17_9", "northwest");
}
public void
init()
{
    ::init();
    init_lay();
}
