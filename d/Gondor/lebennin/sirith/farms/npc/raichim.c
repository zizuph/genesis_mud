/* test copy of raichim using ask_monster
 * /d/Gondor/lebennin/sirith/farms/npc/raichim.c
 * farmer for the pig & cattle farm (sirith/farms/farm1)
 *
 * Copyright (C) 1997 by Nancy L. Mintz (Gnadnar)
 *
 */

#pragma strict_types

inherit "/d/Gondor/lebennin/sirith/farms/npc/farmer";

#include <stdproperties.h>	/* for NPC_M_NO_ACCEPT_GIVE	*/
#include <ss_types.h>		/* for skills			*/
#include <macros.h>		/* for QCTNAME			*/
#include <const.h>		/* for G_FEMALE			*/
#include <money.h>		/* for MONEY_MAKE		*/
#include "/d/Gondor/defs.h"
#include "/d/Gondor/bits.h"
#include "../defs.h"

#define	HOME	(SIRITH_FARMS_DIR+"farm1/house")

/* prototypes */
public void		create_sirith_farmer();
public void		init_living();
public varargs		void arm_me();
public void		react_intro(object tp);
public void		catch_question(string question);
public int		not_here_func();
static object		pig_check(object tp);
public string		pig_answer();
varargs public string	reward_answer(object pig);


/*
 * Function name:	create_sirith_farmer
 * Description	:	set up the npc
 */
