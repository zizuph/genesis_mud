/*
 * /d/Kalad/common/wild/pass/underdark/u12
 * Purpose    : Dunno, just found it sitting here
 * Located    : Under Hespyre Mts.
 * Created By : Antharanos
 * Modified By: Nikklaus, Oct'97: adapted to dark_dom
 */

# pragma strict_types
# include "dark_dom.h"

inherit DARK_DOM;

void
create_dark_dom()
{
    create_tunnel();
    set_long(long()+
      "Dark passages lead to the northeast and south.\n");
    add_exit(DARK(u13), "northeast");
    add_exit(DARK(u11), "south");
}
