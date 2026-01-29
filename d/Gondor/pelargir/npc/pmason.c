/*
 * /d/Gondor/pelargir/npc/pmason.c
 *
 * Modification history:
 *	14-Feb-98, Gnadnar:	added responses to questions re father;
 *				added prototypes and function comments;
 *				use std/act/asking's dont_answer_unseen
 *				instead of rolling our own.
 * Gwyneth 4 November 2000 - Replaced ~elessar/lib/goodkill.h with
 *                           /d/Gondor/common/lib/logkill.c
 */

#pragma strict_types

inherit "/d/Gondor/pelargir/npc/pelargir_npc.c";
inherit "/lib/trade";

#include <macros.h>
#include <money.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/common/lib/logkill.c"
#include "/d/Gondor/pelargir/lib/statue_quest.h"

#define PRICE_TO_CLEAN	24

/* prototypes */
void	create_pelargir_npc();
void	intro_me(object tp);
void	add_introduced(string name);
void	return_object(object ob, object who);
void	return_statue(object statue, object who);
void	clean_statue(object statue, object who);
void	enter_inv(object ob, object from);
string	default_answer();
string	ask_statue();
string	ask_help();
string	ask_work();
string	ask_father();


int     msg_id;
object  working_on;

/*
 * Function name:	create_pelargir_npc
 * Description	:	create the npc
 */
void
create_pelargir_npc() 
{
    set_name("warloe");
    add_name(({"mason", "stone mason"}));
    set_race_name("human");
    set_adj(({"slender","young"}));
    set_long(BSN("Warloe spends all his time chipping and carving "+
        "away at the stone statues."));

    default_config_npc(35);
    set_base_stat(SS_CON,75);
 
    set_alignment(70);

    set_chat_time(4);
    add_chat("Alas, I miss my father very much.");
    add_chat("I keep myself busy making statues... do you want one?");
    add_chat("I only make the best. They're perfect likenesses!");
    add_chat("One day I'll make enough money to visit my family.");
    add_chat("Give a statue to your sweetie.");
    add_chat("Watch out for the stone chips on the floor.");
    add_chat("Fiddlesticks!! I hate it when i mess up!");

    set_cchat_time(4);
    add_cchat("My father has powerful friends!");
    add_cchat("Have mercy!");
    add_cchat("May the stones of the road crumble under your feet!");
    add_cchat("You'll regret this!");
    add_cchat("Guards! Help!");

    set_default_answer(VBFC_ME("default_answer"));
    set_dont_answer_unseen(1);
    add_ask(({"statue", "clean statue", "restore statue" }),
        VBFC_ME("ask_statue"));
    add_ask(({"help", }), VBFC_ME("ask_help"));
    add_ask(({"work", }), VBFC_ME("ask_work"));
    add_ask(({"father","family" }), VBFC_ME("ask_father"));

    remove_prop(NPC_M_NO_ACCEPT_GIVE);
    /* need this since we want to trade: */
    config_default_trade();
}

/*
 * Function name:	intro_me
 * Arguments	:	object tp -- the person who introduced to us
 */
void
intro_me(object tp)
{
    if (!objectp(tp) || !interactive(tp) || !CAN_SEE_IN_ROOM(TO) ||
        !CAN_SEE(TO, tp) || !present(tp, ENV(TO)))
        return;
    command("introduce me to "+tp->query_real_name());
}


/*
 * Function name:	add_introduced
 * Description	:	add the name of a living who has introduced
 *		 	herself to us
 * Arguments	:	string name -- name of the introduced living
 */
void
add_introduced(string name)
{
    object  tp;

    if (!strlen(name))
        name = TP->query_real_name();

    if (!strlen(name) || !objectp(tp = find_player(name)))
        return;

    if (tp->query_met(query_real_name()) && !tp->query_wiz_level())
        return;

    set_alarm(2.0, 0.0, &intro_me(tp));
}

int query_knight_prestige() { return -5; }


/*
 * Function name:	return_object
 * Description	:	return gifts of anything but coins (or the
 *			statue, but that's handled separately)
 * Arguments	:	object ob -- the gift
 *			object who -- the giver
 */
void
return_object(object ob, object who)
{
    if (!objectp(ob))
    {
        return;
    }
    if (ob->id("coin") || ob->id("coins"))
    {
        command("gasp");
        command("say Why, thank you, my dear "
          + (who->query_gender() ? "Lady" : "Sir") + "!");
        command("thank "+who->query_real_name());
        command("say This will help me!");
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
        command("say Oh! So no one else wants it? "+
		"So what should I do with it?");
    }
}

/*
 * Function name:	return_statue
 * Descritpion	:	finish cleaning and return the statue
 * Arguments	:	object statue -- the statue
 *			object who -- the person who gave it to us
 */
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

/*
 * Function name:	clean_statue
 * Description	:	charge for cleaning statue, and start to work
 * Arguments	:	object statue -- the statue
 *			object who -- the person who gave it to us
 */
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
                                              "statue.")); 
}


/*
 * Function name:	enter_inv
 * Description	:	mask parent so we respond to being given things
 * Arguments	:	object ob -- the item entering our inventory
 *			object from -- where it came from
 */
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


/*
 * Function name:	default_answer
 * Description	:	respond to questions we don't understand
 * Returns	:	null string  -- does the response via 'command'
 */
string
default_answer()
{
    if (objectp(query_attack()))
        return "";

    command("peer "+TP->query_real_name());
    command("say I'm afraid I don't know what you are talking about.");
    command("shrug");
    return "";
}

/*
 * Function name:	ask_statue
 * Description	:	respond to questions about "statue"
 * Returns	:	null string  -- does the response via 'command'
 */
string
ask_statue()
{
    if (objectp(query_attack()))
        return "";

    command("say What do you want to know about a statue?");
    command("say Give me the statue, if you have one, and I can "
      + "tell you if it is any good.");
    command("smile");
    command("say I not only carve excellent statues from stone, "
      + "I also can clean and restore old statues.");
    return "";
}

/*
 * Function name:	ask_help
 * Description	:	respond to questions about "help"
 * Returns	:	null string  -- does the response via 'command'
 */
string
ask_help()
{
    if (objectp(query_attack()))
        return "";

    command("say Can you be more specific, please?");
    command("peer "+TP->query_real_name());
    return "";
}

/*
 * Function name:	ask_work
 * Description	:	respond to questions about "work"
 * Returns	:	null string  -- does the response via 'command'
 */
string
ask_work()
{
    if (objectp(query_attack()))
        return "";

    command("say I work as a stone mason.");
    command("say Most of my work is done for the city council.");
    command("say Alas, there is little work for a stone mason in the "
      + "city in recent times!");
    command("say But sometimes I can find some little tasks to make "
      + "some extra money.");
    command("say I make stone statue for visitors as souvenirs.");

    return "";
}

/*
 * Function name:	ask_father
 * Description	:	respond to questions about "father", "family"
 * Returns	:	null string  -- does the response via 'command'
 */
string
ask_father()
{
    if (objectp(query_attack()))
        return "";

    command("say My father no longer works as a stone mason.");
    command("say He tends to lead a retired life now, "+
   	    "although he does advise the city council on occasion.");

    return "";
}
