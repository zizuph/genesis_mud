#pragma strict_types

#include "../esg_defs.h"

inherit "/std/weapon";
inherit ENHANCE_OBJECT;

public void
enter_env(object to, object from)
{
    ::enter_env(to, from);
    enhance_enter_env(to, from);
    if (!query_wf())
        set_wf();
}

public void
leave_env(object from, object to)
{
    ::leave_env(from, to);
    enhance_leave_env(from, to);
}

public int
wield(object ob = this_object())
{
    activate_bonus();
    return 0;
}

public int
unwield(object ob = this_object())
{
    deactivate_bonus();
    return 0;
}
