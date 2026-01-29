/*
 * /d/Kalad/common/wild/pass/underdark/u23.c
 * Purpose    : Because it can be done
 * Located    : Dark Dominion, beneath Hespyre Mts.
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
      "Dark passages lead to the southeast and west.\n");
    add_exit(DARK(u29), "southeast");
    add_exit(DARK(u24), "west");
}
