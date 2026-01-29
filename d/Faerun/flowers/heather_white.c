/*
 * A bunch of lavender heather
 * by Finwe, February 2005
 */


#include "/d/Faerun/defs.h"
#include "flowers.h"
#include <stdproperties.h>
#include <macros.h>

inherit "/std/heap";
inherit BASE_FLOWER;

#define FLOWER_NAME "heather"
#define ADJ1        "bunch"
#define ADJ2        "white"
#define FLOWER_ID   FLOWER_NAME + "_" + ADJ2 + PROP_BASE

string
flower_long()
{
    return "The " + ADJ1 + PLURAL + ADJ2 + " " + FLOWER_NAME +
        IS_ARE + "a group of branches bound together. The branches " +
        "are coverd with small green leaves. The small, cup-like, " + ADJ2 +
        " flowers cover the upper ends of each branch.\n";
}

void
create_flower()
{
    set_heap_size(1);
    add_name(FLOWER_NAME);
    add_name("flower");
    add_name(FLOWER_ID);

    set_adj(({ADJ1, ADJ2}));
    set_long(flower_long);
    set_short(ADJ1 + " of " + ADJ2 + " " + FLOWER_NAME);
    set_pshort(ADJ1+"es of " + ADJ2 + " " + FLOWER_NAME);

    set_fragrance(no);

    add_prop(HEAP_S_UNIQUE_ID, FLOWER_ID);
    add_prop(OBJ_M_NO_SELL, 1);
    add_prop(HEAP_I_UNIT_WEIGHT, 5);
    add_prop(HEAP_I_UNIT_VOLUME, 3);
    add_prop(HEAP_I_UNIT_VALUE, 20);
}    

