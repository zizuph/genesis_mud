/* body_pad: Padded shirt for body armor.... */
inherit "/std/armour";
#include "/sys/wa_types.h"
#include "defs.h"

void create_armour()
{
    set_name("shirt");
    set_short("padded shirt");
    set_long("Woven of tough hair from Atha's native giant population, "+
             "this shirt should be able to absorb all sorts of damage.\n");
    set_adj("padded");

    set_ac(20);
    set_am(({ -4,  1,  3}));
    set_at(A_BODY);

    add_prop(OBJ_I_WEIGHT, 2250);
    add_prop(OBJ_I_VOLUME, 1125);
}
