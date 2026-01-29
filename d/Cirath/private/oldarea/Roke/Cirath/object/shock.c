/* This objects shocks the victim of a plexus hit.
 * 
 * Glindor Jul-94
 *
 * Changed for the inquisitor-sword by Valeria, Nov-94
 */

inherit "/std/object";
#include "/d/Roke/common/defs.h"
#include "/d/Roke/Cirath/defs.h"

int aid;
int inactive;
object victim;
float shocktime,waittime;

#define MAYDO ({"commune","quit","look","v","vitals","help","groan",\
		"moan", "whine","drop","put"})
#define MIGHTDO ({ "north", "south", "east", "west", "up", "down", "in", \
		   "out", "northeast", "northwest", "southeast", "southwest",\
		   "say"})
create_object()
{
    set_no_show();
    set_name("inq_beam_shock");
    add_prop(OBJ_I_NO_DROP, 1);
    add_prop(OBJ_I_NO_GIVE, 1);
    inactive = 0;
}

init()
{
    add_action("stop", "", 1);
    set_alarm(1.0,0.0,"entered",this_player());
}

entered(object ob)
{
    if (environment(this_object()) != ob) return;

    ob->add_stun();
    victim = ob;
    inactive = 0;
}

start_time(mixed time, wtime)
{
    shocktime = 10.0;

    waittime = 10.0;

    aid = set_alarm(shocktime, 0.0, "deactive");
    set_alarm(waittime, 0.0, "expire");
}

int stop(string str)
{
    string verb;
    float time;
    mixed alarm;
    int chance;

    /* Only paralyze our environment */
    if (environment(this_object()) != this_player())
        return 0;

    if (inactive) return 0;

    /* Don't affect wizards */
    if (this_player()->query_wiz_level())
        return 0;

    verb = query_verb();

    if (member_array(verb, MAYDO) != -1) return 0;

    if (member_array(verb, MIGHTDO) == -1)
    {
	write("You are so shocked it would never work.\n");
	return 1;
    }

    alarm = get_alarm(aid);
    time = alarm[2];

    chance = ftoi(400.0 / time);
    if (random(100) > chance) return 0;
    
    write("You are to shocked to do that.\n");
    return 1;
}

deactive()
{
    int a;

    if (inactive) return;

    if (objectp(victim))
    {
	victim->catch_msg("The world is back in your sight.\n");

	victim->remove_stun();
    }

    inactive = 1;
}

expire()
{
    deactive();
    remove_object();
}

string
stat_object()
{
    string str;
    mixed alarms;
    int t;
    str = "This object shocks the enemy from doing many things.\n";
    str += "Original shocktime : "+ftoa(shocktime)+"\n";
    str += "Original waittime : "+ftoa(waittime)+"\n";
    str += "Inactive : "+inactive+ "\n";
    alarms = get_all_alarms();
    for (t = 0; t < sizeof(alarms); t++)
    {
	str+="Alarm   F: "+ alarms[t][1]+"  Time: "+ ftoa(alarms[t][2]) + "\n";
    }
    return str;
}


