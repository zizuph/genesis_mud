// slow_obj ("octo_slow.c")
// creator(s):   Zielia 2008
// last update:
// purpose:      Slow object for port octopus tentacles
// note:
// bug(s):
// to-do:
// 7/24/2022 Ckrik - removed the delayed call of slow_me() that is likely
//     the source of a haste effect bug. There is no reason for the 0.1
//     delayed call via set_alarm().
#pragma strict_types

inherit "/std/object";

#include <macros.h>
#include <stdproperties.h>
#include "/d/Avenir/include/basic.h"

private static object ob;

public void
create_object(void)
{
    setuid();
    seteuid(getuid());

    set_no_show();
    set_name(({"slow_obj","octo::slow"}));
}

private void
slow_me(void)
{
    ALTER_PROP(ENV(TO), LIVE_I_QUICKNESS, -50);
}

private void
unslow_me(void)
{
    ALTER_PROP(ENV(TO), LIVE_I_QUICKNESS, 50);
}

public void
remove_object()
{
    if (IS_CLONE)
    {
	   unslow_me();
    }

    ::remove_object();
}

public void
enter_env(object to, object from)
{
    ::enter_env(to, from);

    if (!IS_CLONE)
	   return;

    slow_me();
}

public string
query_recover(void)	{ return 0; }
