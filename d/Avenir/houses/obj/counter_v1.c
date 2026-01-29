/*
 * counter_v1.c
 *
 * Lilith, Feb 2022
 */

#pragma strict_types
#pragma save_binary 

#include "../defs.h"
#include <macros.h>
#include <composite.h>
#include <filter_funs.h>
#include <stdproperties.h>

inherit HOBJ +"table_base";

public void
create_table()
{
	::create_table();
    set_adj("onyx");
    add_adj("white");
    set_name("counter");
    set_long("This counter is made of the same white onyx as " +
        "the rest of the house. It runs along most of the "+
        "length of the southern wall until it meets up with " +
        "the pantry. It looks like a convenient place to do " +
        "food preparation.\n");

    set_describe_prefix("Along the southern wall is counter made of "+
        "white onyx");
	
    add_prop(CONT_I_VOLUME, 10000);
    add_prop(CONT_I_WEIGHT, 10000);
    add_prop(CONT_I_MAX_VOLUME, 100000);
    add_prop(CONT_I_MAX_WEIGHT, 100000);
    add_prop(OBJ_M_NO_GET, 1);
    add_prop(CONT_I_ATTACH, 1);
}
