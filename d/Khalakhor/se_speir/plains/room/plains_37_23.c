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
    create_plain();
   
    add_my_desc(lay_desc, this_object());
    
    add_exit(PLAINS + "plains_37_22", "north");
    add_exit(PLAINS + "plains_38_22", "northeast");
    add_exit(PLAINS + "plains_38_23", "east");
    add_exit(PLAINS + "plains_38_24", "southeast");
    add_exit(PLAINS + "plains_37_24", "south");
}
public void
init()
{
    ::init();
    init_lay();
}
