/*
 * A torch
 * Modified from Nick's torch by Amelia 11/23/97
 */

#pragma strict_types

inherit "/std/torch";

#include <stdproperties.h>

public void
reset_torch()
{
    set_time(query_max_time());
}

public int
light_me_after_delay()
{
    remove_prop(TEMP_STDTORCH_CHECKED);
    add_prop(OBJ_I_LIGHT, 1);
    add_prop(OBJ_I_HAS_FIRE, 1);
    return 1;
}

public void
create_torch()
{
    set_name("torch");
    add_name("sconce");
    set_pname("torches");
    set_adj("large");
    add_adj("metal");
    set_short("large torch set in a metal sconce");
    set_long("This is a large torch set in a "+
        "metal sconce. When lit, it lights the dark tower hall.\n");
    add_prop(OBJ_M_NO_GET, 1);
}
