/*
 * /d/Gondor/pelargir/misc/bathhouse/npc/attendant.c
 *
 * Copyright (C) 1999 by Nancy L. Mintz (Gnadnar)
 *
 * The bath attendant -- gender & desc can vary.
 *
 */

#pragma save_binary
#pragma strict_types

inherit "/d/Gondor/std/monster.c";
inherit "/d/Gondor/common/lib/logkill.c";

#include <const.h>
#include <stdproperties.h>
#include <macros.h>
#include <money.h>
#include <ss_types.h>
#include <wa_types.h>
#include "/d/Gondor/open/room_chairs/room_chairs.h";

#include "/d/Gondor/defs.h"
#include "../bath.h"

/* prototypes in order of appearance */
public void	create_gondor_monster();
public void	configure();
public void	add_introduced(string str);
public void	introduce_me(object me);
public string	ask_bath();
public string	ask_water();
public string	ask_soap();
public string	ask_towel();
public string	ask_wash_back();
public void	give_towel(object tp);
public void	give_soap(object tp);
public void	pick_up(object ob, object from);
public void	enter_inv(object ob, object from);
public void	respond_tip(int coin_count, string coin_type, object from);
public void	respond_gift(object ob, object from);


/*
 * Function name:	create_gondor_monster
 * Description	:	set up the bath attendant
 */
public void
create_gondor_monster()
{
    FIX_EUID;	/* will be cloning soap, towels */

    set_name( ({ "bath attendant", "attendant" }) );
   
    set_stats(({30, 57, 48, 37, 40, 49}));
    set_alignment(500);
    remove_prop(NPC_M_NO_ACCEPT_GIVE);
   
    set_chat_time(15);
    add_chat("Just ask if you need more soap.");
    add_chat("I can never keep enough fresh towels on hand, it seems.");
    add_chat("There's nothing more relaxing than a nice hot bath.");
    add_chat("I wish people wouldn't drop towels on the floor.");
    add_chat("Please put your towel in the basket when you're " +
	"finished with it.");
    add_chat("Please put any leftover soap in the pot before you leave.");

    add_prop(OBJ_M_NO_ATTACK, "This does not seem wise.\n");

   
    set_act_time(15);
    add_act("emote straightens a mat.");
    add_act("polishes the copper pot.");
    add_act("adds more hot water to the tubs.");
   
    set_dont_answer_unseen(1);
    set_default_answer( ({ ({ "peer @@query_player_name@@",
	"I'm afraid I can't help you with that." }) }) );

    /* call add_ask_item() even tho we need to use VBFC for all
     * of these, so it'll automatically strip leading "for" and
     * "about", and trailing ".", "?" and " ?"
     */
    add_ask_item( ({ "bath", "bathing", "baths" }),
	VBFC_ME("ask_bath"));
    add_ask_item( ({ "water", "hot water", " more hot water", "more water", }),
	VBFC_ME("ask_water")); 
    add_ask_item( ({ "soap", "more soap", }),
	VBFC_ME("ask_soap"));
    add_ask_item( ({ "towel", "a towel", "another towel", "dry towel",
	"a dry towel", "towels", "more towels", "dry towels", "bath towel",
	"a bath towel", "another bath towel", "dry bath towel",
	"a dry bath towel", "bath towels", "more bath towels",
	"dry bath towels", }),
	VBFC_ME("ask_towel"));
    add_ask_item( ({ "back", "wash back", "wash my back", "to wash my back",}),
        VBFC_ME("ask_wash_back"));
    add_ask_item( ({ "job", "work", "task", "assignment", "chore",
	"quest", "help" }),
	({ "say I'm sorry, but I don't have any task for you at present.",
	   "say I don't believe I have any jobs just now.",
	   "say Thank you, but I don't need any help today.",
	}) );

} /* create_gondor_monster */


/*
 * Function name:	configure
 * Description	:	set up name, appearance
 */
