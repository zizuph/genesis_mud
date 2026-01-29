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
    proxim = (["village":({3, "southwest"}),
               "forest":({3, "north"})]);

    create_plain();
    
    add_my_desc(lay_desc, this_object());
    
    add_exit(PLAINS + "plains_18_4", "north");
    add_exit(PLAINS + "plains_19_4", "northeast");
    add_exit(PLAINS + "plains_19_5", "east");
    add_exit(PLAINS + "plains_19_6", "southeast");
    add_exit(PLAINS + "plains_18_6", "south");
    add_exit(PLAINS + "plains_17_6", "southwest");
    add_exit(PLAINS + "plains_17_5", "west");
    add_exit(PLAINS + "plains_17_4", "northwest");
}
public void
init()
{
    ::init();
    init_lay();
}
