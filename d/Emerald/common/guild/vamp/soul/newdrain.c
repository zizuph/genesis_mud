#include "../guild.h"
#include <macros.h>

#define LIVE_M_NO_DRAIN "_live_m_no_drain"

void newdrain2(object drainer, object drainee);

int
newcan_drain(object drainer, object drainee)
{
    object drain_prop;
    mixed why;

    if (drainer->query_drain())
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
        drainer->catch_msg("You can't manage to drain " + 
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
                drainee->query_the_name(drainer) + " while others are fighting " +
                "you.\n");
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
newdrain(string arg)
{
    object *oblist, who, drain_prop;
    mixed why;

    if (sizeof(oblist = parse_this(arg, "[from] [the] %l")))
    {
        who = oblist[0];
    }
    else if (strlen(arg))
    {
        notify_fail(capitalize(query_verb()) + " from whom?\n");
        return 0;
    }
    else if (!(who = this_player()->query_attack()))
    {
        notify_fail(capitalize(query_verb()) + " from whom?\n");
        return 0;
    }

    if (IS_WIZ(who) && !IS_WIZ(this_player()))
    {
        write("You cannot drink the blood of an immortal!\n");
        return 1;
    }

    if (!newcan_drain(this_player(), who))
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
    this_player()->start_vamp_drain(who);

    set_alarm(2.0, 0.0, &newdrain2(this_player(), who));
    return 1;
}

void newdrain2(object drainer, object drainee)
{
    int hitsuc, hit, right, left;
    string drainee_name, drainer_name;
  
    if (!drainer || !drainee ||
        (environment(drainee) != environment(drainer)))
    {
        drainer->release_vamp_drainee(1);
        return;
    }
  
    if (!newcan_drain(drainer, drainee))
    {
        drainer->release_vamp_drainee(1);
        return;
    }
  
    drainer->continue_vamp_drain(drainee);
}

int
stop_drain(object drainer)
{
    int index;

    if (drainer->query_vamp_drain())
    {  
        drainer->release_vamp_drain(0);
        return 1;
    }
  
    notify_fail("You aren't draining anyone!\n");
    return 0;
}
