/*
 * This is a snake skin. 
 */
inherit "/std/leftover";

#include <macros.h>

void
create_leftover()
{
    set_name( ({"snake skin", "skin", "leftover"}) );
    set_pname( ({"skins", "leftovers"}) );
    set_adj(({"green","snake",}));
    set_short("green snake skin");
    set_pshort("green snake skins");
    set_long("This is the skin of a snake.\n");
 
    set_decay_time(1000);
    set_amount(1);
}

string
query_recover()
{
    return MASTER + ":" + "#ic#" + item_count + "#";
}

void
init_recover(string arg)
{
    int     ic;
    string  foo;

    sscanf(arg, "%s#ic#%d#", foo, ic);
    if (ic > 0)
        set_heap_size(ic);
}

