/*
 * /d/Gondor/pelargir/npc/painter.c
 *
 * Modification log:
 *	7 Jan 99, Gnadnar: clean up, respond to questions
 */

#pragma strict_types

inherit "/d/Gondor/pelargir/npc/pelargir_npc";
inherit "/lib/trade";

#include <macros.h>
#include <money.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/pelargir/lib/statue_quest.h"

#define PRICE_TO_PAINT	48

int     msg_id,
        msg_no;
object  working_on;

/* prototypes */
public void	create_pelargir_npc();
public void	arm_me();
public int	query_knight_prestige();
public void	return_object(object ob, object who);
public void	return_statue(object statue, object who);
public void	do_msg();
public void	paint_statue(object statue, object who);
public void	enter_inv(object ob, object from);
public void	ask_help();
public void	ask_statue();
public string	default_answer();

/*
 * Function name:	create_pelargir_npc
 * Description	:	set up the orphan
 */
public void
create_pelargir_npc()
{
    set_name("orphan");
    add_name("painter");
    set_race_name("human"); 
    set_adj("spotted");
    set_short("spotted orphan");
    set_pshort("spotted orphans");
    set_long(BSN("This young orphan is covered in spots of paint " +
         "and chalk. His eyes give off a creative gleam."));
    set_stats(({ (5 + random(10)), (5 + random(10)), (5 + random(10)),
          (5 + random(10)), (5 + random(10)), (5 + random(30)) }));

    set_alignment(50);
    set_skill(SS_WEP_KNIFE, (20 + random(20)));
    set_skill(SS_DEFENCE, (20 + random(20)));
    set_skill(SS_AWARENESS, (20 + random(20)));

    set_chat_time(20);
    add_chat("If it weren't for art, I'd not survive a day.");
    add_chat("I once painted on a fisherman's dock. I'm sure it's " +
	"washed away now.");
    add_chat("I sure could use some extra coins; paint and chalk are " +
	"expensive.");
    add_chat("Not much left to paint, do you have any ideas?");
    add_chat("I'm not sure this is any better than being homeless.");
    add_chat("I'll bet I came from a noble family.");
    add_chat("Excuse me, would you like to take me home?");
    add_chat("I never even knew my parents.");

    set_default_answer(VBFC_ME("default_answer"));
    set_dont_answer_unseen(1);
    add_ask(({"help"}), VBFC_ME("ask_help"));
    add_ask(({"statue", "paint statue"}), VBFC_ME("ask_statue"));

    remove_prop(NPC_M_NO_ACCEPT_GIVE);
    /* need this since we want to trade: */
    config_default_trade();
} /* create_pelargir_npc */


/*
 * Function name:	arm_me
 * Description	:	clone & wear equipment
 */
public void
arm_me()
{
    FIX_EUID
    clone_object(PELAR_DIR + "obj/bknife")->move(TO);
    command("wield knife");

    clone_object(PELAR_DIR + "obj/bcoat")->move(TO);
    clone_object(PELAR_DIR + "obj/orpants")->move(TO);
    command("wear all");
} /* arm_me */

/* solamnian prestige */
int     query_knight_prestige() {return (-3);}


/*
 * Function name:	return_object
 * Description	:	give back an object (or keep coins)
 * Arguments	:	object ob -- the object to return
 *			object who -- the person who gave it to us
 */
public void
return_object(object ob, object who)
{
    if (!objectp(ob) ||
	!objectp(who))
    {
	return;
    }
    if (ob->id("coin") ||
	ob->id("coins"))
    {
        command("gasp");
        command("say Why, thank you, my dear "
          + (who->query_gender() ? "Lady" : "Sir") + "!");
        command("thank " + OB_NAME(who));
        command("smile");
        return;
    }

    if (objectp(who) &&
	present(who, ENV(TO)))
    {
        command("give " + OB_NAME(ob) + " to " + OB_NAME(who));
    }
    else
    {
        command("drop " + OB_NAME(ob));
    }
} /* return_object */


/*
 * Function name:	return_statue
 * Description	:	return finished statue
 * Arguments	:	object statue -- the work of art
 *			object who -- the person to give it to
 */
public void
return_statue(object statue, object who)
{
    remove_alarm(msg_id);
    msg_id = 0;

    if (!objectp(who) ||
	!present(who, ENV(TO)))
    {
        command("sigh");
        command("say What shall I do with this statue now?");
        command("drop statue");
        working_on = 0;
        return;
    }

    statue->remove_object();

    command("emote finishes painting the small statue.");
    FIX_EUID
    statue = clone_object(PEL_SQ_STATUE_FILE_3);
    statue->move(TO);

    command("say Here is your statue!");
    command("give statue to " + OB_NAME(who));
    command("smile");
    return;
} /* return_statue */


