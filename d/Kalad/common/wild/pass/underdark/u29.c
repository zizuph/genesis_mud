/*
 * /d/Kalad/common/wild/pass/underdark/u29.c
 * Purpose    : Someone has to
 * Located    : Under Hespyre Mt. Range
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
      "Dark passages lead to the northwest and east.\n");
    add_exit(DARK(u23), "northwest");
    add_exit(DARK(u30), "east");
}
