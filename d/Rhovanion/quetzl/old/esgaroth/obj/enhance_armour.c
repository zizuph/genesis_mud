#pragma strict_types

#include "../esg_defs.h"

inherit "/std/armour";
inherit ENHANCE_OBJECT;

public void
enter_env(object to, object from)
{
    ::enter_env(to, from);
    enhance_enter_env(to, from);
    if (!query_af())
        set_af();
}

public void
leave_env(object from, object to)
{
    ::leave_env(from, to);
    enhance_leave_env(from, to);
}

public int
wear(object ob = this_object())
{
    activate_bonus();
    return 0;
}

public int
remove(object ob = this_object())
{
    deactivate_bonus();
    return 0;
}
