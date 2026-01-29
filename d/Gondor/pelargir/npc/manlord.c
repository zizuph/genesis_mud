#pragma strict_types

inherit "/d/Gondor/pelargir/npc/citizen.c";

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/bits.h"
#include "/d/Gondor/pelargir/lib/statue_quest.h"

void
set_up_chats()
{
    set_chat_time(2);
    add_chat("If only the rest of the city could be as beautiful as this!");
    add_chat("My family has a history of brave warriors.");
    add_chat("I wish that I had more to remember my ancestors by.");
    add_chat("The foes of Gondor have always been foes of my family!");
    add_chat("I once had a statue to remember by, but I lost it.");
    add_chat("The one thing I value most is the statue I lost.");
    add_chat("Those foul thieves who stole my statue ruined the eve of "
      + "my life.");
    add_chat("Pelargir is beautiful all year round!");
    add_chat("There have been a surprising number of "+
       "strange visitors lately.");
    add_chat("I fear that there will be war soon!");

    set_act_time(3);

    add_act("emote sighs: If I still had the statue that remembers the days "
      + "of my youth!");
    add_act("emote seems lost in remembrance.");
    add_act("emote glances without hope at the bookshelf as if looking for "
      + "something.");
    add_act("emote curses under his breath: If I were still the man I was "
      + "when I was young, I would hunt down those dirty thieves.");
}

void
create_citizen()
{
    set_name("Linyenwo");
    add_name("linyenwo");
    add_name("lord");
    set_race_name("human"); 
    set_adj("elderly");
//  set_short("lord of the mansion");
//  set_pshort("lords of the mansion");
    set_long(BSN("The lord of the mansion. He is an elderly man "
      + "with a very proud posture and clearly of dunadan lineage."));

    if (query_gender())
    {
        set_gender(0);
        remove_name("woman");
        remove_pname("women");
        add_name("man");
        add_pname("men");
    }

    set_alignment(150);

    remove_prop(NPC_M_NO_ACCEPT_GIVE);
    remove_prop(LIVE_I_NEVERKNOWN);

    set_up_chats();

    set_default_answer(VBFC_ME("default_answer"));
    add_ask(({"help", "task", "job", }), VBFC_ME("ask_help"));
    add_ask(({"statue", }), VBFC_ME("ask_statue"));
}


void
return_object(object ob, object tp)
{
    if (ob->id("coin") || ob->id("coins"))
    {
        command("glare "+tp->query_real_name());
        command("say I don't need any charity.");
        command("say Begone!");
        return;
    }

    command("emote inspects the "+ob->short()+".");
    command("ponder");
    command("say I don't think I need that.");
    command("give "+OB_NAME(ob)+" to "+tp->query_real_name());
}

void
remove_statue(object statue)
{
    if (ENV(statue) == TO)
        statue->remove_object();

    set_chat_time(2);
    set_act_time(3);
}

void
check_statue(object statue, object tp)
{
    int     reward;

    command("smile at "+tp->query_real_name());
    command("say This is my statue indeed!");
    command("thank "+tp->query_real_name());

    set_alarm(300.0, 0.0, &remove_statue(statue));

    set_chat_time(40);
    set_act_time(40);
    seq_heartbeat(1);
    if (tp->test_bit("Gondor", PELARGIR_STATUE_GROUP, PELARGIR_STATUE_BIT))
        return;

    reward = tp->query_exp();
    if (reward > PELARGIR_STATUE_EXP)
        reward = PELARGIR_STATUE_EXP;

    tp->set_bit(PELARGIR_STATUE_GROUP, PELARGIR_STATUE_BIT);
    tp->add_exp_quest(reward);
    tp->adjust_alignment(50);
    tp->catch_msg("You feel more experienced.\n");
    LOG_QUEST(tp, reward, "PELARGIR STATUE");

}

void
paint_statue(object statue, object tp)
{
    command("emote inspects the "+statue->short()+".");
    command("emote looks disappointedly at the "+statue->short()+".");
    command("say This is supposed to be my statue?");
    command("say That cannot be!");
    command("say My statue was much more lively and realistic!");
    command("say It was painted by an artist to show every small "
      + "detail!");
    command("give "+OB_NAME(statue)+" to "+tp->query_real_name());
}

void
clean_statue(object statue, object tp)
{
    command("emote inspects the "+statue->short()+".");
    command("emote tries to clean the "+statue->short()+".");
    command("ponder");
    command("say Hmm, what's this?");
    command("say It looks like a statue, but it is too corroded to "
      + "recognize it.");
    command("give "+OB_NAME(statue)+" to "+tp->query_real_name());
    set_alarm(2.0 + 5.0 * rnd(), 0.0, 
        &command("say Perhaps the mason could clean the statue?"));
}

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if (!objectp(ob) || !objectp(from) || !living(from))
        return;

    if (ob->id(PEL_SQ_STATUE_3))
        set_alarm(2.0, 0.0, &check_statue(ob, from));
    else if (ob->id(PEL_SQ_STATUE_2))
        set_alarm(2.0, 0.0, &paint_statue(ob, from));
    else if (ob->id(PEL_SQ_STATUE_1))
        set_alarm(2.0, 0.0, &clean_statue(ob, from));
    else
        set_alarm(2.0, 0.0, &return_object(ob, from));
}
    
string
default_answer()
{
    command("think");
    command("say I'm just an old man.");
    command("say I don't know what you are talking about.");
    return "";
}

string
ask_help()
{
    if (TP->test_bit("Gondor", PELARGIR_STATUE_GROUP, PELARGIR_STATUE_BIT))
    {
        command("say I'm thankful that you helped me already!");
        command("wave "+TP->query_real_name());
        return "";
    }
    command("say Someone has stolen my most valuable possession, "
      + "a wonderful statue.");
    command("say It was all I had left to remind me of the days of "
      + "my youth.");
    command("sigh");
    command("say Please find it and bring it back to me!");
    START_QUEST(TP, "PELARGIR STATUE");
    return "";
}

string
ask_statue()
{
    command("say My statue was the only thing to remind me of the days "
      + "of my youth.");
    command("say I was a mighty warrior then!");
    command("strut");
    command("say But now, I'm too old and too weak to go and find the "
      + "thieves who stole my statue.");
    command("say Please find it for me!");
    command("say Those dirty thieves cannot have any use for my statue.");
    command("say It was valuable only to me alone, as a souvenir!");
    return "";
}

void
react_intro(object tp)
{
    if (!present(tp, ENV(TO)))
    {
        command("shrug");
        return;
    }

    command("introduce me to "+tp->query_real_name());
    command("say Greetings, " + tp->query_name() + "!");
    command("say What brings you to our wonderful city?");
}

public void
add_introduced(string str)
{
    if (!interactive(TP) || TP->query_met(query_name()))
        return;
    set_alarm(2.0 + 5.0 * rnd(), 0.0, &react_intro(TP));
}

