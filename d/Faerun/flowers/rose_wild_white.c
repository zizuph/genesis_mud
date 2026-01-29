/*
 * A wild rose
 * by Finwe, June 2007
 */


#include "/d/Faerun/defs.h"
#include "flowers.h"
#include <stdproperties.h>
#include <macros.h>

inherit "/std/heap";
inherit BASE_FLOWER;

#define FLOWER_NAME "rose"
#define ADJ1        "wild"
#define ADJ2        "white"
#define FLOWER_ID   FLOWER_NAME + "_" + ADJ1 + "_" + ADJ2 + PROP_BASE

string
flower_long()
{
    return "The " + short() + IS_ARE + "large and fragrant with a showy, " +
        "yellow center. The five petals are slightly curled at the edges." + 
        CIT_THEY + "long stemmed with sharp thorns, and some small, sawtoothed " +
        "leaves.\n";
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
    set_short(ADJ1 + " " + ADJ2 + " " + FLOWER_NAME);
    add_prop(HEAP_S_UNIQUE_ID, FLOWER_ID);

    set_fragrance(yes);

    add_prop(OBJ_M_NO_SELL, 1);
    add_prop(HEAP_I_UNIT_WEIGHT, 5);
    add_prop(HEAP_I_UNIT_VOLUME, 3);
    add_prop(HEAP_I_UNIT_VALUE, 20);
}    

