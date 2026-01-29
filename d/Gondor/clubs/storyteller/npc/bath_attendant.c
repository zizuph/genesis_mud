/*
 * /d/Gondor/clubs/storyteller/npc/bath_attendant.c
 * Borrowed from:
 * /d/Gondor/common/guild/north/npc/bath_attendant.c
 *
 * Modification history:
 *	28-Feb-98, Gnadnar:	vary gender (only fair to have a
 *		cute dude handing out towels some of the time) and
 *		conform to domain.rules.
 */

#pragma save_binary
#pragma strict_types

inherit "/d/Gondor/std/monster.c";
inherit "/d/Gondor/common/lib/logkill.c";
inherit "/d/Gondor/common/lib/make_money.c";

#include <const.h>
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>

#include "/d/Gondor/defs.h"

#define RON_I_HAVE_BATHED  "_RoN_i_have_bathed"
#define WET                 "i_am_wet"
#define BATHING             "i_am_bathing"
#define GOT_SOAP            "got_extra_soap"

public void	create_gondor_monster();
public string	ask_towel();
public string	ask_soap();
public string	ask_water();
public string	ask_bath();
public void	give_towel(object tp);
public void	give_soap(object tp);
public void	add_introduced(string str);
public void	introduce_me(object me);


/*
 * Function name:	create_gondor_monster
 * Description	:	set up the bath attendant
 */
public void
create_gondor_monster()
{
    string gender;

    if (random(2))
    {
        set_name("ulgorn");
	set_living_name("_lanforn_");
	set_gender(G_MALE);
        gender = "man";
   
    }
    else
    {
	set_name("meraith");
	set_living_name("_liniel_");
	set_gender(G_FEMALE);
        gender = "woman";
    }

    add_name(({ "bath attendant", "attendant", gender }));
    set_title("the bath attendant for the Storytellers");
    set_race_name("human");
    set_adj(({"young", "shy"}));
    set_long("This young " + gender + " is here to help the Storytellers "
        + "who have come for a bath. " + capitalize(query_pronoun())
        + " takes care of warming up enough hot water, bringing in fresh "
        + "towels, and anything else required for a nice bath. You may ask "
        + query_objective() + " about bathing if you need instructions.\n");

    Equipment = ({ (MINAS_DIR + "obj/mtunic") });
    set_stats(({30, 57, 48, 37, 40, 49}));
    get_money();
    set_skill(SS_DEFENSE, 29 + random(50));
    set_skill(SS_UNARM_COMBAT, 30 + random(42));
    set_skill(SS_AWARENESS, 30 + random(19));
    set_alignment(500);
    add_prop(CONT_I_HEIGHT, 180);	/* normal */
    add_prop(CONT_I_WEIGHT, 63000);	/* lean */
   
    set_chat_time(6);
    add_chat("How warm would you like your bath water?");
    add_chat("Would you be needing any more soap, friend Teller?");
    add_chat("I can never keep enough fresh towels on hand, it seems.");
    add_chat("Don't forget your belongings -- you put them in the stand.");
    add_chat("Where have you been scouting lately?");
    add_chat("Have you ever been to Minas Tirith? I like it there.");
    add_chat("Have you ever been near Minas Morgul? Now there's a scary place.");
    add_chat("What's the harm in a little bath water? Don't be afraid.");
    add_chat("The fire needs more wood, I think.");
   
    set_act_time(5);
    add_act("emote stokes the fire up some more.");
    add_act("tap");
    add_act("ponder where the clean towels are.");
    add_act("emote starts heating another pot of water.");
    add_act("emote gathers some towels from the hamper and takes them "
	  + "for cleaning.");
   
    add_ask(({"for bath", "help", "bathing", "baths", "about bath",
	     "bath", "about bathing"}), ask_bath); 
    add_ask(({"towel", "for towel", "about towel"}), ask_towel);
    add_ask(({"soap", "more soap", "for more soap", "for soap",
	"about soap"}), ask_soap);
    add_ask(({"water", "extra water", "for extra water", "for water",
	     "more water", "for more water"}),
	   ask_water); 
    /* for some reason, set_default_answer seems to require a string arg */
    set_default_answer("The bath attendant says: I'm very sorry, but I don't "
        + "understand your question.\n");
   
} /* create_gondor_monster */

/*
 * Function name:	ask_towel
 * Description	:	respond to request for towel
 * Returns	:	null str (response given via command())
 */
public string
ask_towel()
{
    object	tp = TP;
   
    if (objectp(present("towel", tp)))
    {
	command("say No, no, you already have a towel!");
	command("smile shy");
    }
    else if (tp->query_prop(BATHING))
    {
	command("say Leave the tub first, then I will give you a towel.");
    }
    else if (!tp->query_prop(WET))
    {
	command("say But you don't need a towel -- you are quite dry.");
    }
    else
    {
	give_towel(tp);
    }
    return "";
} /* ask_towel */


/*
 * Function name:	ask_soap
 * Description	:	respond to request for soap
 * Returns	:	null str (response given via command())
 */
