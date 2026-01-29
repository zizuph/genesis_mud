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
    proxim = (["forest":({1, "north"})]);

    create_plain();
    
    add_my_desc(lay_desc, this_object());
    
    add_exit(PLAINS + "plains_17_2", "north");
    add_exit(PLAINS + "plains_18_2", "northeast");
    add_exit(PLAINS + "plains_18_3", "east");
    add_exit(PLAINS + "plains_18_4", "southeast");
    add_exit(PLAINS + "plains_17_4", "south");
    add_exit(PLAINS + "plains_17_4", "southwest");
    add_exit(PLAINS + "plains_16_3", "west");
    add_exit(PLAINS + "plains_16_2", "northwest");
}
public void
init()
{
    ::init();
    init_lay();
}