public void
create_sirith_farmer()
{
    set_name( ({ "raichim", "woman" }) );
    set_living_name("raichim");
    set_race_name("human");
    set_gender(G_FEMALE);
    add_adj( ({ "tall", "middle-aged" }) );
		/* str, dex, con, int, wis, dis */
    set_stats(({45+random(10), 45+random(10), 45+random(10),
	45+random(10), 45+random(10), 45+random(30)}));
    set_alignment(200);
    set_skill(SS_DEFENCE, 20 + random(20));
    set_skill(SS_AWARENESS, 20 + random(20));
    set_skill(SS_WEP_KNIFE, 40 + random(20));
    set_random_move(200+random(60));
    set_monster_home(HOME);

    add_prop(NPC_M_NO_ACCEPT_GIVE, " does not accepts gifts from you.\n");
    /* call npcsize to set CONT_I_HEIGHT, WEIGHT, VOLUME */
    GONDOR_MASTER->npcsize(TO, "tall", "normal");

    set_chat_time(10);
    add_chat("Druyan's a dear soul, and a hard worker.");
    add_chat("How that pig gets out of a closed pen, I'll never know.");
    add_chat("I am so exasperated with Sandros, I could spit.");
    add_chat("The pig is a lot of trouble, but I've had her for years; "+
	"I couldn't get rid of her now.");
    add_chat("I do hope the pig isn't in the crops again.");
    add_chat("I think the cows have been eating green onions; the "+
	"milk's been a little off lately.");
    add_chat("Between the pig and the chickens, we don't have a "+
	"problem with leftovers.");		/* hint, hint */
    add_chat("It was Kellis' idea to raise chickens.");

    set_act_time(10);
    add_act(VBFC_ME("open_it"));
    add_act("emote brushes dirt from the knees of her trousers.");
    add_act("emote looks you over.");

    /* respond nicely to questions */
    set_default_answer(
	({ "peer @@query_player_name@@", "shrug", }) );

    set_not_here_func("not_here_func");
    set_dont_answer_unseen(1);

    add_ask_item( ({ "pig", "pigs", "sow", "sows", "sty", "pen", "trouble",
    	"escape", "job", "work", "task", "assignment", "chore",
	"quest", "help" }), VBFC_ME("pig_answer") );
    add_ask_item( ({ "reward", "pay", "payment", "pay me" }),
	VBFC_ME("reward_answer") );

    add_ask_item( ({ "catch", "capture", "bring", "corner", "kidnap", "grab" }),
	({ "say The pig is a greedy guts.",
	   "say She's hard to coerce, but easy to lure." }) );

    add_ask_item( ({ "greedy", "greedy guts", "distracted", "memory", "lure" }),
        ({ "say As long as you've got something she wants, "+
		"the pig's tractable but easily distracted.",
	   "say She's easy to lure, if you have something "+
		"she likes, but she has a short memory.", }) );

    add_ask_item( ({ "milk", "onions", "green onions", }),
	"say You can tell where the cows grazed by "+
		"the taste of the milk." );

    add_ask_item( ({ "cows", }),
	({ "say Cows are such calm creatures.",
	   "say Cows are not much trouble to raise.",
	   "say You can tell where the cows grazed by "+
		"the taste of the milk." }) );

    add_ask_item( ({ "farm", "garden", "harvest",  "crops", }),
	({ "say The crops seem to thrive this year.",
	   "say Oh, our crops are doing well this year.",
	   "say Anyone should be able to farm "+
		" in this area; the soil is good and there's "+
		"plenty of water." }) );

    add_ask_item( ({ "vegetables", "potatoes", "carrots", "plums" }),
	({ "say The @@query_question@@ seem to thrive this year.",
	   "say Oh, our @@query_question@@ are doing well this year.",
	   "say Anyone should be able to grow @@query_question@@ "+
		" in this area; the soil is good and there's "+
		"plenty of water." }) );

    add_ask_item( ({ "thrive", "soil", "fields", "water", "river",
	"sirith", "river sirith" }),
	({ "say The river's not far away, and the soil is "+
	      "good.",
	   "say The soil around here is very rich, and the River "+
	      "Sirith provides plenty of water.",
	   "say It's easy to farm where there's rich soil "+
	      "and plenty of water.", }) );

    add_ask_item( ({ "chicken", "chickens", "hens", "speckled hens", }),
	({ "say The speckled hens are the best layers.", 
	   "say Hens vary widely in the number of eggs they give.",
	   "say Kellis is very proud of those chickens.",
	   "say We have to lock the chickens up at night; "+
		"otherwise, foxes get them.",
	}) );

    add_ask_item( ({ "egg", "eggs", "layers", }),
	({ "say The speckled hens are the best layers.", 
	   "say Hens vary widely in the number of eggs they give.",
	}) );

    add_ask_item( ({ "grain", }),
	"say I swear, the chickens and the pig prefer scraps "+
		"to good grain." );

    add_ask_item( ({ "leftovers", "scraps", "kitchen scraps", "like", "likes",
	"want", "wants", "grain", "appetites" }),
	({ "say I swear, the chickens and the pig prefer scraps "+
		"to good grain.",
	   "say The pig and the chickens eat all the kitchen scraps.",
	   "say Leftovers don't last long, given the appetites of "+
		"the chickens and the pig." }) );

    add_ask_item( ({ "animals" }),
	({ ({ "frown", 
	      "say Sandros is not very good with animals." }), 
	   "say None of the animals like Sandros.",  }) );

    add_ask_item( ({ "sandros", "mistake", "hiring" }),
	({ ({ "frown",
	      "say Sandros is not very good with animals." }),
	   "say None of the animals like Sandros.",
	   ({ "say Hiring Sandros may have been a mistake.",
	      "say He's not been much help." }),
	   ({ "sigh",
	      "say It's hard to get much work out of Sandros." }) }) );

    add_ask_item( ({ "sheep" }),
	({ "smile", "say Druyan is doing very well with her sheep." }) );
    add_ask_item( ({ "cider" }),
	"say Druyan makes an excellent cider." );
    add_ask_item( ({ "bees" }),
	"say Druyan is a good neighbor, but don't annoy her bees!" );

    add_ask_item( ({ "druyan", "neighbor", "neighbors", }),
	({ ({ "smile",
	      "say Druyan is doing very well with her sheep." }),
	   "say Druyan makes an excellent cider.",
	   "say Druyan is a good neighbor, but don't annoy her bees!"
	}) );

    add_ask_item( ({ "kellis", "husband" }),
	({ ({ "smile", "say Kellis is a born farmer." }),
	   "say Kellis? He'll be around the farm somewhere.",
	   "say Kellis and I have farmed here for years." }) );

} /* create_sirith_farmer */


/*
 * Function name:	init_living
 * Description	:	load the pigsty
 */
public void
init_living()
{
     ::init_living();
     PIGSTY->short();	/* we'll very likely need the sty */
} /* init_living */


