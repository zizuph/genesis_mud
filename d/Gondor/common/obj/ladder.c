/*
 *	/d/Gondor/common/obj/ladder.c
 *
 *	A ladder.
 *
 *	Olorin, 18-Oct-1995
 */
#pragma strict_types

inherit "/std/object.c";

#include "/d/Gondor/defs.h"

void
create_object()
{
    set_name("ladder");

    set_adj(({"wooden", "rickety", }));

    set_long(BSN("The rickety ladder was constructed by tying a "
      + "few wooden sticks together with some leather strings."));
}

void
leave_env(object from, object to)
{
    ::leave_env(from, to);

    if (query_no_show_composite())
        unset_no_show_composite();
}

