
/*
\ * whiskey.c
 * The drunk sailor's whiskey stash
 * Gulfport
 * Tibbit, 1 May 1998
 */

inherit "/std/drink";
#include <stdproperties.h>

create_drink()
{
    set_name("whiskey");
    set_adj("whiskey");
    set_long("This bottle contains a quanitity of "+
        "whiskey, extremely dark in color (and, therefore, "+
        "heady in taste).\n");

    set_soft_amount(295);
    set_alco_amount(20);
    add_prop(OBJ_I_WEIGHT, 330);
    add_prop(OBJ_I_VOLUME, 330);
}
