#pragma strict_types
#include "defs.h"
inherit "/std/heap.c";

string
nail_long()
{
    return "The iron nail" + ((num_heap() == 1) ? " is" : "s are") +
        " sharp and straight, suitable for assembling things with wood.\n";
}

public void
create_heap()
{
    set_heap_size(1);
    set_name("nail");
    set_adj("iron");
    set_short("iron nail");
    set_long("@@nail_long@@");

    add_prop(HEAP_S_UNIQUE_ID, MASTER_OB(TO));

    add_prop(HEAP_I_UNIT_VOLUME, 1);
    add_prop(HEAP_I_UNIT_WEIGHT, 1);
    add_prop(HEAP_I_UNIT_VALUE, COPPER_VALUE);
}
