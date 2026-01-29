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
    proxim = (["t_hills":({0, "north"})]);
    mountains_hidden = 1;

    create_plain();
    add_my_desc(lay_desc, this_object());
    
    add_exit(PLAINS + "plains_8_1", "east");
    add_exit(PLAINS + "plains_8_2", "southeast");
    add_exit(PLAINS + "plains_7_2", "south");
    add_exit(PLAINS + "plains_6_2", "southwest");
    add_exit(PLAINS + "plains_6_1", "west");
}
public void
init()
{
    ::init();
    init_lay();
}
