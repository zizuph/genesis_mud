#include "../guild.h"
#include <filter_funs.h>
#include <macros.h>

#define DRINK_HP 75

void drink2(int response, object drainer, object drainee);

varargs void
tell_others(string str, object *exclude)
{
    object *players;

    players = all_inventory(environment(this_player())) - exclude;
    players = FILTER_PLAYERS(FILTER_CAN_SEE_IN_ROOM(players));

    if (sizeof(players))
    {
        players->catch_msg(str);
    }
}

int
can_drink(object drainer, object drainee)
{
    object drain_prop;

    if (IS_WIZ(drainee) && !IS_WIZ(drainer))
    {
        drainer->catch_tell("You cannot drink the blood of an immortal!\n");
        return 0;
    }

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

    if (!drainer->can_vamp_drink(drainer, drainee))
    {
        return 0;
    }

    /* Don't continue if the target is already very injured */
    if (drainee->query_hp() <= DRINK_HP)
    {
        drainer->catch_tell(capitalize(PRO(drainee)) +
            " is already on the verge of death.\n");
        return 0;
    }

    return 1;
}

int
drink(string arg)
{
    object *oblist, who, drain_prop, yn_ob;

    if (!strlen(arg) || !sizeof(oblist = parse_this(arg, "[from] [the] %l")))
    {
        notify_fail(capitalize(query_verb()) + " from whom?\n");
        return 0;
    }

    who = oblist[0];
  
    if (!can_drink(this_player(), who))
    {
        return 1;
    }

    setuid();
    seteuid(getuid());

    // Ask the target if he will give blood.
    if (yn_ob = clone_object(YES_NO_OBJECT))
    {
        /* When yn_ob gets a "yes" or "no" answer, or it times out,
         * it reports back to this object with the answer
         */
        if (!yn_ob->get_answer(who, 
            &drink2(, this_player(), who), 20.0))
        {
            // something failed in yn_ob...remove it.
            yn_ob->remove_object();
        }
        else
        {
            write("You ask " + who->query_the_name(this_player()) +
                " if you may drink some of " + POS(who) +
                " precious blood.\n");
            who->catch_tell(this_player()->query_The_name(who) +
                " asks if " + PRO(this_player()) + " may drink some " +
                "of your precious blood.  (Yes/No)\n");
            tell_others(QCTNAME(this_player()) + " asks " + QTNAME(who) +
                " something.\n", ({ who, this_player() }));
  
            return 1;
        }
    }

    /* yn_ob won't clone...oh well.... */
    write("For some reason you can't bring yourself to drink any of " +
        LANG_POSS(who->query_the_name(this_player())) + " blood.\n");

    return 1;
}

void
drink2(int response, object drainer, object drainee)
{
    string name = drainee->query_The_name(drainer);
  
    if (!drainee || !drainer || 
        (environment(drainee) != environment(drainer)))
    {
        drainer->release_vamp_drainee(1);
        return;
    }
  
    if (!response)
    {
        drainer->catch_tell(name + " denied your request for " +
            POS(drainee) + " blood.\n");
        drainer->release_vamp_drainee(1);
        return;
    }
  
    if (response < 0)
    {
        drainer->catch_tell(name + " failed to respond to your request " +
            "for " + POS(drainee) + " blood.\n");
        drainer->release_vamp_drainee(1);
        return;
    }
  
    if (!can_drink(drainer, drainee))
    {
        drainer->release_vamp_drainee(1);
        return;
    }
  
    set_this_player(drainer);
    write(drainee->query_The_name(drainer) + " bends " + POS(drainee) +
        " head to the side, exposing " + POS(drainee) + " neck.\nYou " +
        "tightly press your lips against " + POS(drainee) + " flesh and " +
        "gently bite into " + POS(drainee) + " flesh, easily piercing " +
        POS(drainee) + " skin with your fangs.\n");
    drainee->catch_tell("As " + drainer->query_the_name(drainee) +
        " moves toward your exposed neck, " + POS(drainer) +
        " eyes meet yours, and all senses are lost in " + POS(drainer) +
        " entrancing gaze.\nSuddenly you are overcome with a rush " +
        "of ecstacy as " + POS(drainer) + " cold lips press against " +
        "your neck and " + POS(drainer) + " fangs pierce your skin.\n");
    tell_others(QCTNAME(drainee) + " bends " + POS(drainee) +
        " head to the side, exposing " + POS(drainee) + " neck.\n" +
        capitalize(PRO(drainee)) + " closes " +  POS(drainee) + " eyes as " +
        QTNAME(drainer) + " takes " + OBJ(drainee) + " in " +
        POS(drainer) + " arms,\npressing " + POS(drainer) +
        " lips tightly against " + POS(drainee) + " neck.\nIt almost " +
        "seems as if you can hear the sound of " + POS(drainee) +
        "\nskin breaking as " + PRO(drainer) + " bites into " +
        POS(drainee) + " flesh.\n", ({ drainer, drainee }));
  
    /* begin drinking */
    drainer->start_vamp_drink(drainee);
}
