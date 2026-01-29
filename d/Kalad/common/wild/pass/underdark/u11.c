/* /d/Kalad/common/wild/pass/underdark/u11
 * Purpose    : Draw your own conclusions
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
      "Dark passages lead to the north, east and south.\n");
    add_exit(DARK(u12), "north");
    add_exit(DARK(u20), "east");
    add_exit(DARK(u10), "south");
}