public string
ask_soap()
{
    int		day = CLOCK->query_day();
    object	tp = TP;
   
    if (objectp(present("soap", tp)))
    {
	command("say No, no, you already have some soap!");
	command("smile shy");
    }
    else if (!tp->query_prop(BATHING))
    {
	if (!tp->query_prop(RON_I_HAVE_BATHED))
	{
	    command("say You should enter the tub first; you wouldn't want to "
		  + "bathe dry, would you?");
	    if (tp->query_gender() != query_gender())
	    {
		command("say I will look away.");
		command("blush");
                write(TO->query_The_name(tp) + " turns "+POSSESSIVE(TO)
		            + " back on you so you can get undressed.\n");
		say(QCTNAME(TO)+" turns "+POSSESSIVE(TO)
		            + " back on "+QTNAME(tp)+".\n");
	    }
	}
	else
    	{
	    command("say You've already dried off; surely you don't "
	          + "need more soap now.");
	}
    }
    else
    {
	give_soap(tp);
    }
    return "";
} /* ask_soap */


/*
 * Function name:	ask_water
 * Description	:	respond to request for water
 * Returns	:	null str (response given via command())
 */
public string
ask_water()
{
    object	tp = TP;
    if (!tp->query_prop(BATHING) )
    {
	command("say Well, undress and get into a tub, "
	      + "and I'll bring you water.");
	command("smile " + tp->query_name());
    }
    else if (tp->query_prop(BATHING))
    {
	command("say You want more water? Just wait a second.");
	command("emote fetches a pot that was heating over the fire.");
	say(QCTNAME(TO) + " pours the hot water slowly over " + QTNAME(tp) +
		 ", who gives a yelp in surprise.\n", tp);
        write(TO->query_The_name(tp) + " pours the hot water over you, and "
		     + "you yelp in surprise at how hot it is.\n");
	command("giggle");
    }
    return "";
} /* ask_water */


/*
 * Function name:	ask_bath
 * Description	:	respond to request for bath
 * Returns	:	null str (response given via command())
 */
public string 
ask_bath()
{
    object	tp = TP;
    if (tp->query_prop(BATHING))
    {
	command("say Well, you seem to have the hang of it...");
	command("say When you've finished bathing, you can stand up, ");
	command("say And I'll bring you a towel, or you can splash "); 
	command("say as long as you like, I'll keep the water hot.");
	command("smile kind");
    }
    else if (tp->query_prop(WET))
    {
	command("say You should dry yourself, silly.");
	command("smile merrily");
	if (!present("towel", tp))
	{
	    command("say Here, I'll get you a towel.");
	    give_towel(tp);
	}
    }
    else if (tp->query_prop(RON_I_HAVE_BATHED))
    {
	command("say You've already bathed, I believe.");
    }
    else
    {
	command("say It's really quite simple -- just enter a tub. "
	      + "Then I'll bring over the hot water and soap and "
	      + "you can get to washing yourself.");
	command("smile encouragingly");
    }
    return "";
} /* ask_bath */


/*
 * Function name:	give_towel
 * Description	:	give someone a towel
 * Arguments	:	object tp -- the recipient
 */
public void
give_towel(object tp)
{
    object	to = TO,
		env = ENV(to),
		towel;

    write(to->query_The_name(tp)+" gives you a plush towel.\n");
    tell_room(env,
	QCTNAME(to) + " gives "+QTNAME(tp)+" a plush towel.\n",
	tp);
    FIX_EUID;
    towel = clone_object(STORYT_DIR + "obj/towel");
    if (towel->move(tp))
    {
	write("Oops! You dropped it.\n");
	tell_room(env, QCTNAME(tp) + " drops a towel.\n", tp);
	if (towel->move(env))
	{
	    towel->move(env, 1);
	}
    }
} /* give_towel */


/*
 * Function name:	give_soap
 * Description	:	give someone a soap
 * Arguments	:	object tp -- the recipient
 */
public void
give_soap(object tp)
{
    object	to = TO,
		env = ENV(to),
		soap;

    write(to->query_The_name(tp)+" gives you a bar of soap.\n");
    tell_room(env,
	QCTNAME(to) + " gives "+QTNAME(tp)+" a bar of soap.\n",
	tp);
    FIX_EUID;
    soap = clone_object(STORYT_DIR + "obj/soap");
    if (soap->move(tp))
    {
	write("Oops! You dropped it.\n");
	tell_room(env, QCTNAME(tp) + " drops a bar of soap.\n", tp);
	if (soap->move(env))
	{
	    soap->move(env, 1);
	}
    }
} /* give_soap */


/*
 * Function name:	add_introduced
 * Description	:	schedule a response to an introduction
 * Arguments	:	string str -- name of the introduced living
 */
public void
add_introduced(string str)
{
    object	pl;
    if (objectp(pl = present(str, ENV(TO))))
    {
	set_alarm(3.0, 0.0, &introduce_me(pl));
    }
} /* add_introduced */


/*
 * Function name:	introduce_me
 * Description	:	respond to introductions
 * Arguments	:	object who -- person who introduced
 */
public void
introduce_me(object who)
{
    /* wizards always know the npc name, so query_met() is true.
     * however, assume that if a wiz intro'd, we should respond
     */
    if (objectp(who) &&
	ENV(who) == ENV(TO) &&
	interactive(who) &&
    	CAN_SEE_IN_ROOM(TO) &&
	CAN_SEE(TO, who) &&
    	(!who->query_met(query_name()) ||
	 who->query_wiz_level()))
    {
	command("introduce me to "+who->query_real_name());
    }
} /* introduce_me */
