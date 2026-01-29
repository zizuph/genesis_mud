/*
 * /d/Gondor/guilds/rangers/npc/poisoned_npc.c
 *
 * Poisoned Ranger used for Ranger tasks. A player must keep him alive
 * or cleanse him to pass the task.
 *
 * Coded by Gwyneth
 */
#include <composite.h>
#include <files.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "../rangers.h"

inherit RANGERS_NPC + "npc_ranger.c";

int    gPoisoned = 0;
int    gTracker = 0;
object gPoison;
string gHelper = "";

public void
create_ranger()
{
    set_stats(({ 90, 90, 90, 90, 90, 90 }));
    set_company(one_of_list(({ "ithilien", "north" })));
    set_adj(({ "pale", "sickly" }));
    set_gender(G_MALE);
}

void
init_living()
{
    ::init_living();

    if (!objectp(gPoison) && !gPoisoned)
    {
        gPoison = clone_object(RANGERS_DIR + "tasks/poison.c");
        gPoison->move(this_object(), 1);
        gPoison->start_poison(this_object());
        gPoisoned = 1;
        heal_hp(-1 * query_max_hp()/2);
    }

    remove_prop(LIVE_M_NO_ACCEPT_GIVE);
}

void
set_helper(string name)
{
    gHelper = name;
}

public void
return_sigh(object actor)
{
    if (!objectp(present(actor, ENV(TO))))
        return;

    switch (random(5))
    {
    case 0:
        if (objectp(gPoison))
            command("say Is there no hope?");
        else
            command("say Do not give up hope!");

        break;
    case 1:
        if (objectp(gPoison))
            command("emote looks grim as the poison ravages his body.");
        else
        {
            command("say Something wrong, friend?");
            command("peer . " + actor->query_real_name());
        }

        break;
    default:
        break;
    }
}

public void
return_smile(object actor)
{
    if (!objectp(present(actor, ENV(TO))))
        return;

    switch (random(7))
    {
    case 0:
        if (objectp(gPoison))
            command("say I hope that is a smile of hope, " +
              (actor->query_gender() ? "madam" : "sir") + ", for I " +
              "do not think I will last very long.");
        else
            command("say You seem pleased today, " +
              (actor->query_gender() ? "madam" : "sir") + ".");
        break;
    case 1:
        command("smile hopefully " + actor->query_real_name());
        break;
    case 2:
        command("say I wish I could share your good mood.");
        command("say I lost my best friend in Ithilien two days ago.");
        command("sigh .");
        if (objectp(gPoison))
            command("say Now I may join him if I am not cured!");
        break;
    default:
        break;
    }
}

void
set_tracker(int i)
{
    gTracker = i;
}

void
consume_ob(object ob)
{
    if (present(ob))
    {
        command("say I could not manage to use that.");
        command("put " + ob->query_pname());
        return;
    }

    if (!gTracker)
    {
        command("say You are very " +
            one_of_list(({ "kind", "generous", "compassionate", "helpful" })));
        set_tracker(1);
    }

    set_alarm(0.5, 0.0, &set_tracker(0));
}

public void
do_remove()
{
    remove_object();
}

void
leave_inv(object ob, object from)
{
    object helper = find_player(gHelper);
    if (ob->query_task_poison() && query_hp() > 0)
    {
        helper->add_prop(RANGER_I_SUCCESS_CURE, 1);
        command("emote starts to look better.");
        remove_adj("pale");
        remove_adj("sickly");
        add_adj("healthy");
        add_adj("glowing");
        command("say I'm all better! Thank you!");
        set_alarm(1.0, 0.0, &do_remove());
        set_alarm(0.9, 0.0, &command("emote returns to neglected duties."));
    }
}

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if (!objectp(from))
        return;

    if (ob->query_name() == "potion")
    {
        set_alarm(0.5, 0.0, &command("quaff " + OB_NAME(ob)));
        set_alarm(2.3, 0.0, &consume_ob(ob));
    }
    else if (strlen(ob->query_herb_name()))
    {
        set_alarm(0.5, 0.0, &command(ob->query_ingest_verb() +
            " " + OB_NAME(ob)));
        set_alarm(2.3, 0.0, &consume_ob(ob));
    }
    else if (IS_DRINK_OBJECT(ob))
    {
        set_alarm(0.5, 0.0, &command("drink " + ob->query_pname()));
        set_alarm(2.3, 0.0, &consume_ob(ob));
    }
    else if (IS_FOOD_OBJECT(ob))
    {
        set_alarm(0.5, 0.0, &command("eat " + ob->query_pname()));
        set_alarm(2.3, 0.0, &consume_ob(ob));
    }
    else
    {
        set_alarm(1.0, 0.0, &command("put" + ob->query_pname()));
    }
}

public void
do_die(object killer)
{
    object helper = find_player(gHelper);
    command("emote groans: You have failed me, " + capitalize(gHelper) + "!");
    helper->add_prop(RANGER_I_FAILED_CURE, 1);
    command("sing gondor");
    ::do_die(killer);
}
