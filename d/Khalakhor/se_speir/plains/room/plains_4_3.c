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
    proxim = (["shore":({2, "west"}),
               "t_hills":({2, "north"})]);

    create_plain();
    add_my_desc(lay_desc, this_object());
    
    add_exit(PLAINS + "plains_4_2", "north");
    add_exit(PLAINS + "plains_5_2", "northeast");
    add_exit(PLAINS + "plains_5_4", "southeast");
    add_exit(PLAINS + "plains_4_4", "south");
    add_exit(PLAINS + "plains_3_4", "southwest");
    add_exit(PLAINS + "plains_3_3", "west");
    add_exit(PLAINS + "plains_3_2", "northwest");
}
public void
init()
{
    ::init();
    init_lay();
}
