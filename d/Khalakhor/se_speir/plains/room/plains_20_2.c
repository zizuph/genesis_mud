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
    proxim = (["forest":({0, "north"})]);
    mountains_hidden = 1;

    create_plain();
    add_item(({"blanket", "lush grass", "grass", "soft grass"}), lay_desc);
    add_my_desc(lay_desc, this_object());
    
    add_exit(PLAINS + "tfor_k_06",   "northwest",0,1,1);
    add_exit(PLAINS + "tfor_k_07",   "north",0,1,1);
    add_exit(PLAINS + "tfor_k_08",   "northeast",0,1,1);
    add_exit(PLAINS + "plains_21_2", "east");
    add_exit(PLAINS + "plains_19_2", "west");
}
public void
init()
{
    ::init();
    init_lay();
}
