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
    
    add_exit(PLAINS + "plains_33_15", "south");
    add_exit(PLAINS + "plains_32_15", "southwest");
    add_exit(PLAINS + "plains_32_14", "west");
}
public void
init()
{
    ::init();
    init_lay();
}
