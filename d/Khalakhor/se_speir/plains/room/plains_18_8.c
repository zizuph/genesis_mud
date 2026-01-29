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
    proxim = (["village": ({1, "southwest"}),
               "harbour": ({3, "south"})]);

    create_plain();
    
    add_my_desc(lay_desc, this_object());
    
    add_exit(PLAINS + "plains_18_7", "north");
    add_exit(PLAINS + "plains_19_7", "northeast");
    add_exit(PLAINS + "plains_19_9", "southeast");
    add_exit(PLAINS + "plains_18_9", "south");
    add_exit(PLAINS + "plains_17_9", "southwest");
    add_exit(PLAINS + "plains_17_8", "west");
    add_exit(PLAINS + "plains_17_7", "northwest");
}
public void
init()
{
    ::init();
    init_lay();
}
