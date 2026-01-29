/*
 * /d/Kalad/common/wild/pass/underdark/u40.c
 * Purpose    : Cause they said it could never be done
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
      "Dark passages lead to the north and southeast.\n");
    add_exit(DARK(u39), "north");
    add_exit(DARK(u42), "southeast");
}
