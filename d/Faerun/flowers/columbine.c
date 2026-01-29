/*
 * Flower
 * by Finwe, September 2006
 */


#include "/d/Faerun/defs.h"
#include "flowers.h"
#include <stdproperties.h>
#include <macros.h>

inherit "/std/heap";
inherit BASE_FLOWER;

//#define IS_ARE      ((num_heap() == 1) ? " is " : "s are ")
//#define IT_THEY     ((num_heap() == 1) ? " it is " : "they are ")
//#define CIT_THEY    ((num_heap() == 1) ? " It is " : "They are ")

// Is this flower fragrant? yes or no
#define FRAGRANT    no

#define FLOWER_NAME "columbine"
#define ADJ1        "long"
#define ADJ2        "pink"
#define FLOWER_ID   FLOWER_NAME + PROP_BASE




string
flower_long()
{
    return "The " + ADJ1 + " " + ADJ2 + " " + FLOWER_NAME + IS_ARE + "a unique flower. It has a fascinating hollow spur-like blossom that appear to be two flowers in one; an inner white flower that is surrounded by an elegantly spurred red outer flower.\n";
}

void
create_flower()
{
    set_heap_size(1);
    set_name(({FLOWER_NAME, "flower", FLOWER_ID}));

    set_adj(({ADJ1, ADJ2}));

    set_short(ADJ1 + " " + ADJ2 + " " + FLOWER_NAME);
    set_long(flower_long);
    add_prop(HEAP_S_UNIQUE_ID, FLOWER_ID);
    set_fragrance(FRAGRANT);

    add_prop(OBJ_M_NO_SELL, 1);

    add_prop(HEAP_I_UNIT_WEIGHT, 5);
    add_prop(HEAP_I_UNIT_VOLUME, 3);
    add_prop(HEAP_I_UNIT_VALUE, 20);
}    

