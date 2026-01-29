/* 
 * /d/Kalad/common/wild/pass/underdark/u16.c
 * Purpose    : I'll give you three guesses
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
      "Dark passages lead to the northeast and southwest.\n");
    add_exit(DARK(u15), "southwest");
add_exit(DGNOME(s1), "northeast", "@@cave_block");
}
