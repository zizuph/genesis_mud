/* head_lth: A leather cap: Not as good as hide, but...... */
inherit "/std/armour";
#include "/sys/wa_types.h"
#include "defs.h"

void create_armour()
{
    set_name("cap");
    set_short("worn leather cap");
    set_long("A common piece of light headwear, the cap has a wide brim "+
             "to keep eyes free from the blinding sun.\n");
    set_adj("worn");
    add_adj("leather");

    set_ac(15);
    set_am(({ -2, 0, 2}));
    set_at(A_HEAD);

    add_prop(OBJ_I_WEIGHT, 450);
    add_prop(OBJ_I_VOLUME, 225);
}
