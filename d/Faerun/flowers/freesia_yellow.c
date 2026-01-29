/*
 * Yellow Freesia
 * by Finwe, February 2005
 */


#include "/d/Faerun/defs.h"
#include "flowers.h"
#include <stdproperties.h>
#include <macros.h>

inherit "/std/heap";
inherit BASE_FLOWER;

#define FLOWER_NAME "freesia"
#define ADJ1        "fragrant"
#define ADJ2        "yellow"
#define FLOWER_ID   FLOWER_NAME + "_" + ADJ2 + PROP_BASE

string
flower_long()
{
    return "The " + ADJ1 + " " + FLOWER_NAME + IS_ARE +  ADJ2 + " colored " +   
        "with trumpet shaped flowers on long stalks. Each flower is about " +
        "the length of a finger. They are delicate looking with fluted edges " +
        "and pale, yellow throats. The stalks are flexible and covered " +
        "with many flowers.\n";

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

