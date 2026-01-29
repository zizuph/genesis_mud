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

// Is this flower fragrant? yes or no
#define FRAGRANT    yes

#define FLOWER_NAME "milkweed"
#define ADJ1        "fragrant"
#define ADJ2        "common"
#define FLOWER_ID   FLOWER_NAME + PROP_BASE

string
flower_long()
{
    return "This is a " + ADJ1 + " " + ADJ2 + " " +  FLOWER_NAME + " flower." +CIT_THEY + "a large cluster of small trumpet-like flowers. They are sweet-scented and lavendar colored.\n";
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

