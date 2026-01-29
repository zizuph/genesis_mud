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
    proxim = (["forest":({3, "north"})]);

    create_plain();
    add_item(({"blanket", "lush grass", "grass", "soft grass"}), lay_desc);
    add_my_desc(lay_desc, this_object());
    
    add_exit(PLAINS + "plains_20_5", "southeast");
    add_exit(PLAINS + "plains_19_5", "south");
    add_exit(PLAINS + "plains_18_5", "southwest");
    add_exit(PLAINS + "plains_18_4", "west");
    add_exit(PLAINS + "plains_18_3", "northwest");
}
public void
init()
{
    ::init();
    init_lay();
}
