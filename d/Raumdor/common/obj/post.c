#pragma strict_types
#include "defs.h"
inherit "/std/heap";

string
post_long()
{
    return "The wooden post" + ((num_heap() == 1) ? " is" : "s are") +
        " solid, capable of supporting something heavy.\n";
}

public void
create_heap()
{
    set_heap_size(1);
    set_name("post");
    set_adj("wooden");
    set_short("wooden post");
    set_long("@@post_long@@");

    add_prop(HEAP_S_UNIQUE_ID, MASTER_OB(TO));

    add_prop(HEAP_I_UNIT_VOLUME, 300); 
    add_prop(HEAP_I_UNIT_WEIGHT, 1500);
    add_prop(HEAP_I_UNIT_VALUE, COPPER_VALUE * 9);
}

