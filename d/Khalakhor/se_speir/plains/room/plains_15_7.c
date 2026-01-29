/**********************************************************************
 * - plains_15_7.c                                                  - *
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
    proxim = (["village": ({1, "south"}),
               "harbour": ({4, "south"})]);

    create_plain();
    
    add_my_desc(lay_desc, this_object());
    
    add_exit(PLAINS + "plains_15_6", "north");
    add_exit(PLAINS + "plains_16_6", "northeast");
    add_exit(PLAINS + "plains_16_7", "east");
    add_exit(PLAINS + "plains_16_8", "southeast");
    add_exit(PLAINS + "plains_15_8", "south");
    add_exit(PLAINS + "plains_14_8", "southwest");
    add_exit(PLAINS + "plains_14_7", "west");
    add_exit(PLAINS + "plains_14_6", "northwest");
}
public void
init()
{
    ::init();
    init_lay();
}