/*
 * Function name: arm_me
 * Description:   set our equipment before calling parent's arm_me().
 */
public varargs void
arm_me()
{
    object	obj;
    set_equipment( ({ (ARM_DIR + "tunic"),
	(SIRITH_FARMS_DIR + "obj/boots"), 
	(ARM_DIR + "trousers"),
	(SIRITH_FARMS_DIR + "obj/knife") }) );
    ::arm_me();
    if (objectp(obj= present("tunic", TO)))
    {
	obj->configure("faded", "blue", "cotton", "loose", "");
    }
    if (objectp(obj= present("trousers", TO)))
    {
	obj->configure("tightly-woven", "heavy", "cloth",
	    "loose-fitting",
	    ", with leather patches reinforcing the knees");
    }
} /* arm_me */


/*
 * Function name:	react_intro
 * Description	:	respond to introduction
 * Arguments	:	object tp -- the person who intro'd
 */
public void
react_intro(object tp)
{
    if (ENV(tp) != ENV())
    {
        command("shrug");
        return;
    }
    command("say Greetings, " + tp->query_name() + ".");
    command("introduce me to "+tp->query_real_name());
} /* react_intro */


/*
 * Function name:	catch_question
 * Description	:	intercept /std/act/asking.c's catch_question() to:
 *			1) strip leading "for", "about" and trailing "?"
 *			2) do extra parsing if asking for hints
 *			3) remember the question
 * Arguments:		string question -- whatever the player asked
 */
public void
catch_question(string question)
{
    string *tmp_arr, *pig_arr, stuff1, stuff2, stuff3, new_question;

    if (objectp(query_attack()))
    {
	return;	/* no answers if fighting */
    }

    new_question = LOW(question);
    if (strlen(new_question))
    {
	/* strip off leading "for", "about" and trailing " ?" */
	tmp_arr = ({ "for", "about" });
	if (parse_command(new_question, ({}), "%p %s", tmp_arr, stuff1))
	{
	    new_question = stuff1;
	}
	if (sscanf(new_question, "%s ?", stuff1) ||
	    sscanf(new_question, "%s?", stuff1))
	{
	    new_question = stuff1;
	}

	/* match on:
	 * 	[ how do i, can i, should i, does one, ...]
	 *	    get / take / capture ... 
	 *   	    [ a, the, your, that mangy ... ]
	 *	    pig / sow
	 *	[ and bring it home or whatever ]
	 * and set question to the verb.
	 */
	tmp_arr = ({ "get", "take", "capture", "corner", "catch",
    		      "kidnap", "bring", "grab", "lure" });
	pig_arr = ({ "pig", "sow" });

	if (parse_command(new_question, ({}), "%s %p %s %p %s",
		stuff1, tmp_arr, stuff2, pig_arr, stuff3))
	{
	    new_question = tmp_arr[0];
	}
	else 
	{
	    tmp_arr = ({ "like", "likes", "want", "wants" });
	    pig_arr = ({ "pig", "sow", "she" });
	    /*	what
	     *      [does that foolish /would the /is it that ...]
	     *      pig / sow / she
	     *      [ usually / thinks she / ... ]
	     *      want[s] / like[s] 
	     */
	    if (parse_command(new_question, ({}), "'what' %s %p %s %p %s",
	    	stuff1, pig_arr, stuff2, tmp_arr, stuff3))
	    {
		new_question = tmp_arr[0];
	    }
	}
    }
    ::catch_question(new_question);
} /* catch_question */


/*
 * Function name:	not_here_func
 * Description	:	called when player asks question & leaves
 * Returns	:	0 -> don't answer the question
 */
public int
not_here_func()
{
     command("shrug");
     return 0;
} /* not_here_func */


/*
 * Function name:	pig_check
 * Description	:	check whether this player led pig to sty
 * Arguments	:	object tp -- this player
 * Returns	:	object pig if successful, NULL if not
 */
static object
pig_check(object tp)
{
    object	pigsty,
		pig;

    if (!objectp(tp) ||
	!tp->query_prop(SIRITH_I_LED_PIG))
    {
	return 0;
    }

    pigsty = find_object(PIGSTY);

    if (objectp(pigsty) &&
	objectp(pig = pigsty->query_pig()) &&
    	ENV(pig) == pigsty &&
    	pig->query_prop(SIRITH_S_WAS_LED) == tp->query_real_name())
    {
	return pig;
    }
    return 0;
} /* pig_check */


