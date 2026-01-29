/*
 * /d/Kalad/common/wild/pass/underdark/u24.c
 * Purpose    : For no sake at all.
 * Location   : Under Hespyre Mts.
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
      "Dark passages lead to the east and west.\n");
    add_exit(DARK(u23), "east");
    add_exit(DARK(u25), "west");
    set_noshow_obvious(1);
}
