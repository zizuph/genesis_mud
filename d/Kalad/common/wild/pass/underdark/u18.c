/* /d/Kalad/common/wild/pass/underdark/u18.c
 * Purpose    : Same as the last 17 u rooms.
 * Located    : Under Hespyre Mts.
 * Created By : Antharanos
 * Modified By: Nikklaus, Oct'97: adapted to dark_dom
 * /
 */

# pragma strict_types
# include "dark_dom.h"

inherit DARK_DOM;

void
create_dark_dom()
{
    set_long(long()+
      "Dark passages lead to the north and south.\n");
    add_exit(DARK(u21), "south");
    add_exit(DARK(u14), "north");
}
