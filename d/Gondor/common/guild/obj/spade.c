/*
 * /d/Gondor/common/guild/obj/spade.c
 *
 * Spade to dig worms with.
 *
 * Coded by Gwyneth on June 4, 2000
 */

inherit "/std/object";
inherit "/lib/holdable_item";

#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>

#include "/d/Gondor/defs.h"

void
create_object()
{
    set_name("spade");
    add_name("regrowth_spade");

    set_adj("small");

    set_short("small spade");
    set_pshort("small spades");

    set_long("A small spade commonly used to dig in the earth.\n");

    set_slots(W_ANYH);

    add_prop(OBJ_I_VALUE, 50);
    add_prop(OBJ_I_WEIGHT, 150);
    add_prop(OBJ_I_VOLUME, 75);
}

void
leave_env(object from, object to)
{
    ::leave_env(from, to);

    holdable_item_leave_env(from, to);
}

void
appraise_object(int num)
{
    ::appraise_object(num);

    appraise_holdable_item();
}
