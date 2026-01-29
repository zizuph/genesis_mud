/**********************************************************************
 * - plains_11_8.c                                                  - *
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
    proxim = (["village": ({1, "southeast"}),
               "harbour": ({3, "south"})]);

    create_plain();
    
    add_my_desc(lay_desc, this_object());
    
    add_exit(PLAINS + "plains_12_8", "east");
    add_exit(PLAINS + "plains_12_9", "southeast");
    add_exit(PLAINS + "plains_11_9", "south");
}
public void
init()
{
    ::init();
    init_lay();
}