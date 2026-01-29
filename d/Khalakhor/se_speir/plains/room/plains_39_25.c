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
    
    add_exit(PLAINS + "plains_39_24", "north");
    add_exit(PLAINS + "plains_40_24", "northeast");
    add_exit(PLAINS + "plains_40_25", "east");
    add_exit(PLAINS + "plains_39_26", "south");
    add_exit(PLAINS + "plains_38_25", "west");
    add_exit(PLAINS + "plains_38_24", "northwest");
}
public void
init()
{
    ::init();
    init_lay();
}
