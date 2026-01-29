/*
 * /d/Kalad/common/wild/pass/underdark/u39.c
 * Purpose    : to get the players grungy and confused
 * Located    : Dark Dominion, under Hespyre Mts.
 * Created By : Antharanos
 * Modified By: Nikklaus, Oct'97: adapted to dark_dominion inherit
 */

# pragma strict_types
# include "dark_dom.h"

inherit DARK_DOM;

void
create_dark_dom()
{
    create_tunnel();
    set_long(long()+
      "Dark passages lead to the northwest and south.\n");
    add_exit(DARK(u36), "northwest");
    add_exit(DARK(u40), "south");
}
