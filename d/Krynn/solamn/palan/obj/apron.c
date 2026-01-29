/* created by Aridor, 09/06/94 */

inherit "/std/armour";

#include <wa_types.h>

void
create_armour()
{
    set_name("apron");
    set_adj("flour");
    add_adj("covered");
    add_adj("bright");
    add_adj("red");
    set_short("flour covered bright red apron");
    set_long("This used to be a bright red apron, but now it is " +
      "all covered with flour and you can hardly see any " +
      "color.\n");
    set_ac(3);
    set_at(A_ROBE);
}
