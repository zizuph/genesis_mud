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
    proxim = (["village":({3, "south"}),
               "forest":({4, "northeast"})]);

    create_plain();
    
    add_my_desc(lay_desc, this_object());
    
    add_exit(PLAINS + "plains_15_4", "north");
    add_exit(PLAINS + "plains_16_4", "northeast");
    add_exit(PLAINS + "plains_16_5", "east");
    add_exit(PLAINS + "plains_16_6", "southeast");
    add_exit(PLAINS + "plains_15_6", "south");
    add_exit(PLAINS + "plains_14_6", "southwest");
    add_exit(PLAINS + "plains_14_5", "west");
    add_exit(PLAINS + "plains_14_4", "northwest");
}
public void
init()
{
    ::init();
    init_lay();
}

