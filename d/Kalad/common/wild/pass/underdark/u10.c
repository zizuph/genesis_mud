/*
 * /d/Kalad/common/wild/pass/underdark/u10
 * Purpose    :
 * Located    : Under Hespyre Mts.
 * Created By : Antharanos
 * Modified By: Nikklaus, Oct'97: Adaped to dark_dom inherit
 */

# pragma strict_types
# include "dark_dom.h"

inherit DARK_DOM;

public void
create_dark_dom()
{
    create_tunnel();
    set_long(long()+
      "Dark passages lead to the north and southwest.\n");
    add_exit(DARK(u9), "southwest");
    add_exit(DARK(u11), "north");
}
