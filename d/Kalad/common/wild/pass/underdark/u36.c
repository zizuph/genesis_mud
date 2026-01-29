/*
 * /d/Kalad/common/wild/pass/underdark/u36.c
 * Purpose    : Best left unknown
 * Located    : Dark Dominion under Hespyre Mts.
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
      "Dark passages lead to the northeast, southeast and west.\n");
    add_exit(DARK(u33), "northeast");
    add_exit(DARK(u39), "southeast");
    add_exit(DARK(u35), "west");
}
