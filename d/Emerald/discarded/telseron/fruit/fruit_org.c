/*
 * FRUIT.c
 * This is a base fruit file. Call set_fruit(#) to change
 * what fruit it is.
 */

#include "/d/Emerald/defs.h"
#include "fruit.h"

inherit STDFRUIT;

void set_fruit(int f);

void
create_food()
{
    set_name("fruit");
    set_adj("meaningless");
    set_long("Tis an amorphous blob vaguely resembling a fruit.\n");
    set_amount(10);

}

void
set_fruit(int f)
{
    set_name(FRUIT_NAMES[f]);
    set_adj(FRUIT_ADJ[f]);
    set_long(FRUIT_LONGS[f] + "\n");
    set_amount(FRUIT_AMOUNTS[f]);

    add_prop(OBJ_I_WEIGHT, FRUIT_WEIGHTS[f]);
    add_prop(OBJ_I_VOLUME, FRUIT_VOLUMES[f]);
}
