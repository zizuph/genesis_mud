#pragma strict_types

inherit "/d/Gondor/common/dunedain/npc/npc_dunadan.c";
inherit "/lib/trade";
inherit "/d/Gondor/common/lib/logkill.c";

#include <macros.h>
#include <money.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/pelargir/lib/statue_quest.h"

#define PRICE_TO_CLEAN	24

int     msg_id;
object  working_on;

void
create_dunadan() 
{
  set_living_name("throman");
  set_name("throman");
  add_name("mason");
  add_name("stone mason");
  set_race_name("human");
  set_dunedain_house("Thalion");
  set_adj(({"slender","old"}));
  set_long("Throman used to do the upkeep on the walls of Minas Tirith. "+
         "Now that he has turned that job over to his sons "+
         "he spends his life chipping out figurines for those "+
         "who want them.\n");
  set_base_stat(SS_CON,75);
    set_alignment(70);
   set_chat_time(4);
   add_chat("I like this job so much better!");
   add_chat("Not enough people want to sit and chat.");
   add_chat("My sons are always busy repairing the walls.");
   add_chat("I keep myself busy making statues... do you want one?");
   add_chat("I only make the best. They're perfect likenesses!");
   add_chat("One day I'll retire for good.");
   add_chat("I give my relatives a new statue every year.");
   add_chat("Give a statue to your sweetie.");
   add_chat("Watch out for the stone chips on the floor.");
   add_chat("Fiddlesticks!! I hate it when i mess up!");
   add_cchat("My sons will avenge me!");
   add_cchat("Have mercy!");
   add_cchat("May the stones of the road crumble under your feet!");
   add_cchat("You'll regret this!");
   add_cchat("Guards! Help!");

    set_default_answer(VBFC_ME("default_answer"));
    add_ask(({"statue", }), VBFC_ME("ask_statue"));
    add_ask(({"help", }), VBFC_ME("ask_help"));
    add_ask(({"work", }), VBFC_ME("ask_work"));

    remove_prop(NPC_M_NO_ACCEPT_GIVE);
    /* need this since we want to trade: */
    config_default_trade();
}

void
intro_me(object tp)
{
    if (!objectp(tp) || !interactive(tp) || !CAN_SEE_IN_ROOM(TO) ||
        !CAN_SEE(TO, tp) || !present(tp, ENV(TO)))
        return;
    command("introduce me to "+tp->query_real_name());
}

void
add_introduced(string name)
{
    object  tp;

    if (!objectp(tp = find_player(name)))
        return;

    if (tp->query_met(query_real_name()))
        return;

    set_alarm(2.0, 0.0, &intro_me(tp));
}

int query_knight_prestige() { return -5; }

void
return_object(object ob, object who)
{
    if (ob->id("coin") || ob->id("coins"))
    {
        command("gasp");
        command("say Why, thank you, my dear "
          + (who->query_gender() ? "Lady" : "Sir") + "!");
        command("thank "+who->query_real_name());
        command("say It will help me!");
        command("smile");
        return;
    }

    if (objectp(who) && present(who, ENV(TO)))
    {
        command("give "+OB_NAME(ob)+" to "+who->query_real_name());
        command("say What was that for?");
    }
    else
    {
        command("drop "+OB_NAME(ob));
        command("say Oh! So no one else wants it? So what should I do with it?");
    }
}

void
return_statue(object statue, object who)
{
    remove_alarm(msg_id);
    msg_id = 0;

    if (!objectp(who) || !present(who, ENV(TO)))
    {
        command("sigh");
        command("say What shall I do with this statue now?");
        command("drop statue");
        working_on = 0;
        return;
    }

    statue->remove_object();

    command("emote does some work on the statue.");
    command("emote moves his hands quickly over the statue cleaning it.");
    command("emote finishes his work on the statue.");
    FIX_EUID
    statue = clone_object(PEL_SQ_STATUE_FILE_2);
    statue->move(TO);
    command("say Here is you statue. I have cleaned it from corrosion and mud!");
    command("give "+OB_NAME(statue)+" to "+who->query_real_name());
    command("smile");
    return;
}

void
clean_statue(object statue, object who)
{
    int    *arr,
            ms = sizeof(MONEY_TYPES);

    if (!objectp(who) || !present(who, ENV(TO)))
    {
        command("shrug");
        set_alarm(2.0, 0.0, &return_object(statue, who));
        return;
    }

    if (objectp(working_on))
    {
        command("say I would like to help you, "
          + "but, alas, I am busy right now!");
        command("say Perhaps you can come back later?");
        set_alarm(2.0, 0.0, &return_object(statue, who));
        return;
    }

    if (!can_pay(PRICE_TO_CLEAN, who))
    {
        command("say I would love to clean this statue from muck "
          + "and corrosion for you.");
        command("say But it would cost you "+PRICE_TO_CLEAN/12+
                " silver coins.");
        command("say And you do not seem to be able to afford that!");
        set_alarm(2.0, 0.0, &return_object(statue, who));
        return;
    }

    command("say I will clean this statue from muck and corrosion for you, "
          + (who->query_gender() ? "Lady" : "Sir") + "!");
    command("say But I would like to ask for just "+PRICE_TO_CLEAN/12+
            " silver coins.");

    arr = pay(PRICE_TO_CLEAN, who);
    write("You pay "+text(arr) + (strlen(text(arr[ms..])) ? 
        " and receive "+text(arr[ms..])+" in return" : "") + ".\n");
    say(QCTNAME(who)+" pays "+QTNAME(TO)+".\n");

    working_on = statue;

    set_alarm(40.0 + 40.0*rnd(), 0.0, &return_statue(statue, who));

    command("emote starts working the "+statue->short()+".");
    if (!msg_id || !sizeof(get_alarm(msg_id)))
        msg_id = set_alarm(5.0, 10.0, &command("emote is busy cleaning a "+ 
                                              "statue.")); }

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if (!objectp(ob) || !objectp(from) || !interactive(from))
        return;

    if (!ob->id(PEL_SQ_STATUE_1))
    {
        set_alarm(2.0, 0.0, &return_object(ob, from));
        return;
    }
    set_alarm(2.0, 0.0, &clean_statue(ob, from));
}

int
no_reply()
{
    if (objectp(query_attack()))
        return 1;

    if (!CAN_SEE_IN_ROOM(TO) || !CAN_SEE(TO, TP))
    {
        command("confused");
        command("say Who is talking to me?");
        return 1;
    }
    return 0;
}

string
default_answer()
{
    if (no_reply())
        return "";

    command("peer "+TP->query_real_name());
    command("say I'm afraid I don't know what you are talking about.");
    command("shrug");
    return "";
}

string
ask_statue()
{
    if (no_reply())
        return "";

    command("say What do you want to know about a statue?");
    command("say Give me the statue, if you have one, and I can "
      + "tell you if it is any good.");
    command("smile");
    command("say I not only make excellent statue from stone, "
      + "I also can restore old statues, cleaning them from dirt.");
    return "";
}

string
ask_help()
{
    if (no_reply())
        return "";

    command("say Do you want to help me or do you need help?");
    command("peer "+TP->query_real_name());
    return "";
}

string
ask_work()
{
    if (no_reply())
        return "";

    command("say I work as a stone mason.");
    command("say Most of my work is done for the Steward.");
    command("say Alas, there is little work for a stone mason in the "
      + "city in recent times!");
    command("say But sometimes I can find some little tasks to make "
      + "some extra money.");
    command("say I make stone statue for visitors as souvenirs.");

    return "";
}



