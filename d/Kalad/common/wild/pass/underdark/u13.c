/* 
 * /d/Kalad/common/wild/pass/underdark/u13.c
 * Purpose    : Just another tunnel
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
      "Dark passages lead to the east and southwest.\n");
    add_exit(DARK(u14), "east");
    add_exit(DARK(u12), "southwest");
}
