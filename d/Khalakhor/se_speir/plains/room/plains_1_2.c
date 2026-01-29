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
               "t_hills":({1, "north"})]);

    create_plain();
    
    add_my_desc(lay_desc, this_object());
    
    add_exit(PLAINS + "plains_1_1", "north");
    add_exit(PLAINS + "plains_2_1", "northeast");
    add_exit(PLAINS + "plains_2_2", "east");
    add_exit(PLAINS + "plains_2_3", "southeast");
}
public void
init()
{
    ::init();
    init_lay();
}
