/* created by Aridor, 09/06/94 */

inherit "/std/armour";

#include <wa_types.h>

void
create_armour()
{
    set_name("shirt");
    set_adj("cotton");
    set_short("thin cotton shirt");
    set_long("A thin cotton shirt, perfect for warm days.\n");
    set_ac(3);
    set_at(A_TORSO);
}
