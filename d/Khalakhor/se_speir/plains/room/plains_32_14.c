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
    create_plain();
    
    add_my_desc(lay_desc, this_object());
    
    add_exit(PLAINS + "plains_32_13", "north");
    add_exit(PLAINS + "plains_33_14", "east");
    add_exit(PLAINS + "plains_33_15", "southeast");
    add_exit(PLAINS + "plains_32_15", "south");
    add_exit(PLAINS + "plains_31_15", "southwest");
    add_exit(PLAINS + "plains_31_14", "west");
    add_exit(PLAINS + "plains_31_13", "northwest");
}
public void
init()
{
    ::init();
    init_lay();
}
