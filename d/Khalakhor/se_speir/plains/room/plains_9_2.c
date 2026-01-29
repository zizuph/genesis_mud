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
    proxim = (["t_hills":({3, "northwest"}),
               "forest":({1, "north"})]);

    create_plain();
    add_my_desc(lay_desc, this_object());
    
    add_exit(PLAINS + "plains_9_1", "north");
    add_exit(PLAINS + "plains_10_1", "northeast");
    add_exit(PLAINS + "plains_10_2", "east");
    add_exit(PLAINS + "plains_8_2", "west");
    add_exit(PLAINS + "plains_8_1", "northwest");
}
public void
init()
{
    ::init();
    init_lay();
}
