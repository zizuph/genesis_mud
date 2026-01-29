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
    proxim = (["river"  : ({0, "east"}),
               "harbour": ({0, "south"})]);
    extra = "Here, the river empties out into " +
        "harbour. ";

    create_plain();
    
    add_my_desc(lay_desc, this_object());
    
    add_exit(PLAINS + "plains_22_10", "north");
    add_exit(PLAINS + "plains_23_10", "northeast");
    add_exit(PLAINS + "plains_21_11", "west");
    add_exit(PLAINS + "plains_21_10", "northwest");
}
public void
init()
{
    ::init();
    init_lay();
}

