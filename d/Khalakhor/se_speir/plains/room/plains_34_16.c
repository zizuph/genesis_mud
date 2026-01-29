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
    
    add_exit(PLAINS + "plains_35_16", "east");
    add_exit(PLAINS + "plains_35_17", "southeast");
    add_exit(PLAINS + "plains_34_17", "south");
    add_exit(PLAINS + "plains_33_17", "southwest");
    add_exit(PLAINS + "plains_33_16", "west");
    add_exit(PLAINS + "plains_33_15", "northwest");
}
public void
init()
{
    ::init();
    init_lay();
}