public void
configure()
{
    if (query_gender() == G_MALE)
    {
	add_name("man");
	switch(random(3))
	{
	case 0:
	    set_name("halforn");
	    set_living_name("halforn");
	    set_adj( ({ "animated", "green-eyed", }) );
	    set_race_name("elf");
	    GONDOR_MASTER->npcsize(TO, "short", "normal");
	    break;
	case 1:
	    set_name("theo");
	    set_living_name("theo");
	    set_adj( ({ "pale", "clean-shaven" }) );
	    set_race_name("human");
	    GONDOR_MASTER->npcsize(TO, "tall", "lean");
	    break;
	case 2:
	    set_name("harnor");
	    set_living_name("harnor");
	    set_race_name("dwarf");
	    set_adj( ({ "philosophical", "black-bearded" }) );
	    GONDOR_MASTER->npcsize(TO, "normal", "normal");
	    break;
	}
    }
    else
    {
	add_name("woman");
	switch(random(3))
	{
	case 0:
	    set_name("koranna");
	    set_living_name("koranna");
	    set_adj( ({ "merry", "red-haired" }) );
	    set_race_name("human");
	    GONDOR_MASTER->npcsize(TO, "tall", "plump");
	    break;
	case 1:
	    set_name("solya");
	    set_living_name("solya");
	    set_adj( ({ "calm", "black-eyed" }) );
	    set_race_name("elf");
	    GONDOR_MASTER->npcsize(TO, "normal", "lean");
	    break;
	case 2:
	    set_name("melin");
	    set_living_name("melin");
	    set_adj( ({ "gray-eyed", "round-faced" }) );
	    set_race_name("dwarf");
	    GONDOR_MASTER->npcsize(TO, "normal", "normal");
	    break;
	}
    }
} /* configure */


/*
 * Function name:	add_introduced
 * Description	:	schedule a response to an introduction
 * Arguments	:	string str -- name of the introduced living
 */
public void
add_introduced(string str)
{
    set_alarm(3.0, 0.0, &introduce_me(TP));
} /* add_introduced */


/*
 * Function name:	introduce_me
 * Description	:	respond to introductions
 * Arguments	:	object who -- person who introduced
 */
public void
introduce_me(object who)
{
    if (objectp(who) &&
	ENV(who) == ENV(TO) &&
	interactive(who) &&
    	CAN_SEE_IN_ROOM(TO) &&
	CAN_SEE(TO, who))
    {
	if (!who->query_met(query_real_name()) ||
	    who->query_wiz_level())
    	{
	    /* wizards always know the npc name, so query_met() is true.
	     * however, assume that if a wiz intro'd, we should respond
	     */
	    command("introduce me to " + who->query_real_name());
	}
	else
	{
	    command("nod happily " + OB_NAME(who));
	    command("say Nice to see you again, " + who->query_name());
	}
    }
} /* introduce_me */


/*
 * Function name:	ask_bath
 * Description	:	respond to request for bath
 * Returns	:	null str (response given via command())
 */
public string 
ask_bath()
{
    switch(TP->query_prop(PLAYER_I_BATH))
    {
    case I_AM_DRY_AND_DIRTY:
	command("smile " + OB_NAME(TP));
	command("say Enter a tub, please, and I'll bring you some soap.");
	command("emote gestures encouragingly towards the tubs.");
	break;
    case I_AM_WET_AND_DIRTY:
	command("say Well, you've made a start.");
	command("say Now, put that soap I gave you to good use!");
	command("grin . " + OB_NAME(TP));
	break;
    case I_AM_SOAPY:
	command("say Ahh, you're looking much cleaner, if a bit soapy.");
	command("wink cheerfully " + OB_NAME(TP));
	command("say This would probably be a good time to rinse yourself off.");
	break;
    case I_AM_WET_AND_CLEAN:
	if (TP->query_prop(LIVE_S_SITTING) == TUB_NAME)
	{
	    command("say You're certainly clean enough.");
	    command("say Why don't you just relax in the tub for a while?");
	    command("smile soothingly " + OB_NAME(TP));
	}
	else
	{
	    command("say All good things must come to an end.");
	    command("grin sympathetically " + OB_NAME(TP));
	    command("say It's time to dry yourself off.");
	}
	break;
    case I_AM_DRY_AND_CLEAN:
	command("say It seems you've already enjoyed a bath.");
	command("say You certainly are looking good.");
	command("wink appreciatively " + OB_NAME(TP));
	break;
    }
    return "";
} /* ask_bath */


