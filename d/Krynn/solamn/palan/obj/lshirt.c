/* created by Aridor, 09/06/94 */

inherit "/std/armour";

#include <wa_types.h>

void
create_armour()
{
    set_name("shirt");
    set_adj("linen");
    set_short("linen shirt");
    set_long("This is an ordinary linen shirt. It looks a little crude, " +
      "but can still protect some.\n");
    set_ac(5);
    set_at(A_TORSO);
}
