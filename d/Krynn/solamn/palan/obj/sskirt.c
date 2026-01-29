/* created by Aridor, 09/06/94 */

inherit "/std/armour";

#include <wa_types.h>

void
create_armour()
{
    set_name("skirt");
    set_adj("short");
    add_adj("red");
    set_short("short red skirt");
    set_long("A short red skirt, quite an attraction to the eye. " +
      "It falls down below the knees.\n");
    set_ac(3);
    set_at(A_LEGS);
}
