/* 
 * /d/Kalad/common/wild/pass/underdark/u9
 * Purpose    : Why is anything here?
 * Located    : Under Hespyre Mts.
 * Created By : Antharanos
 * Modified By: Nikklaus, Aug'97: Adapted to dark_dom inherit
 */

# pragma strict_types
# include "dark_dom.h"

inherit DARK_DOM;

public void
create_dark_dom()
{
    create_tunnel();
    set_long(long()+"You've reached a branching point where "+
      "dark passages lead to the northeast, west and southeast.\n");
    add_exit(DARK(u10), "northeast");
    add_exit(DARK(u8), "west");
    add_exit(DARK(u34), "southeast");
}
