/* 
 * /d/Kalad/common/wild/pass/underdark/u46.c
 * Purpose    : For the sheer thrill of it. Don't make me do it again, tho...
 * Located    : Dark Dominion, beneath Hespyre
 * Created By : Antharanos
 * Modified By: Nikklaus, Oct'97: adapted to dark_dom inherits
 */

# pragma strict_types
# include "dark_dom.h"

inherit DARK_DOM;

void
create_dark_dom()
{
    create_tunnel();
    set_long(long()+
      "Dark passages lead to the northeast and south.\n");
    add_exit(DARK(u45), "northeast");
    add_exit(MIND(i1), "south", "@@cave_block");
}
