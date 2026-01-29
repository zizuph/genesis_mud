/* created by Aridor, 09/06/94 */

inherit "/std/armour";

#include <wa_types.h>

void
create_armour()
{
    set_name("skirt");
    set_adj("long");
    set_adj("brown");
    set_short("long brown skirt");
    set_long("This long skirt reaches down to the feet. It is of " +
      "mud brown color.\n");
    set_ac(4);
    set_at(A_LEGS);
}