/*
 * Function name:	pig_answer
 * Description	:	respond to questions about the pig
 * Returns	:	null string ... response is gen'd via command()
 *
 *
 * have to keep this one VBFC, since we need to call pig_check
 *
 *  add_ask_item( ({ "pig", "pigs", "sow", "sows", "sty", "pen", "trouble",
 *  	"escape", "job", "work", "task", "assignment", "chore",
 *	"quest", "help" }),
 */
public string
pig_answer()
{
    object	pig,
		pigsty;
    string	question = query_question();

    if (objectp(pig = pig_check(TP)))
    {
	return reward_answer(pig);
    }

    command("sigh");
    switch (random(4))
    {
    case 0:
	command("say That pig can escape any pen!");
	break;
    case 1:
	command("say It's more than I can do to keep the pig in her sty.");
	break;
    case 2:
	command("say I don't know how she does it, but the pig often escapes.");
	break;
    case 3:
	command("say It's hard to keep that pig in her sty.");
	break;
    }
    if (question == "pig" ||
	question == "pigs" ||
	question == "sow" ||
    	question == "sows" ||
	question == "sty" ||
	question == "pen" ||
    	question == "escape" ||
	question == "trouble")
    {
	/* they didn't explicity ask for job ... */
	return "";
    }

    /* "job", "work", "task", "assignment", "quest", "help"
     * the word "lure" is a hint re further question
     */
    if (objectp(pigsty = find_object(PIGSTY)) &&
    	pigsty->query_pig_env() == pigsty)
    {
	command("say The last time I checked, the pig was where she belonged, "+
		"so I don't need your help just now.");
	command("say However, if you ever see do her wandering the fields, "+
		"please lure her back to the sty.");
    }
    else
    {
	command("say She's probably in the crops right now.");
	command("say If you see her wandering the fields, please "+
	    "lure her back to the sty.");
    }
    START_QUEST(TP, "SIRITH PIG (LED HOME)");
    command("say I'd certainly reward your efforts.");
    return "";
} /* pig_answer */


/*
 * Function name:	reward_answer
 * Description	:	quest done -- reward the player
 * Arguments	:	object pig -- if set, no need to call pig_check()
 * Returns	:	null string ... response is gen'd via command()
 *
 * have to keep this one VBFC, since we need to call pig_check,
 * hand out rewards, etc
 *
 *  add_ask_item( ({ "reward", "pay", "payment", "pay me" }),
 *
 */
varargs public string
reward_answer(object pig = 0)
{
    object	sty, tp = TP;

    if (!objectp(pig) &&
	!objectp(pig = pig_check(tp)))
    {
    	command("say I'm sorry, "+
	   (tp->query_met(TO) ? tp->query_name() : tp->query_nonmet_name())+
	   ", but you haven't completed the job.");
	return "";
    }

    pig->remove_prop(SIRITH_S_WAS_LED);
    tp->remove_prop(SIRITH_I_LED_PIG);
    command("smile "+tp->query_real_name());
    command("say You brought the pig back, "+
	( tp->query_met(TO) ?
	      tp->query_name() : tp->query_nonmet_name() )+"!");
    command("say Thank you very much!");
    MONEY_MAKE_GC(SIRITH_PIG_GOLD)->move(TO);
    command("say Here is a little something for your help.");
    command("give "+SIRITH_PIG_GOLD+" gold coins to "+
	tp->query_real_name());
    if (!tp->test_bit("Gondor", SIRITH_PIG_GROUP, SIRITH_PIG_BIT))
    {
	tp->set_bit(SIRITH_PIG_GROUP, SIRITH_PIG_BIT);
        tp->add_exp_quest(SIRITH_PIG_EXP);
        tp->adjust_alignment(SIRITH_PIG_ALIGN);
        tp->catch_tell("You feel more experienced!\n");
        LOG_QUEST(tp, SIRITH_PIG_EXP, "SIRITH PIG (LED HOME)");
	DEBUG_LOG(tp->query_real_name()+" led pig home!\n");
    }
    return "";
} /* reward_answer */

