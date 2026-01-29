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
    proxim = (["river"  : ({2, "northwest"})]);

    create_plain();
    
    add_my_desc(lay_desc, this_object());
    
    add_exit(PLAINS + "plains_29_12", "southeast");
    add_exit(PLAINS + "plains_28_12", "south");
    add_exit(PLAINS + "plains_27_12", "southwest");
    add_exit(PLAINS + "plains_27_11", "west");
    add_exit(PLAINS + "plains_27_10", "northwest");
}
public void
init()
{
    ::init();
    init_lay();
}