/*
 * Function name:	ask_water
 * Description	:	respond to request for water
 * Returns	:	null str (response given via command())
 */
public string
ask_water()
{
    if (TP->query_prop(LIVE_S_SITTING) == TUB_NAME)
    {
	command("nod . " + OB_NAME(TP));
	command("say Certainly -- we have plenty of hot water!");
	TP->catch_msg(QCTNAME(TO) + " pours more hot water " +
	    "into your tub.\n");
	say(QCTNAME(TO) + " pours more hot water into " +
	    QTNAME(TP) + "'s tub.\n");
    }
    else
    {
	command("say Enter a tub and I'll be glad to bring you " +
	    "some hot water.");
	command("smile encouragingly " + OB_NAME(TP));
    }
    return "";
} /* ask_water */


/*
 * Function name:	ask_soap
 * Description	:	respond to request for soap
 * Returns	:	null str (response given via command())
 */
public string
ask_soap()
{
    if (objectp(present("soap", TP)))
    {
	command("say You already have some soap -- why do you need more?");
	command("peer " + OB_NAME(TP));
    }
    else if (TP->query_prop(LIVE_S_SITTING) == TUB_NAME)
    {
	command("say Yes, of course. It's hard to bathe without soap.");
	give_soap(TP);
    }
    else
    {
	command("say Enter a tub and I'll be glad to give you " +
	    "some soap.");
	command("smile encouragingly " + OB_NAME(TP));
    }
    return "";
} /* ask_soap */


/*
 * Function name:	ask_towel
 * Description	:	respond to request for towel
 * Returns	:	null str (response given via command())
 */
public string
ask_towel()
{
    object	*towels;
    int		state = TP->query_prop(PLAYER_I_BATH),
		s;
    
    if (state == I_AM_DRY_AND_DIRTY ||
	state == I_AM_DRY_AND_CLEAN)
    {
	command("say You are not wet -- why do you need a towel?");
	command("peer " + OB_NAME(TP));
    }
    else if (TP->query_prop(LIVE_S_SITTING) == TUB_NAME)
    {
	command("say Finish bathing and leave the tub, " +
	    "and I'll give you a towel.");
	command("smile encouragingly " + OB_NAME(TP));
    }
    else if (s = sizeof(towels = filter(all_inventory(TP), &->id(TOWEL_NAME))))
    {
	if (sizeof(filter(towels, &->query_wet())) < s)
	{
	    command("say You already have a towel.");
	    command("smile gently " + OB_NAME(TP));
	}
	else
	{
	    command("say Yes, you do need a dry towel, don't you?");
	    give_towel(TP);
	}
    }
    else
    {
	command("say I'm sorry ... I thought I'd given you a towel.");
	command("smile apologetically " + OB_NAME(TP));
	give_towel(TP);
    }
    return "";
} /* ask_towel */


/*
 * Function name:	ask_wash_back
 * Description	:	respond to request to wash back
 * Returns	:	null str (response given via command())
 */
