/*
 * /d/Krynn/common/potions/quenta_object.c
 *
 * Teth, Feb 1997, modified from Olorin's old invis_object.
 */
#pragma strict_types

inherit "/std/object";

#include <macros.h>
#include <poison_types.h>
#include <ss_types.h>

#include "/d/Krynn/common/defs.h"

int old_prop;
static int     time = 1;

void
create_object()
{
    set_name("Quenta_Invis_Object");

    add_prop(OBJ_I_VOLUME, 0);
    add_prop(OBJ_I_WEIGHT, 0);
    add_prop(OBJ_I_NO_DROP, 1);
    add_prop(OBJ_I_NO_GIVE, 1);

    set_no_show();
}

void
set_duration(int i)
{
    time = i;
}

void
end_effect()
{
    object  ob = E(TO),
    poison;

    if (ob->query_invis())
    {
        ob->add_prop(LIVE_I_SEE_DARK, ((ob->query_prop(LIVE_I_SEE_DARK)) + 30));
        ob->add_prop(OBJ_I_INVIS, ((ob->query_prop(OBJ_I_INVIS)) -1));
        ob->catch_msg("You are visible, and can see again!\n");
        tell_room(E(ob), QCTNAME(ob) + " appears out of nowhere!\n", ob, ob);
        set_alarm(0.0, 0.0, remove_object);

    }
}

void
enter_env(object to, object from)
{
    ::enter_env(to, from);

    if (!objectp(to) || !living(to))
    {
        set_alarm(0.0, 0.0, remove_object);
        return;
    }

    if (to->query_invis())
    {
        to->catch_msg("Nothing seems to happen\n");
        set_alarm(0.0, 0.0, remove_object);
        return;
    }

    to->catch_msg("You are now invisible... but blinded!\n");
    tell_room(E(to), QCTNAME(to) + " vanishes!\n", to, to);
    to->add_prop(OBJ_I_INVIS, ((query_prop(OBJ_I_INVIS)) + 1));
    to->add_prop(LIVE_I_SEE_DARK, ((query_prop(LIVE_I_SEE_DARK)) - 30));
    set_alarm(itof(time), 0.0, end_effect);
}

void
leave_env(object old, object dest)
{
    ::leave_env(old, dest);

}

