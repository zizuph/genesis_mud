/* new boots*/
#pragma strict_types
inherit "std/armour";
#include "/sys/wa_types.h"
#include "../local.h"
 
void
create_armour()
{
    set_name("sandals");
    set_adj("well-worn");
    add_adj("erdlu-hide");
    set_short("pair of well-worn erdlu-hide sandals");
    set_pshort("pairs of well-worn erdlu-hide sandals");
    set_long("A pair of simple sandals, made from erdlu-hide.\n");
 
    set_ac(2);
    set_at(A_FEET);
}
