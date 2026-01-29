/* This objects stuns the victim of a plexus hit.
 * 
 * Glindor Jul-94
 * Recoded and commented by Cirion, 1998.08.05
 */
#pragma strict_types
#pragma save_binary

inherit "/std/object";

#include "defs.h"

int aid;
int inactive;
object victim;
float stuntime, waittime;

#define MAYDO ({ "commune", "quit", "look", "examine", "exa", \
        "v", "vitals", "help", \
        "groan", "moan", "whine", "drop", "put" })
#define MIGHTDO ({ "north", "south", "east", "west", "up", "down", "in", \
        "out", "northeast", "northwest", "southeast", "southwest",\
        "say" })

string *stun_messages = ({
        "The pain from the blow to your solar plexus prevents you "
            + "from doing that.",
        "You are immobalized by the blow to your plexus, making you "
            + "unable to do that.",
        "Your limbs refuse to follow your orders." });

public void
create_object()
{
    set_no_show();
    set_name(MONK_PLEXUS_STUN_ID);
    add_prop(OBJ_M_NO_DROP, 1);
    add_prop(OBJ_I_NO_GIVE, 1);
    inactive = 0;
}

/*
 * Function name: stop
 * Description:   catch-all command that stops a player from
 *                performing any actions, except those defined
 *                in the MAYDO definition.
 * Arguments:     str - the argument to the command
 * Returns:       1 if we stopped the command
 */
public int
stop(string str)
{
    string verb;
    float stun_time;
    mixed alarm;
    int chance;
    object who;

    who = this_player();

    /* Only paralyze our environment */
    if (environment() != who)
        return 0;

    if (inactive)
        return 0;

    // Don't affect wizards
    if (who->query_wiz_level())
    {
        write("Your wizardly state prevents the plexus stun "
            + "from having any effect.\n");
        return 0;
    }

    verb = query_verb();

    // If the verb is in the list of things we are allowed
    // to do, then prevent the stun from stopping the action.
    if (member_array(verb, MAYDO) >= 0) 
        return 0;

    if ((member_array(verb, MIGHTDO) < 0) &&
        (member_array(verb, environment(who)->query_exit_cmds()) < 0))
    {
        write(stun_messages[random(sizeof(stun_messages))] + "\n");
        return 1;
    }

    // otherwise, the command is in the list of things
    // we might be able to do.
    alarm = get_alarm(aid);
    stun_time = alarm[2];

    chance = (stun_time == 0.0 ? 100 : ftoi(400.0 / stun_time));
    if (random(100) > chance) 
        return 0;
        
    write(stun_messages[random(sizeof(stun_messages))] + "\n");
    return 1;
}

void
deactivate()
{
    if (inactive)
        return;

    if (objectp(victim))
    {
        victim->catch_msg("You feel your breath returning.\n");
        tell_room(environment(victim), QCTNAME(victim) + " seems to "
            + "regain " + victim->query_possessive() + " breath.\n", victim, victim);
        victim->remove_stun();
    }

    inactive = 1;

    remove_object();
}


void
start_time(float time)
{
    stuntime = time;

    aid = set_alarm(stuntime, 0.0, deactivate);
}

void
init()
{
    ::init();

    if (environment() != this_player())
        return;

    add_action(stop, "", 1);

    this_player()->add_stun();

    victim = this_player();
    inactive = 0;
}

void
enter_env(object env, object from)
{
    ::enter_env(env, from);

    if (!env || !living(env))
    {
        remove_object();
    }
}

string
stat_object()
{
        string str;
        mixed alarms;
        int t;
        str = "This object is used to paralyze the victim of a plexus attack.\n";
        str += "Original stuntime : "+ftoa(stuntime)+"\n";
        str += "Original waittime : "+ftoa(waittime)+"\n";
        str += "Inactive : "+inactive+ "\n";
        alarms = get_all_alarms();
        for (t = 0; t < sizeof(alarms); t++)
        {
	str+="Alarm     F: "+ alarms[t][1]+"    Time: "+ ftoa(alarms[t][2]) + "\n";
        }
        return str;
}

