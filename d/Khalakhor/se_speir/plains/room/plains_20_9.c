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
    proxim = (["village": ({4, "west"}),
               "river"  : ({4, "east"}),
               "harbour": ({2, "south"})]);

    create_plain();
    add_item(({"blanket", "lush grass", "grass", "soft grass"}), lay_desc);
    add_my_desc(lay_desc, this_object());
    
    add_exit(PLAINS + "plains_21_9", "east");
    add_exit(PLAINS + "plains_21_10", "southeast");
    add_exit(PLAINS + "plains_20_10", "south");
    add_exit(PLAINS + "plains_19_10", "southwest");
    add_exit(PLAINS + "plains_19_9", "west");
}
public void
init()
{
    ::init();
    init_lay();
}
