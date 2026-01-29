/* 
 * /d/Kalad/common/wild/pass/underdark/u21.c
 * Purpose    : I'll never tell
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
      "Dark passages lead to the north, east and southwest.\n");
    add_exit(DARK(u18), "north");
    add_exit(DARK(u22), "east");
    add_exit(DARK(u26), "southwest");
}
