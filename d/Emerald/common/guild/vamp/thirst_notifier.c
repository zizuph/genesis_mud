#pragma strict_types
#pragma no_clone

#include <filter_funs.h>
#include <stdproperties.h>
#include <macros.h>
#include <language.h>

static private int alarm_id = 0;
static private object *registered = ({});
static private int n_counter = 0;

void unregister(object who);

void
notify_thirst(object who)
{
    string msg;

    if (strlen(msg = who->desc_vamp_thirst()))
    {
	who->catch_tell(msg);
    }
}

int
filter_ppl(object ob1, object ob2)
{
    return (living(ob1) &&
        CAN_SEE(ob2, ob1) &&
        !ob1->query_prop(LIVE_I_UNDEAD) &&
        !ob1->query_prop(LIVE_I_NO_BODY) &&
        !ob1->query_prop("_live_i_no_blood") &&
        ob1->query_humanoid());
}

int
check_if_occupied(object who)
{
    return (who->query_attack() ||
        who->query_vamp_drain() ||
        who->query_prop(LIVE_I_STUNNED) ||
        who->query_prop(LIVE_I_MEDITATES) ||
        who->query_prop(LIVE_I_CONCENTRATE));
}

void
notify_misc(object who)
{
    object *ppl, target;

    if ((who->thirst() < 30) || check_if_occupied(who))
    {
        return;
    }

    if (!CAN_SEE_IN_ROOM(who))
    {
        return;
    }

    if (!sizeof(ppl = filter(all_inventory(environment(who)) - ({ who }),
        &filter_ppl(, who))))
    {
        return;
    }

    target = ppl[random(sizeof(ppl))];
    
    switch (random(3))
    {
        case 0:
            if (!CAN_SEE_IN_ROOM(target) || !CAN_SEE(target, who) ||
                check_if_occupied(target))
	    {
                return;
	    }

            target->catch_tell("You notice " + who->query_the_name(target) +
                " staring absentmindedly at your neck.\n");
            return;

        case 1:
            who->catch_tell("Glancing at " + target->query_the_name(who) +
                ", you notice the faint pulsation in " +
                target->query_possessive() + " neck, throbbing with each " +
                "heartbeat.\n");
            return;
        case 2:
            who->catch_tell("You hear the scarcely perceptible sound of " +
                LANG_POSS(target->query_the_name(who)) + " heart beating.\n");
            return;
    }
}
    
void
notify()
{
    int i;
    string msg;

    unregister(0);

    if (++n_counter == 3)
    {
        n_counter = 0;
    }

    for (i = 0; i < sizeof(registered); i++)
    {   
        if (!n_counter)
	{
            notify_thirst(registered[i]);
	}
        else if (!random(8))
        {
            notify_misc(registered[i]);
	}
    }
}

void
register(object who)
{
    /* make sure there aren't double entries */
    registered -= ({ who });
    registered += ({ who });

    if (!alarm_id)
    {
        alarm_id = set_alarm(120.0, 120.0, notify);
    }
}

void
unregister(object who)
{
    registered -= ({ who, 0 });

    if (!sizeof(registered) && alarm_id)
    {
        remove_alarm(alarm_id);
        alarm_id = 0;
    }
}
