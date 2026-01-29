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
    proxim = (["forest":({0, "north"}),
               "river" :({2, "east"})]);
    mountains_hidden = 1;

    create_plain();
    
    add_my_desc(lay_desc, this_object());
    
    add_exit(PLAINS + "tfor_k_13","northwest",0,1,1);
    add_exit(PLAINS + "tfor_k_14","north",0,1,1);
    add_exit(PLAINS + "tfor_k_15","northeast",0,1,1);
    add_exit(PLAINS + "plains_28_2", "east");
    add_exit(PLAINS + "plains_26_2", "west");
}
public void
init()
{
    ::init();
    init_lay();
}
