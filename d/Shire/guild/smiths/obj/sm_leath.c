/*
 * 2021-01-21 - Cotillion
 * - Converted to heap
 */
inherit "/std/heap";

#include <stdproperties.h>
#include <macros.h>
#include "/d/Shire/common/defs.h"
#include "smiths.h"

#define ITEM_TYPE "leather"

int smiths_item_bonus=LEATHER;    // == 0

void
create_heap() {
    set_heap_size(1);

    set_name(({"leather","smiths_leather"}));
    set_pname("leathers");

    set_long("This piece of leather is useful for wrapping the hilts of"+
        " weapons and in the making of armours.\n");

    add_prop(HEAP_I_UNIT_WEIGHT, 200);
    add_prop(HEAP_I_UNIT_VOLUME, 300);
    add_prop(HEAP_I_UNIT_VALUE, 20);

    add_prop(HEAP_S_UNIQUE_ID, "_smith_leather");
}

string
query_smiths_item() {
    return ITEM_TYPE;
}

