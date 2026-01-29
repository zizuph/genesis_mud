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
    proxim = (["village": ({2, "east"}),
               "harbour": ({1, "south"})]);

    create_plain();
    
    add_my_desc(lay_desc, this_object());
    
    add_exit(PLAINS + "plains_11_10", "northeast");
    add_exit(PLAINS + "plains_11_11", "east");
    add_exit(PLAINS + "plains_10_12", "south");
    add_exit(PLAINS + "plains_9_12", "southwest");
}
public void
init()
{
    ::init();
    init_lay();
}
