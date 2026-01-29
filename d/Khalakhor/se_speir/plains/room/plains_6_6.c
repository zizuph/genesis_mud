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
               "t_hills":({4, "north"})]);

    create_plain();
    add_my_desc(lay_desc, this_object());
    
    add_exit(PLAINS + "plains_6_7", "south");
    add_exit(PLAINS + "plains_5_7", "southwest");
    add_exit(PLAINS + "plains_5_6", "west");
    add_exit(PLAINS + "plains_5_5", "northwest");
}
public void
init()
{
    ::init();
    init_lay();
}
