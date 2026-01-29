/*
 * /d/Kalad/common/wild/pass/underdark/u34.c
 * Purpose    : Another stretch of tunnel to trudge through
 * Located    : Dark Dominion beneath Hespyre Mt.s
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
      "Dark passages lead to the northwest and southwest.\n");
    add_exit(DARK(u9), "northwest");
    add_exit(DARK(u35), "southwest");
}
