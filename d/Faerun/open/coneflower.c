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

#define FLOWER_NAME "coneflower"
#define ADJ1        "pale"
#define ADJ2        "purple"
#define FLOWER_ID   FLOWER_NAME + PROP_BASE



string
flower_long()
{
    return "This is a " + ADJ1 + " " + ADJ2 + " " + FLOWER_NAME + "." + CIT_THEY + "a single, drooping pale purple flower on top of a tall stem. The center is orange colored and looks like half a ball set on the center of the bloom. The petals are long and purple colored and surround the center.\n";
}

void
create_flower()
{
    set_heap_size(1);
    add_name(FLOWER_NAME);
    add_name("flower");
    add_name(FLOWER_ID);

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

