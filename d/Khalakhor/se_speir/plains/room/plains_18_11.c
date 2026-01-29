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
    proxim = (["village": ({1, "west"}),
               "river"  : ({3, "east"}),
               "harbour": ({0, "south"})]);

    create_plain();
    add_item(({"blanket", "lush grass", "grass", "soft grass"}), lay_desc);
    add_my_desc(lay_desc, this_object());
    
    add_exit(PLAINS + "plains_18_10", "north");
    add_exit(PLAINS + "plains_19_10", "northeast");
    add_exit(PLAINS + "plains_19_11", "east");
    add_exit(PLAINS + "plains_17_11", "west");
    add_exit(PLAINS + "plains_17_10", "northwest");
}
public void
init()
{
    ::init();
    init_lay();
}
