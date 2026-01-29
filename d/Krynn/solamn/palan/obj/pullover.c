/* created by Aridor, 09/06/94 */

inherit "/std/armour";

#include <wa_types.h>

void
create_armour()
{
    set_name("pullover");
    set_adj("woolen");
    set_short("woolen pullover");
    set_long("This is a pullover made from wool. It's very thick " +
      "and warm and dyed in a blue-green color.\n");
    set_ac(7);
    set_at(A_TORSO);
}
