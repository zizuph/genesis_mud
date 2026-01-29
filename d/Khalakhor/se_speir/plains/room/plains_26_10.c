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
    proxim = (["river"  : ({0, "west"})]);
    create_plain();
    
    add_my_desc(lay_desc, this_object());
    
    add_exit(PLAINS + "plains_26_9", "north");
    add_exit(PLAINS + "plains_27_10", "east");
    add_exit(PLAINS + "plains_27_11", "southeast");
    add_exit(PLAINS + "plains_26_11", "south");
    add_exit(PLAINS + "plains_25_11", "southwest");
    add_exit(PLAINS + "plains_25_10", "west");
}
public void
init()
{
    ::init();
    init_lay();
}
