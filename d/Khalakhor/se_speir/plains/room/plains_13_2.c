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
    proxim = (["forest":({0, "northeast"})]);

    create_plain();
    
    add_my_desc(lay_desc, this_object());
    
    add_exit(PLAINS + "plains_13_1", "north");
    add_exit(PLAINS + "plains_14_2", "east");
    add_exit(PLAINS + "plains_14_3", "southeast");
    add_exit(PLAINS + "plains_13_3", "south");
    add_exit(PLAINS + "plains_12_3", "southwest");
    add_exit(PLAINS + "plains_12_2", "west");
    add_exit(PLAINS + "plains_12_1", "northwest");
}
public void
init()
{
    ::init();
    init_lay();
}
