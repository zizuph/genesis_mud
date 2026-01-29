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
    
    add_exit(PLAINS + "plains_37_19", "north");
    add_exit(PLAINS + "plains_38_19", "northeast");
    add_exit(PLAINS + "plains_38_20", "east");
    add_exit(PLAINS + "plains_38_21", "southeast");
    add_exit(PLAINS + "plains_37_21", "south");
    add_exit(PLAINS + "plains_36_20", "west");
    add_exit(PLAINS + "plains_36_19", "northwest");
}
public void
init()
{
    ::init();
    init_lay();
}
