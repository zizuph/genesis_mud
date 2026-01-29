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
    proxim = (["village":({4, "south"}),
               "forest":({3, "northeast"})]);

    create_plain();
    
    add_my_desc(lay_desc, this_object());
    
    add_exit(PLAINS + "plains_15_3", "north");
    add_exit(PLAINS + "plains_16_3", "northeast");
    add_exit(PLAINS + "plains_16_4", "east");
    add_exit(PLAINS + "plains_16_5", "southeast");
    add_exit(PLAINS + "plains_15_5", "south");
    add_exit(PLAINS + "plains_14_5", "southwest");
    add_exit(PLAINS + "plains_14_4", "west");
    add_exit(PLAINS + "plains_14_3", "northwest");
}
public void
init()
{
    ::init();
    init_lay();
}
