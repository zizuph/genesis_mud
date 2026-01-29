/*  lake/wep/oar.c cloned by lake/npc/slave.c */
inherit "/std/object";
inherit "/lib/holdable_item";

#include <stdproperties.h>
#include <wa_types.h>

public void
create_object()
{
    set_name("oar");
    add_adj("rowing");
    set_long("It is a finely crafted oar.\n");

    set_slots(W_BOTH);

    add_prop(OBJ_I_VALUE, 10);
}

public void
leave_env(object env, object to)
{
    ::leave_env(env, to);
    holdable_item_leave_env(env, to);
}

public void
appraise_object(int num)
{
    ::appraise_object(num);
    write(holdable_item_usage_desc());
}
