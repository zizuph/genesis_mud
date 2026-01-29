/* -*- Mode: C -*-
 *
 * npc/harbourm.c
 *
 * The questmaster in Dol Amroth. He is realy in charge of the harbour,
 * and responsible that all visiting ships are given good service and
 * that they dont try to smugle anything in or out.
 */
inherit "/d/Gondor/common/dunedain/npc/npc_dunadan";
inherit "/d/Gondor/common/lib/binbit";

#include "../defs.h"
#include <const.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

#define TASK         ({ "I want you to find the following locations: The " + \
                        "bank, the post office and the tavern.\n", \
                        "In the baraks by the navy pier the beds are " + \
                        "untidy, I want you to go there and make the beds.\n",\
                        "I have heard roumors about a spy working " + \
                        "from this city. I need proof to take him in. " + \
                        "Can you gather them for you?\n", \
                        "I want you to check the sewer, and report to me " + \
                        "when it is done.\n", \
                     })

       void      get_armed();
public string    give_task();
public string    give_reward();

public void
create_dunadan()
{
    set_living_name("gotmir");
    set_name("gotmir");
    add_name( ({ "dunadan","human","master","harbourmaster","questmaster" }) );
    set_adj("tired");
    add_adj("busy");
    add_adj("harbour");
    add_adj("master");
    set_race_name("human");
    set_gender(G_MALE);
    set_title("Harbour Master of Dol Amroth");
    set_dunedain_house("Hallacar");
    set_long("This busy man is the harbour master of Dol Amroth.\n");

    default_config_npc(75);
    set_base_stat(SS_INT, 80);
    set_base_stat(SS_WIS, 85);
    set_skill(SS_WEP_SWORD, 55);
    set_skill(SS_AWARENESS, 60);
    set_skill(SS_TRADING, 75);

    add_prop(LIVE_I_ALWAYSKNOWN, 1);
    remove_prop(LIVE_M_NO_ACCEPT_GIVE);

    add_cmdsoul("/d/Gondor/common/dunedain/dunedain_soul");

    set_alignment(850 + random(150));

    set_chat_time(200);
    add_chat("With all the traffic here, I would need an extra hand.");
    add_chat("With the prince out of town I will have to do his tasks " +
	     "aswell.");

    set_default_answer("I have no idea what you are talking about.");
    add_ask( ({ "task", "quest", "job", "help" }), &give_task() );
    add_ask("reward", &give_reward() );

    set_act_time(75);
    add_act("emote shuffles through some papers.");
    add_act("emote ruffles his hair.");
    add_act("ponder");
    add_act("glitter");
    add_act("gleam");
    add_act("silence");
    add_act("dpace");

    get_armed();
}

int
accept(string str)
{
    object o, tp = this_player();
    int    task = tp->query_prop(I_HAVE_JUST_ASKED_FOR_A_TASK) - 1;

    if (!strlen(str))
	return 0;

    if (str != "task" || !tp->query_prop(I_HAVE_JUST_ASKED_FOR_A_TASK))
	return 0;

    tp->remove_prop(I_HAVE_JUST_ASKED_FOR_A_TASK);
    o = clone_object(DOL_OBJ + "quest/I_do_quest_token");
    o->set_task(task);
    o->set_part(1);
    o->move(tp,1);
    command("say Good, return to me as soon as you have finished your task.");

    return 1;
}

void
init_living()
{
    ::init_living();
    add_action(accept, "accept");
}

void
get_armed()
{
    clone_object(DOL_TG+"pants")->move(this_object());
    clone_object(DOL_TG+"vest")->move(this_object());
    clone_object(DOL_TG+"belt")->move(this_object());
    clone_object(DOL_TG+"lboots")->move(this_object());
    command("wear all");
}

public string
give_task()
{
    int task;

    object tp = this_player();

    if (present("I_do_quest_token.c", tp))
    {
        command("say Arn't you busy?\n");
        return "";
    }

    task = query_bin_bits(DOL_Q_GROUP, DOL_FIRST_BIT, DOL_Q_M_LAST, tp);
    
    if (task < DOL_Q_M_EXPLORE_TOWN)
	task = DOL_Q_M_EXPLORE_TOWN;

    if (task <= DOL_Q_M_LAST)
    {
	command("say Ah, you will help me out here, that good. Now listen " +
		"here.");
	tell_object(tp, TASK[task - DOL_Q_M_EXPLORE_TOWN]);
	command("say If you have understood the task, pleace 'accept task'.");
	command("emote waits hopefully.");
	tp->add_prop(I_HAVE_JUST_ASKED_FOR_A_TASK, task + 1);
	return "";
    }

    command("say I have no more tasks for you. You can help out " +
	    "discharging goods.");

    return "";
}

public void
introduce_me(object pl, string name)
{
    command("say Greetings "+capitalize(name));
    command("introduce me to "+name);
    command("grumble");
    command("say to "+name+" Maybe you can help me with something?");
}

public void
add_introduced(string name)
{
    object    pl;

    set_alarm(1.4, 0.0, &introduce_me(pl, name) );
}

public string
give_reward()
{
    object tp = this_player();
    object token = present("I_do_quest_token.c", tp);

    if (token->query_task() == DOL_Q_M_EXPLORE_TOWN && token->query_part() == 4)
    {
	command("say So now you know the town a little better.");

	tp->command("$smile");

	token->give_reward(tp, 50);
	token->remove_object();

	command("say Now you can start doing more important tasks.");

	return "";
    }

    if (token->query_task() == DOL_Q_M_MAKE_BED && token->query_part() == 2)
    {
	command("say Finished with the bed?");

	tp->command("$nod .");

	token->give_reward(tp, 50);
        token->remove_object();

	command("say Thanks for the help.");

	return "";
    }

    if (token->query_task() == DOL_Q_M_UNCOVER_SPY)
    {
	command("say Hand me the evidence, and I can reward you.");
	command("snort");
	
	return "";
    }

    if (token->query_task() == DOL_Q_M_CHECK_SEWER && token->query_part() == 8)
    {
	command("say You have seen enough of the sewer to give me a report?");
	command("smile");
	token->give_reward(tp, 300);
	token->remove_object();

	return "";
    }

    if (token->query_task() < DOL_Q_M_LAST)
    {
	command("You havn't completed your task.");
    }

    command("You're not working for me.");

    return "";
}

void
remove_evidence(object ob)
{
    ob->remove_object();
    command("emote puts an envilop into a drawer.");
}

/*
 * Function name:    enter_inv
 * Description  :    mask parent to catch herbs.
 * Arguments    :    object ob -- the entering object
 *                   object from -- source
 */
public void
enter_inv(object ob, object from)
{
    object token;

    ::enter_inv(ob, from);

    if (objectp(from))
    {
	token  = present("I_do_quest_token.c", from);
    }

    if (objectp(token) && ob->id("DolAmrothEvidence") && 
	token->query_task() == DOL_Q_M_UNCOVER_SPY)
    {
	command("say Thanks for the evidence, this will realy help us.");
	token->give_reward(from, 300);
	token->remove_object();
	set_alarm(1.0, 0.0, &remove_evidence(ob));
        return;
    }
    command("say I am not interested in your "+ob->query_short()+".");
    command("give "+ob->query_name()+" to "+from->query_name());
}

