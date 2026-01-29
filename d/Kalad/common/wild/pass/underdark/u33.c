/*
 * /d/Kalad/common/wild/pass/underdark/u33.c
 * Purpose    : The world may never know
 * Located    : Dark Dominion beneath Hespyre Mts.
 * Created By : Antharanos
 * Modified By: Nikklaus, Oct'97: adapted to dark_dom inherit
 */

# pragma strict_types
# include "dark_dom.h"

inherit DARK_DOM;

void
create_dark_dom()
{
    create_tunnel();
    set_long(long()+
      "Dark passages lead to the northeast and southwest.\n");
    add_exit(DARK(u27), "northeast");
    add_exit(DARK(u36), "southwest");
}
