/*
 * /d/Kalad/common/wild/pass/underdark/u14
 * Purpose    : There have to be a reason?
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
    set_long(long()+
      "You've reached a branching point of tunnels, where "+
      "dark passages lead to the east, south and west.\n");
    add_exit(DARK(u15), "east");
    add_exit(DARK(u18), "south");
    add_exit(DARK(u13), "west");
}
