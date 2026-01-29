#include "../guild.h"
#include <macros.h>

#define LIVE_M_NO_DRAIN "_live_m_no_drain"

void drain2(object drainer, object drainee, int past_death);

int
can_drain(object drainer, object drainee)
{
    object drain_prop;
    mixed why;

    if (drainer->query_vamp_drain())
    {
        drainer->catch_tell("You are already draining someone!\n");
        return 0;
    }

    if (drain_prop = drainee->query_prop(LIVE_O_VAMP_DRAINER) &&
        (drain_prop != drainer))
    {
        drainer->catch_tell(capitalize(PRO(drainee)) +
            " is already in someone's embrace.\n");
        return 0;
    }

    if (QP(drainer, LIVE_I_STUNNED))
    {
        drainer->catch_tell("You can't manage to drain " + 
            drainee->query_the_name(drainer) + ".\n");
        return 0;
    }

    if (why = QP(drainer, LIVE_M_MOUTH_BLOCKED))
    {
        drainer->catch_tell(stringp(why) ? why : "Your mouth is blocked\n");
        return 0;
    }
  
    if (why = QP(drainee, LIVE_M_NO_DRAIN))
    {
        drainer->catch_tell(stringp(why) ? why : "You can't seem to manage " +
            "to drain " + drainee->query_the_name(drainee) + ".\n");
        return 0;
    }
  
#if 0
    /* We can't drain if anyone other than the target
     * is currently attacking us.
     */
    livings = FILTER_OTHER_LIVE(all_inventory(drainer) - ({ drainee, drainer }));
    for (i = 0; i < sizeof(livings); i++)
    {
        if (livings[i]->query_attack() == drainer)
        {
            drainer->catch_tell("You can't drain from " + 
                drainee->query_the_name(drainer) + " while others are " +
                "fighting you.\n");
            return 0;
        }
    }

    /* Don't continue if the target is in combat */
    for (i = 0; i < sizeof(livings); i++)
    {
        if (livings[i]->query_attack() == drainee)
        {
            drainer->catch_msg("You can't drain from " + 
                drainee->query_the_name(drainer) +
                " while others are fighting " + OBJ(drainee) + ".\n");
            return 0;
        }
    }
#endif

    if (stringp(why = drainer->c_can_attack(drainee, "drain")))
    {
        drainer->catch_tell(why);
        return 0;
    }

    return 1;
}

int
drain(string arg)
{
    int past_death;
    object *oblist, who, drain_prop;
    mixed why;

    if (strlen(arg))
    {
        if (!sizeof(oblist = parse_this(arg, "[from] [the] %l")))
        {
            if (!sizeof(oblist = 
                parse_this(arg, "[from] [the] %l 'past' 'death'")))
	    {
                if (arg != "past death")
		{
                    notify_fail("Vdrain from whom?\n");
                    return 0;
		}
	    }

            past_death = 1;
	}

        if (sizeof(oblist))
	{
            who = oblist[0];
	}
    }

    if (!who && !(who = this_player()->query_attack()))
    {
        notify_fail("Vdrain from whom?\n");
        return 0;
    }

    if (past_death && (who == this_player()->query_vamp_drain()))
    {
        this_player()->enable_drain_past_death(who);
        write("Ok.\n");
        return 1;
    }
    
    if (IS_WIZ(who) && !IS_WIZ(this_player()))
    {
        write("You cannot drink the blood of an immortal!\n");
        return 1;
    }

    if (!can_drain(this_player(), who))
    {
        return 1;
    }

    if (this_player()->query_attack() != who)
    {  
    	say(QCTNAME(this_player()) + " attacks " + QTNAME(who) + ".\n",
    	    ({ this_player(), who }) );
    	tell_object(who, this_player()->query_The_name(who) + 
            " attacks you!\n");
    }

    this_player()->attack_object(who);
    this_player()->reveal_me();

    set_alarm(2.0, 0.0, &drain2(this_player(), who, past_death));
    return 1;
}

void drain2(object drainer, object drainee, int past_death)
{
    int hitsuc, hit, right, left;
    string drainee_name, drainer_name;
  
    if (!drainer || !drainee ||
        (environment(drainee) != environment(drainer)))
    {
        return;
    }
  
    if (!can_drain(drainer, drainee))
    {
        return;
    }
  
    drainer->start_vamp_drain(drainee);

    if (past_death)
    {
        drainer->enable_drain_past_death(drainee);
    }
}

int
stop_drain(object drainer)
{
    int index;

    if (drainer->query_vamp_drain())
    {  
        drainer->release_vamp_drainee(0);
        return 1;
    }
  
    notify_fail("You aren't draining anyone!\n");
    return 0;
}
