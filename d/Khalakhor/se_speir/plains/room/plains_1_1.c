/**********************************************************************
 * - Added add_fail()                                               - *
 * - Added a laying function so players can lay upon grass or some  - *
 * - other player.                                                  - *
 * - Modified by Damaris@Genesis 02/2005                            - *
 * - Added the connector to the road to the SW Speir                - *
 * - Tapakah, 09/2021                                               - *
 **********************************************************************/
#include "plains.h"

inherit PLAINBASE;
#include "laying.c"

void
create_khalakhor_room ()
{
    proxim = (["shore":({0, "west"}),
               "t_hills":({0, "north"})]);
    mountains_hidden = 1;

    create_plain();

    add_my_desc(lay_desc, this_object());
    
    add_exit(PLAINS + "plains_2_1", "east");
    add_exit(PLAINS + "plains_2_2", "southeast");
    add_exit(PLAINS + "plains_1_2", "south");
    add_exit(TO_SW + "path-22-5", "west");

}
void
init ()
{
    ::init();
    init_lay();
}