public string
ask_wash_back()
{
    int		i;
    if (TP->query_prop(PLAYER_I_TIPPED))
    {
	if (TP->query_prop(LIVE_S_SITTING) != TUB_NAME)
	{
	    command("say Please enter a tub first.");
	    command("smile encouragingly " + OB_NAME(TP));
	    return "";
	}
	i = random(3);
	TP->catch_msg(QCTNAME(TO) + ({ 
	    " rubs some soap between " + POSSESSIVE(TO) + 
		" hands to soften it, then covers your back " +
		"with lather.\n",
	    " gently scrubs your back.\n",
	    " vigorously washes your back. Soap bubbles drift across " +
		"the room.\n",
	    })[i] );
	tell_room(ENV(TO), QCTNAME(TO) + ({ 
	    " rubs some soap between " + POSSESSIVE(TO) + 
		" hands to soften it, then covers " + QTNAME(TP) +
		"'s back with lather.\n",
	    " gently scrubs " + QTNAME(TP) + "'s back.\n",
	    " vigorously washes " + QTNAME(TP) + "'s back. Soap " +
	    "bubbles drift across the room.\n",
	    })[i], TP);
	TP->catch_msg(
	    QCTNAME(TO) + " pours a bucket of hot water over you, " +
	    "rinsing off any traces of soap.\n");
	tell_room(ENV(TO),
	    QCTNAME(TO) + " pours a bucket of hot water over " +
	    QTNAME(TP) + 
	    ", rinsing off any traces of soap.\n", TP);
	TP->add_prop(PLAYER_I_BATH, I_AM_WET_AND_CLEAN);
	return "";
    }
    command("eyebrow . " + OB_NAME(TP));
    command("emote winks and pats " +  POSSESSIVE(TO) + 
            " purse suggestively.");
    return "";
} /* ask_wash_back */


/*
 * Function name:	give_soap
 * Description	:	give someone a soap
 * Arguments	:	object tp -- the recipient
 */
public void
give_soap(object tp)
{
    object	env = ENV(TO),
		soap;

    if (!CAN_SEE_IN_ROOM(TO) ||
	!CAN_SEE(TO, tp))
    {
	return;
    }
    tp->catch_msg(QCTNAME(TO) + " gives you a bar of soap.\n");
    tell_room(env,
	QCTNAME(TO) + " gives " + QTNAME(tp) + " a bar of soap.\n",
	tp);
    soap = clone_object(SOAP_FILE);
    if (soap->move(tp))
    {
	tell_object(tp, "Oops! You dropped it.\n");
	tell_room(env,
	    QCTNAME(tp) + " drops a bar of soap.\n", tp);
	if (soap->move(env))
	{
	    soap->move(env, 1);
	}
    }
} /* give_soap */


/*
 * Function name:	give_towel
 * Description	:	give someone a towel
 * Arguments	:	object tp -- the recipient
 */
public void
give_towel(object tp)
{
    object	env = ENV(TO),
		towel;

    if (!CAN_SEE_IN_ROOM(TO) ||
	!CAN_SEE(TO, tp))
    {
	return;
    }
    tp->catch_msg(QCTNAME(TO) + " gives you a plush towel.\n");
    tell_room(env,
	QCTNAME(TO) + " gives " + QTNAME(tp) + " a plush towel.\n",
	tp);
    towel = clone_object(TOWEL_FILE);
    if (towel->move(tp))
    {
	tell_object(tp, "Oops! You dropped it.\n");
	tell_room(env,
	    QCTNAME(tp) + " drops a towel.\n", tp);
	if (towel->move(env))
	{
	    towel->move(env, 1);
	}
    }
} /* give_towel */


/*
 * Function name:	pick_up
 * Description	:	pick up soap and towels and put in proper
 *			receptacles
 * Arguments	:	object ob -- the object to retrieve
 *			object from -- its source
 */
public void
pick_up(object ob, object from)
{
    object	env = ENV(TO);

    if (!CAN_SEE_IN_ROOM(TO))
    {
	return;
    }
    if (!objectp(ob) ||
	ENV(ob) != env)
    {
	return;
    }
    if (living(from) &&
	ENV(from) == env &&
	CAN_SEE(TO, from))
    {
	command("frown . " + OB_NAME(from));
    }
    command("$get " + OB_NAME(ob));
    if (ob->id("soap"))
    {
	command("$put " + OB_NAME(ob) + " in pot");
    }
    else
    {
	command("$put " + OB_NAME(ob) + " in basket");
    }
    command("sigh");
} /* pick_up */


/*
 * Function name:	enter_inv
 * Description	:	respond to gifts
 * Arguments	:	object ob -- the gift
 *		:	object from -- its source
 */
