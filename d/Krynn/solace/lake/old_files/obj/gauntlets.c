/* created by Splunge 01/94 */

inherit "/std/armour";
#include "/sys/wa_types.h"

void
create_armour()
{
    set_name("gauntlets");
    set_short("iron gauntlets");
    set_long("This is a pair of very solid iron gauntlets.\n");
    set_adj("iron");
    set_ac(8);
    set_am(({ -1, 4, -3 }));
    set_at(A_HANDS);
}

