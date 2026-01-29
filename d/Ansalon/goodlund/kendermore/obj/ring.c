/* Emerald ring for Kendermore, Gwyneth, June 1999 */

inherit "/std/armour";

#include "/sys/wa_types.h"
#include "/sys/formulas.h"
#include "/sys/stdproperties.h"

void
create_armour()
{
    set_name("ring");
    set_adj("emerald");
    set_short("emerald ring");
    set_long("This is a dazzling emerald ring. It looks like a family " + 
        "heirloom\n");

    set_ac(0);
    set_at(A_ANY_FINGER);
    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 100);
    add_prop(OBJ_I_VALUE, 1500);
}

