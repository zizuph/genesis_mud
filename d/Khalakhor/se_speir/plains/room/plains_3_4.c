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
    proxim = (["shore":({0, "west"}),
               "t_hills":({3, "north"})]);

    create_plain();

    add_my_desc(lay_desc, this_object());
    
    add_exit(PLAINS + "plains_3_3", "north");
    add_exit(PLAINS + "plains_4_3", "northeast");
    add_exit(PLAINS + "plains_4_4", "east");
    add_exit(PLAINS + "plains_4_5", "southeast");
    add_exit(PLAINS + "plains_3_5", "south");
    add_exit(PLAINS + "plains_2_3", "northwest");
}
public void
init()
{
    ::init();
    init_lay();
}
