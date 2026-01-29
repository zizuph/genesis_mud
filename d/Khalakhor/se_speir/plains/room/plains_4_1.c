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
    proxim = (["shore":({3, "west"}),
               "t_hills":({0, "north"})]);
    mountains_hidden = 1;

    create_plain();

    add_my_desc(lay_desc, this_object());
    
    add_exit(PLAINS + "plains_5_1", "east");
    add_exit(PLAINS + "plains_5_2", "southeast");
    add_exit(PLAINS + "plains_4_2", "south");
    add_exit(PLAINS + "plains_3_2", "southwest");
    add_exit(PLAINS + "plains_3_1", "west");
}
public void
init()
{
    ::init();
    init_lay();
}
