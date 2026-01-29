#pragma strict_types
#include "defs.h"
inherit "/std/heap";

string
plank_long()
{
    return "The wooden plank" + ((num_heap() == 1) ? " is" : "s are") +
        " fresh, ready to build something.\n";
}

public void
create_heap()
{
    set_heap_size(1);
    set_name("plank");
    set_adj("wooden");
    set_short("wooden plank");
    set_long("@@plank_long@@");

    add_prop(HEAP_S_UNIQUE_ID, MASTER_OB(TO));

    add_prop(HEAP_I_UNIT_VOLUME, 200); 
    add_prop(HEAP_I_UNIT_WEIGHT, 1000);
    add_prop(HEAP_I_UNIT_VALUE, COPPER_VALUE * 6);
}

