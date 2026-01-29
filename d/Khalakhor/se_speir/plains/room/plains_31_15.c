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
    
    add_exit(PLAINS + "plains_31_14", "north");
    add_exit(PLAINS + "plains_32_14", "northeast");
    add_exit(PLAINS + "plains_32_15", "east");
    add_exit(PLAINS + "plains_32_16", "southeast");
    add_exit(PLAINS + "plains_31_16", "south");
    add_exit(PLAINS + "plains_30_15", "west");
    add_exit(PLAINS + "plains_30_14", "northwest");
}
public void
init()
{
    ::init();
    init_lay();
}