/*
 * Funciton name:	do_msg
 * Description	:	issue a msg re progress of work
 */
public void
do_msg()
{
    switch (msg_no++)
    {
    case 0: command("emote begins to paint the statue.");                break;
    case 1:
        command("emote covers the statue with sweeping motions of his brush.");
        break;
    case 2: command("emote squints as he adds a small detail.");         break;
    case 3: command("emote is busy painting a small statue.");           break;
    case 4: command("emote takes care as he adds some fine detail.");    break;
    default: command("emote is busy painting a small statue.");          break;
    }
} /* do_msg */


/*
 * Function name:	paint_statue
 * Description	:	start working on a statue
 *			(if we're idle, they can pay, etc)
 * Arguments	:	object statue -- the work of art
 *			object who -- person who gave it to us
 */
public void
paint_statue(object statue, object who)
{
    int    *arr,
            ms = sizeof(MONEY_TYPES);

    if (!objectp(who) ||
	!present(who, ENV(TO)))
    {
        command("shrug");
        set_alarm(2.0, 0.0, &return_object(statue, who));
        return;
    }

    if (objectp(working_on))
    {
        command("say I would like to paint this statue, "
          + "but, alas, I am busy right now!");
        command("say Perhaps you can come back later?");
        set_alarm(2.0, 0.0, &return_object(statue, who));
        return;
    }

    if (!can_pay(PRICE_TO_PAINT, who))
    {
        command("say I would love to paint this statue for you!");
        command("say But it would cost you " + (PRICE_TO_PAINT/12)
	    + " silver coins.");
        command("say And you do not seem to be able to afford that!");
        set_alarm(2.0, 0.0, &return_object(statue, who));
        return;
    }

    command("say I will paint this statue for you, my dear "
        + (who->query_gender() ? "Lady" : "Sir") + "!");
    command("say But I would like to ask for just " + (PRICE_TO_PAINT/12)
	+ " silver coins.");

    arr = pay(PRICE_TO_PAINT, who);
    write("You pay " + text(arr) + (strlen(text(arr[ms..])) ? 
        " and receive " + text(arr[ms..]) + " in return" : "") + ".\n");
    say(QCTNAME(who) + " pays " + QTNAME(TO) + ".\n");

    working_on = statue;

    set_alarm((20.0 + 20.0*rnd()), 0.0, &return_statue(statue, who));

    command("emote starts painting the " + statue->short() + ".");
    if (!msg_id ||
	!sizeof(get_alarm(msg_id)))
    {
        msg_no = 0;
        msg_id = set_alarm(5.0, 5.0, do_msg);
    }
} /* paint_statue */


/*
 * Function name:	enter_inv
 * Description	:	respond to gifts
 * Arguments	:	object ob -- the gift
 *			object from -- its source
 */
public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if (!objectp(ob) ||
	!objectp(from) ||
	!interactive(from))
    {
        return;
    }

    if (!ob->id(PEL_SQ_STATUE_2))
    {
        set_alarm(2.0, 0.0, &return_object(ob, from));
        return;
    }
    set_alarm(2.0, 0.0, &paint_statue(ob, from));
} /* enter_inv */


/*
 * Function name:	ask_statue
 * Description	:	respond to questions about "statue"
 * Returns	:	null string  -- does the response via 'command'
 */
public string
ask_statue()
{
    if (objectp(query_attack()))
    {
        return "";
    }

    command("say Do you have a statue that needs painting?");
    command("smile hopefully");
    command("say Just give me the statue and I'll see what i can do.");
    return "";
} /* ask_statue */

/*
 * Function name:	ask_help
 * Description	:	respond to questions about "help"
 * Returns	:	null string  -- does the response via 'command'
 */
public string
ask_help()
{
    if (objectp(query_attack()))
    {
        return "";
    }

    command("peer " + OB_NAME(TP));
    command("say If it's painting you need, I probably can help, " +
    	"but I need to know more about it.");
    return "";
} /* ask_help */


/*
 * Function name:	default_answer
 * Description	:	respond to questions we don't understand
 * Returns	:	null string  -- does the response via 'command'
 */
public string
default_answer()
{
    if (objectp(query_attack()))
        return "";

    command("peer " + OB_NAME(TP));
    command("say I'm afraid I don't know what you are talking about.");
    command("shrug");
    return "";
} /* default_answer */
