/*
 * /d/Kalad/common/wild/pass/underdark/u42.c
 * Purpose    : None of your business
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
      "Dark passages lead to the northeast, southeast, and northwest.\n");
    add_exit(DARK(u41), "northeast", "@@cave_block");
    add_exit(DARK(u43), "southeast");
    add_exit(DARK(u40), "northwest");
}
