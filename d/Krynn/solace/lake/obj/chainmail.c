/* created by Splunge 01/94 */

inherit "/std/armour";

#include <macros.h>

void
create_armour()
{
    set_name("chainmail");
    set_short("dull war-torn chainmail");
    set_adj("sturdy");
    add_adj("war-torn");
    set_long("This is a sturdy, but war-torn chainmail.\n");
    set_default_armour(22);
}
