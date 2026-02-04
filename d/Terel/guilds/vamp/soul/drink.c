
#include "../guild.h"
#include <filter_funs.h>
#include <macros.h>
#include <std.h>

inherit "/lib/commands";

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

    // Vampires should not be able to drink from NPCs. They need to
    // earn their blood through fighting. November 2009 - Petros
    if (!drainer->query_npc() && drainee->query_npc())
    {
        drainer->catch_msg(QCTNAME(drainee) + " does not offer "
            + drainee->query_possessive() + " blood to you.\n");
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

    who->hook_asked_blood(TP);

    if (this_player()==who->query_prop(LIVE_O_OFFERED_BLOOD))
    {
        drink2(1,this_player(),who);
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
                " if you may savor some of " + POSS(who) +
                " warm blood.\n");
            who->catch_tell(this_player()->query_The_name(who) +
                " asks if " + PRO(this_player()) + " may savor some " +
                "of your warm blood.  Do you accept or refuse?\n");
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
            POSS(drainee) + " blood.\n");
        drainer->release_vamp_drainee(1);
        return;
    }
  
    if (response < 0)
    {
        drainer->catch_tell(name + " failed to respond to your request " +
            "for " + POSS(drainee) + " blood.\n");
        drainer->release_vamp_drainee(1);
        return;
    }
  
    if (!can_drink(drainer, drainee))
    {
        drainer->release_vamp_drainee(1);
        return;
    }
  
    set_this_player(drainer);
    write(drainee->query_The_name(drainer) + " bends " + POSS(drainee) +
        " head to the side, exposing " + POSS(drainee) + " neck. You " +
        "tightly press your lips against " + POSS(drainee) + " flesh and"+ 
        " gently bite into " + POSS(drainee) + " flesh, easily piercing " +
        POSS(drainee) + " skin with your fangs.\n");
    drainee->catch_tell("As " + drainer->query_the_name(drainee) +
        " moves toward your exposed neck, " + POSS(drainer) +
        " eyes meet yours, and all senses are lost in " + POSS(drainer) +
        " entrancing gaze. Suddenly you are overcome with a rush " +
        "of ecstacy as " + POSS(drainer) + " cold lips press against " +
        "your neck and " + POSS(drainer) + " fangs pierce your skin.\n");
    tell_others(QCTNAME(drainee) + " bends " + POSS(drainee) +
        " head to the side, exposing " + POSS(drainee) + " neck. " +
        capitalize(PRO(drainee)) + " closes " +  POSS(drainee) + " eyes as " +
        QTNAME(drainer) + " takes " + OBJ(drainee) + " in " +
        POSS(drainer) + " arms, pressing " + POSS(drainer) +
        " lips tightly against " + POSS(drainee) + " neck. It almost " +
        "seems as if you can hear the sound of " + POSS(drainee) +
        " skin breaking as " + PRO(drainer) + " bites into " +
        POSS(drainee) + " flesh.\n", ({ drainer, drainee }));
  
    drainer->stop_fight(({ drainee }));
    drainee->stop_fight(({ drainer }));
    
    (ABILITY_DIR+"bite")->stop_ability(drainer);
    (ABILITY_DIR+"bite")->stop_ability(drainee);
  
    /* begin drinking */
    drainer->start_vamp_drink(drainee);
}
