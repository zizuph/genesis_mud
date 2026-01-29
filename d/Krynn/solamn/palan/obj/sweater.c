/* created by Aridor, 09/06/94 */

inherit "/std/armour";

#include <wa_types.h>

void
create_armour()
{
    set_name("sweater");
    set_adj("cotton");
    set_short("cotton sweater");
    set_long("This is a sweater made from cotton. Like all undyed cotton, " +
      "this sweater is of a greyish dirty looking color.\n");
    set_ac(5);
    set_at(A_TORSO);
}
