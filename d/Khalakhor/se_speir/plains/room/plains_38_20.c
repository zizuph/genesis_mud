/**********************************************************************
 * - Added a laying function so players can lay upon grass or some  - *
 * - other player.                                                  - *
 * - Modified by Damaris@Genesis 02/2005                            - *
 **********************************************************************/
#include "plains.h"
#include <macros.h>
inherit PLAINBASE;
#include "laying.c"
object marker;

public void
reset_room()
{
   //set number of honeysuckle flowers that can be picked
   marker->set_num_flowers(10);
}

public void
create_khalakhor_room()
{
    create_plain();

    add_exit(PLAINS + "plains_38_19", "north");
    add_exit(PLAINS + "plains_39_19", "northeast");
    add_exit(PLAINS + "plains_39_20", "east");
    add_exit(PLAINS + "plains_39_21", "southeast");
    add_exit(PLAINS + "plains_38_21", "south");
    add_exit(PLAINS + "plains_37_21", "southwest");
    add_exit(PLAINS + "plains_37_20", "west");
    add_exit(PLAINS + "plains_37_19", "northwest");
   
    add_my_desc(lay_desc, this_object());
    
    marker=clone_object(OBJ + "marker");
    marker->move(this_object());
    reset_room();
}
public void
init()
{
    ::init();
    init_lay();
}
