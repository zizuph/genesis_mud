inherit "/std/container";

#include "/d/Shire/sys/defs.h"
#include "defs.h"
#include <stdproperties.h>

void
create_container()
{
    set_name("basket");
    set_pname("baskets");
    set_adj("wooden");
    set_short("wooden basket");
    set_pshort("wooden baskets");
    set_long("A wooden basket for holding apples.\n");

    add_prop(CONT_I_WEIGHT, 250);       /* It weights 250 grams */
    add_prop(CONT_I_MAX_WEIGHT, 2250);  /* It can hold 2000 grams of weight. */
    add_prop(CONT_I_VOLUME, 30);        /* Only 30 ml volume (very small) */
    add_prop(CONT_I_MAX_VOLUME, 2030);  /* 2 litres of volume */

    add_prop(OBJ_I_VALUE, 40);          /* Worth 40 cc */
}
