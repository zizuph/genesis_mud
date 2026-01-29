#pragma strict_types
#include "defs.h"
inherit "/std/heap";

string
block_long()
{
    return "The stone block" + ((num_heap() == 1) ? " is" : "s are") +
        " well cut and look ready to build something solid.\n";
}

public void
create_heap()
{
    set_heap_size(1);
    set_name(({"block", "_stone_block"}));
    set_adj("stone");
    set_short("stone block");
    set_long("@@block_long@@");

    add_prop(HEAP_S_UNIQUE_ID, MASTER_OB(TO));

    add_prop(HEAP_I_UNIT_VOLUME, 200); 
    add_prop(HEAP_I_UNIT_WEIGHT, 5000);
    add_prop(HEAP_I_UNIT_VALUE, SILVER_VALUE * 1);
}

