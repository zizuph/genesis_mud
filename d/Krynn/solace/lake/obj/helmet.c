/* created by Splunge 01/94 */

inherit "/std/armour";
#include "/sys/wa_types.h"

void
create_armour()
{
    set_name("helmet");
    set_short("black helmet");
    set_long("This is a rather non-descript black helmet.\n");
    set_adj("black");
    set_ac(7);
    set_am(({ -4, 5, -1 }));
    set_at(A_HEAD);
}
