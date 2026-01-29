/*
 * A torch
 * Modified from Nick's torch by Amelia 11/23/97
 *
 */

inherit "/std/torch";

#include <macros.h>

void
create_torch()
{
    set_name("torch");
    set_pname("torches");
    set_adj("large");
    set_short("large torch");
    set_pshort("large torches");
    set_long("A large torch made from a wooden stick "+
        "with a rag soaked in pitch on one end. You can light it.\n");

    set_strength(2);
}

string
query_recover()
{
    return MASTER + ":" + query_torch_recover();
}

void
init_recover(string arg)
{
    init_torch_recover(arg);
}
