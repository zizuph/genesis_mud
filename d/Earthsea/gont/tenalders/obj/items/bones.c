#pragma strict_types

inherit "/std/object";
inherit "/lib/holdable_item";
inherit "/lib/keep";

#include <stdproperties.h>
#include <wa_types.h>

public void
create_object()
{
    set_name("bones");
    add_name("bone");
    add_name("drumstick");
    add_name("drumsticks");
    add_name("stick");
    add_name("sticks");
    add_name("__es_bonesman_bones__");
    set_adj(({"pair", "of", "bone", "drum"}));
    set_short("pair of bones");
    set_long("A set of bones used as drumsticks.\n");
    set_slots(W_BOTH);
    add_prop(OBJ_I_WEIGHT, 90);
    add_prop(OBJ_I_VOLUME, 75);
    add_prop(OBJ_I_VALUE, 50);
}

public void
leave_env(object from, object to)
{
    ::leave_env(from, to);
    holdable_item_leave_env(from, to);
}

public void
appraise_object(int num)
{
    ::appraise_object(num);

    appraise_holdable_item();
}
