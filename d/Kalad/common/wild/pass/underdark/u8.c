/* 
 * /d/Kalad/common/wild/pass/underdark/u8.c
 * Purpose    : dark dominion tunnels
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
    set_short("Tunnel");
    set_long(long()+"You find yourself within a wide tunnel, sides sloping towards "+
      "the top. The rough, irregular walls mark this passageway as natural, "+
      "as opposed to having been carved out by someone, or something. Dark "+
      "passages lead to the west and east.\n");
    add_item(({"sides","side","irregular walls","walls","wall"}),"The "+
      "walls are nothing but bare uncut stone.\n");
    add_exit(DARK(u7), "west");
    add_exit(DARK(u9), "east", 0);
}
