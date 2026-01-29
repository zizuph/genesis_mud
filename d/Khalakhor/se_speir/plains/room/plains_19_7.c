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
    proxim = (["village": ({2, "southwest"}),
               "harbour": ({4, "south"})]);

    create_plain();
    add_item(({"blanket", "lush grass", "grass", "soft grass"}), lay_desc);
    add_my_desc(lay_desc, this_object());
    
    add_exit(PLAINS + "plains_19_6", "north");
    add_exit(PLAINS + "plains_18_8", "southwest");
    add_exit(PLAINS + "plains_18_7", "west");
    add_exit(PLAINS + "plains_18_6", "northwest");
}
public void
init()
{
    ::init();
    init_lay();
}
