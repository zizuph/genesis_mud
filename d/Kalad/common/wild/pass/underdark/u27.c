/*
 * /d/Kalad/common/wild/pass/underdark
 * Purpose    : Just because Anth was a mad code spawner
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
      "Dark passages lead to the northwest, east and southwest.\n");
    add_exit(DARK(u26), "northwest");
    add_exit(DARK(u28), "east");
    add_exit(DARK(u33), "southwest");
}
