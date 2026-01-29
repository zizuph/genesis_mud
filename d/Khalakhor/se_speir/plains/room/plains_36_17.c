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
    
    add_exit(PLAINS + "plains_36_16", "north");
    add_exit(PLAINS + "plains_37_17", "east");
    add_exit(PLAINS + "plains_37_18", "southeast");
    add_exit(PLAINS + "plains_36_18", "south");
    add_exit(PLAINS + "plains_35_18", "southwest");
    add_exit(PLAINS + "plains_35_17", "west");
    add_exit(PLAINS + "plains_35_16", "northwest");
}
public void
init()
{
    ::init();
    init_lay();
}
