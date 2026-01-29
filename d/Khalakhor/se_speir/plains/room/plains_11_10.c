/**********************************************************************
 * - plains_11_10.c                                                 - *
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
    proxim = (["village": ({1, "east"}),
               "harbour": ({1, "south"})]);

    create_plain();
    
    add_my_desc(lay_desc, this_object());
    
    add_exit(PLAINS + "plains_11_9", "north");
    add_exit(PLAINS + "plains_12_9", "northeast");
    add_exit(PLAINS + "plains_12_10", "east");
    add_exit(PLAINS + "plains_12_11", "southeast");
    add_exit(PLAINS + "plains_11_11", "south");
    add_exit(PLAINS + "plains_10_11", "southwest");
}
public void
init()
{
    ::init();
    init_lay();
}


