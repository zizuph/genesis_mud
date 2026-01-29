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
    proxim = (["river": ({1, "east"}),
               "harbour": ({2, "southwest"})]);
    create_plain();
    
    add_my_desc(lay_desc, this_object());
    
    add_exit(PLAINS + "plains_24_9", "east");
    add_exit(PLAINS + "plains_23_10", "south");
    add_exit(PLAINS + "plains_22_10", "southwest");
    add_exit(PLAINS + "plains_22_9", "west");
}
public void
init()
{
    ::init();
    init_lay();
}
