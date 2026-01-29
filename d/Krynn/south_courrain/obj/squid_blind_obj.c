/*
 *    Squid blind object.
 */

inherit "/std/object";

#include <stdproperties.h>
#include <macros.h>
#include "/d/Krynn/common/defs.h"

#define BLIND_SUBLOC "squid_blind_subloc"

object blinder;
int time = 8;

void
create_object()
{
    set_name("squid_blind_object");

    add_prop(OBJ_I_VOLUME, 0);
    add_prop(OBJ_I_WEIGHT, 0);
    add_prop(OBJ_I_NO_DROP, 1);
    add_prop(OBJ_I_NO_GIVE, 1);

    set_no_show();
}

void
can_see_again(object victim)
{
    int blind = victim->query_prop(LIVE_I_BLIND);
        
    victim->add_prop(LIVE_I_BLIND, --blind);

    if ((!objectp(victim)) || (victim->query_ghost()) || 
            (!living(victim)))
    {
        remove_object();
        return;
    }

    if(CAN_SEE_IN_ROOM(victim))
    {
        victim->catch_msg("You manage to clear the squid ink from " +
            "your eyes and are able to see again!\n");
        TELL_ROOM(E(victim), victim, " clears " + POSSESSIVE(victim)
            + " eyes, and seems to be able to see again!", victim);
    }
    else
    {
        victim->catch_msg("You manage to clear some of the squid " +
            "ink from your eyes.\n");
        TELL_ROOM(E(victim), victim, " clears some of the ink from " 
            + POSSESSIVE(victim) + " eyes.", victim);
    }

    remove_object();
}

void
do_blind(object target, int duration)
{
    int blind = target->query_prop(LIVE_I_BLIND);
        
    target->add_prop(LIVE_I_BLIND, ++blind);

    set_alarm(itof(duration), 0.0, &can_see_again(target));

}

void
enter_env(object to, object from)
{
    ::enter_env(to, from);

    if (!objectp(to))
    {
	remove_object();
	return;
    }

    if (!living(to))
    {
	remove_object();
	return;
    }

    time += random(8);

    to->add_subloc(BLIND_SUBLOC, TO);
    do_blind(to, time);
}

void
leave_env(object from, object to)
{
    from->remove_subloc(BLIND_SUBLOC);
    ::leave_env(from, to);
}

string
show_subloc(string subloc, object carrier, object for_obj)
{
    string str;
    if (carrier->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
	return "";

    if (for_obj == carrier)
	str = "You cannot see! Everything is a black inky mess!\n";
    else str = C(PRONOUN(carrier)) + " seems to have something in "
	+ POSSESSIVE(carrier) + " eyes!\n";
    return str;
}

