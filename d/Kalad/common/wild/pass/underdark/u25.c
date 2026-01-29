/*
 * /d/Kalad/common/wild/pass/underdark/u25.c
 * Purpose    : Why are any of us here?
 * Located    : Under Hespyre Mts.
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
      "Dark passages lead to the east and southeast.\n");
    add_exit(DARK(u24), "east");
    add_exit(DARK(u28), "southeast");
}
