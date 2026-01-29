inherit "/std/object";
inherit "/lib/holdable_item";

#include <wa_types.h>

public void
create_object()
{
    set_name("fork");

    set_long("It is a silver fork.\n");

    set_slots(W_ANYH);
}

public void
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
