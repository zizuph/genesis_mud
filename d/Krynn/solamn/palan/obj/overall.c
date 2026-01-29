/* created by Aridor, 09/06/94 */

inherit "/std/armour";

#include <wa_types.h>

void
create_armour()
{
    set_name("overall");
    set_adj("dirty");
    add_adj("blue");
    set_short("dirty blue overalls");
    set_long("It's the common overall of the harbour workers.\n");
    set_ac(5);
    set_at(A_ROBE);
}
