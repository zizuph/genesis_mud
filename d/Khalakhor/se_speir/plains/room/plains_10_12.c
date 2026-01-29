/**********************************************************************
 * - plains_12_10.c                                                 - *
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
    proxim = (["village": ({3, "northeast"}),
               "harbour": ({0, "south"})]);

    create_plain();
    
    add_my_desc(lay_desc, this_object());
    
    add_exit(PLAINS + "plains_10_11", "north");
    add_exit(PLAINS + "plains_11_11", "northeast");
    add_exit(PLAINS + "plains_9_12", "west");
}
public void
init()
{
    ::init();
    init_lay();
}
