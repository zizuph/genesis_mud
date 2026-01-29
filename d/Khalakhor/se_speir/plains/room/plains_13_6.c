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
    proxim = (["village":({2, "south"})]);

    create_plain();
    
    add_my_desc(lay_desc, this_object());
    
    add_exit(PLAINS + "plains_14_5", "northeast");
    add_exit(PLAINS + "plains_14_6", "east");
    add_exit(PLAINS + "plains_14_7", "southeast");
    add_exit(PLAINS + "plains_13_7", "south");
}
public void
init()
{
    ::init();
    init_lay();
}
