/*
 * /d/Kalad/common/wild/pass/underdark/u44.c
 * Purpose    : It was too late to stop
 * Located    : Dark Dominion, Under Hespyre Mts.
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
    add_exit(DARK(u45), "southeast");
    add_exit(DARK(u43), "west");
}
