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
    proxim = (["river"  : ({1, "northwest"})]);

    create_plain();
    
    add_my_desc(lay_desc, this_object());
    
    add_exit(PLAINS + "plains_27_10", "north");
    add_exit(PLAINS + "plains_28_11", "east");
    add_exit(PLAINS + "plains_28_12", "southeast");
    add_exit(PLAINS + "plains_27_12", "south");
    add_exit(PLAINS + "plains_26_12", "southwest");
    add_exit(PLAINS + "plains_26_11", "west");
    add_exit(PLAINS + "plains_26_10", "northwest");
}
public void
init()
{
    ::init();
    init_lay();
}
