/* created by Aridor, 09/06/94 */

inherit "/std/armour";

#include <wa_types.h>

void
create_armour()
{
    set_name("shirt");
    set_adj("woolen");
    set_short("woolen shirt");
    set_long("A warm woolen shirt, very comfortable, too.\n");
    set_ac(8);
    set_at(A_TORSO);
}
