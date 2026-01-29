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
    proxim = (["village":({2, "southwest"}),
               "forest": ({4, "north"})]);

    create_plain();
    
    add_my_desc(lay_desc, this_object());
    
    add_exit(PLAINS + "plains_17_5", "north");
    add_exit(PLAINS + "plains_18_5", "northeast");
    add_exit(PLAINS + "plains_18_6", "east");
    add_exit(PLAINS + "plains_18_7", "southeast");
    add_exit(PLAINS + "plains_17_7", "south");
    add_exit(PLAINS + "plains_16_7", "southwest");
    add_exit(PLAINS + "plains_16_6", "west");
    add_exit(PLAINS + "plains_16_5", "northwest");
}
public void
init()
{
    ::init();
    init_lay();
}