public void
enter_inv(object ob, object from)
{
    /* if the obj is a coin and if we already have coins of its type,
     * obj will be null on return from ::enter_inv(), so use coin_type and
     * coin_count to remember about it.
     * don't have to worry about any other heap object, because
     * we'll return 'em.
     */
    string	coin_type;
    int		coin_count;

    if (ob->id("coin"))
    {
	coin_count = ob->num_heap();
	coin_type = ob->query_coin_type();
    }
    ::enter_inv(ob, from);
    if (!interactive(from))
    {
	return;
    }
    
    if (coin_count)
    {
	set_alarm(1.0, 0.0, &respond_tip(coin_count, coin_type, from));
    }
    else
    {
	set_alarm(1.0, 0.0, &respond_gift(ob, from));
    }
}


/*
 * Function name:   respond_tip
 * Description  :   respond to money from players
 * Arguments    :   int coin_count -- how many coins
 *                  string coin_type -- what type
 *                  object from -- the person who gave them
 */
public void
respond_tip(int coin_count, string coin_type, object from)
{
    int	tip;

    if (!interactive(from) ||
	ENV(from) != ENV(TO) ||
	!CAN_SEE_IN_ROOM(TO) ||
	!CAN_SEE(TO, from))
    {
	return;
    }

    if (coin_type != "platinum")
    {

	switch(coin_type)
	{
	case "copper":
            command("thank " + OB_NAME(from) + " .");
	    tip = MONEY_MERGE( ({ coin_count, 0, 0, 0, }) );
	    break;
	case "silver":
            command("thank " + OB_NAME(from));
	    tip = MONEY_MERGE( ({ 0, coin_count, 0, 0, }) );
	    break;
	case "gold":
            command("thank " + OB_NAME(from) + " warmly");
	    tip = MONEY_MERGE( ({ 0, 0, coin_count, 0, }) );
	    break;
	}
        if (tip > MIN_TIP)
        {
            from->add_prop(PLAYER_I_TIPPED,
		(tip + from->query_prop(PLAYER_I_TIPPED)));
        }
        command("emote pockets the " + coin_type + " coin" +
	    (coin_count == 1 ? "." : "s."));
    }
    else
    {
	tip = MONEY_MERGE( ({ 0, 0, 0, coin_count, }) );
        from->add_prop(PLAYER_I_TIPPED,
	    (tip + from->query_prop(PLAYER_I_TIPPED)));
        command("bow gratefully " + OB_NAME(from));
        command("say You are most generous, my " +
            (from->query_gender() == G_FEMALE ? "lady." : "lord."));
        command("emote carefully tucks the " + coin_type +
	    " coin" + (coin_count == 1 ? " away." : "s away."));
    }
} /* respond_tip */


/*
 * Function name:	respond_gift
 * Description	:	respond to gifts other than coins
 * Arguments	:	object ob -- the gift
 *		:	object from -- its source
 */
public void
respond_gift(object ob, object from)
{
    if (ob->id(TOWEL_NAME))
    {
	command("put " + OB_NAME(ob) + " in basket");
	return;
    }
    if (ob->id(SOAP_NAME))
    {
	command("put " + OB_NAME(ob) + " in pot");
	return;
    }
    if (!interactive(from) ||
	ENV(from) != ENV(TO) ||
	!CAN_SEE_IN_ROOM(TO) ||
	!CAN_SEE(TO, from))
    {
	command("shrug");
	command("$drop " + OB_NAME(ob));
	return;
    }
    if (ob->query_amount())
    {
	command("say I'm sorry, but I cannot eat while I'm working.");
    }
    else if (ob->query_soft_amount())
    {
	command("say I'm sorry, but I cannot drink while I'm working.");
    }
    else
    {
	command("say Thank you, but I don't think I need this.");
    }
    command("$give " + OB_NAME(ob) + " to " + OB_NAME(from));
    if (ENV(ob) == TO)
    {
	command("$drop " + OB_NAME(ob));
    }
} /* respond_gift */
