// file name:   vines_sh.c
// creator(s):  Zielia  2006
// last update:
// purpose: Traps players who are foolish enough to attack Maree.
// note:
// bug(s):
// to-do: Change alarm time
#pragma strict_types

#include "zigg.h"
#include <macros.h>
#include <living_desc.h>
#include <stdproperties.h>

inherit "/std/shadow";

private static string xtr;
private static int temp;
private static object trap;

/* Try to cleanly handle shadow removal. */
public void
remove_shadow(void)
{
    shadow_who->remove_prop(LIVE_S_EXTRA_SHORT);

    shadow_who->catch_tell("The vines that were holding you finally let "+
	"go as they wither and fall away.\n");
    tell_room(environment(shadow_who), "The vines holding "+
	QTNAME(shadow_who) +" wither and fall away.\n", shadow_who,
	shadow_who);

    if (xtr)
	shadow_who->add_prop(LIVE_S_EXTRA_SHORT, xtr);

    ::remove_shadow();
}

public void
remove_trap_shadow(void)    { remove_shadow(); }

public void
set_trapped_object(object ob)  { trap = ob; }

public object
query_trapped_object(void)     { return trap; }

public varargs int
shadow_me(mixed to_shadow)
{
    if (::shadow_me(to_shadow))
    {
	if (shadow_who->query_prop(LIVE_S_EXTRA_SHORT))
        {
	    xtr = shadow_who->query_prop(LIVE_S_EXTRA_SHORT);
        }
	shadow_who->add_prop(LIVE_S_EXTRA_SHORT, ", ensnared by thick, "+
	"thorny vines");
	set_alarm(420.0, 0.0, &remove_trap_shadow());
	return 1;
    }

    return 0;
}

public int
remove_object(void)
{
    temp = 1;
    set_alarm(0.0, 0.0, &remove_trap_shadow());
    return shadow_who->remove_object();
}


