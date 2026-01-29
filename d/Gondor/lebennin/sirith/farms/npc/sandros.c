/*
 * /d/Gondor/lebennin/sirith/farms/npc/sandros.c
 * farmer for the pig & cattle farm (sirith/farms/farm1)
 *
 * Copyright (C) 1997 by Nancy L. Mintz (Gnadnar)
 *
 */

#pragma strict_types

inherit "/d/Gondor/lebennin/sirith/farms/npc/farmer";

#include <stdproperties.h>	/* for CONT_I_HEIGHT, etc */
#include <ss_types.h>		/* for skills		  */
#include <macros.h>		/* for QCTNAME, etc	  */
#include <const.h>		/* for G_MALE		  */
#include <money.h>		/* for MONEY_MAKE  	  */
#include "/d/Gondor/defs.h"
#include "/d/Gondor/bits.h"
#include "../defs.h"

#define	HOME	(SIRITH_FARMS_DIR+"farm1/shed")

static int	DontMove;	/* set if about to process gift */

/* prototypes */
public void	create_sirith_farmer();
public void	catch_question(string question);
public int	not_here_func();
public string	name_answer();
public string   give_job();
public string	whisper_poison();
public string	cap_place();
public void	enter_inv(object obj, object from);
public void	do_give_back(object obj, object from);
public void	accept_coin(object obj, object from, int plural);
public void	accept_drink(object obj, object from);
public void	accept_pigskin(object obj, object from);
public mixed	oke_to_move(string exit);
public void	do_defend(object livestock, object attacker);
public varargs	void arm_me();
public void	react_intro(object tp);
public int	query_knight_prestige();


/*
 * Function name:	create_sirith_farmer
 * Description	:	set up sandros
 */
public void
create_sirith_farmer()
{
    set_name( ({ "sandros", "man" }) );
    set_living_name("sandros");
    set_race_name("human");
    set_gender(G_MALE);
    add_adj( ({ "dour", "jug-eared" }) );
		/* str, dex, con, int, wis, dis */
    set_stats(({55+random(10), 45+random(10), 45+random(10),
	45+random(10), 45+random(10), 45+random(30)}));
    set_alignment(-200);	/* untrustworthy */
    set_skill(SS_DEFENCE, 20 + random(20));
    set_skill(SS_AWARENESS, 20 + random(20));
    set_skill(SS_WEP_KNIFE, 20 + random(20));
    /* farmers are pretty handy with pitchforks */
    set_skill(SS_WEP_POLEARM, 50 + random(20));
    set_random_move(200+random(60));
    set_monster_home(HOME);
    remove_prop(NPC_M_NO_ACCEPT_GIVE);

    /* call npcsize to set CONT_I_HEIGHT, WEIGHT, VOLUME */
    GONDOR_MASTER->npcsize(TO, "tall", "skinny");

    set_chat_time(10);
    add_chat("It's nothing but work, work, work around here.");
    add_chat("Wish I owned that pig.");
    add_chat("The chickens have more feathers than brains.");
    add_chat("They act like the world will end if a man stops "+
	"to rest.");
    add_chat("The cows are almost as stupid as the chickens.");
    add_chat("On this farm, the animals are treated better than the help.");
    add_chat("It's not my fault; that pig's a devil!");

    set_act_time(10);
    add_act(VBFC_ME("open_it"));
    add_act("emote grumbles under his breath.");
    add_act("emote gives you a sour smile.");


    /* respond nicely to questions */
    set_dont_answer_unseen(1);
    set_default_answer(
    	({ "scowl . @@query_player_name@@", "shrug" }) );
    set_not_here_func("not_here_func");

    add_ask_item( ({ "what's your name", "what is your name", "name" }),
	VBFC_ME("name_answer") );

    add_ask_item( ({ "chicken", "chickens", "hen", "hens", "pets" }),
	({ "say If those were my chickens, I'd have a nice "+
		"feather pillow.",
	   "say At least the chickens lay eggs. That's more "+
		"than the pig does.",
	   "say Oh, they're Kellis' pets, they are." }) );
    add_ask_item( ({ "feathers", "pillow", }),
	"say If those were my chickens, I'd have a nice "+
		"feather pillow.");
    add_ask_item( "eggs",
	   "say At least the chickens lay eggs. That's more "+
		"than the pig does.");

    add_ask_item( ({ "sow", "escapes", "escape", "devil", "trouble",
	"sty", "pen", "pig" }),
	({ "say If I owned that pig, I'd soon wear a pigskin vest.",
	   "say They always blame me when the pig escapes her pen.",
	   "say It's impossible to keep the pig in the sty, "+
	"but somehow it's always my fault when she escapes." }) );
    add_ask_item( ({ "blame", "fault", }),
	({ "say They always blame me when the pig escapes her pen.",
	   "say It's impossible to keep the pig in the sty, "+
		"but somehow it's always my fault when she escapes." }) );

    add_ask_item( ({ "vest", "feature", "pig skin", "pigskin", "skin" }),
	({ "say That pig's only good feature is its skin.",
	   "say I could get a nice vest out of that pig's skin, "+
	        "if it were in good condition." }) );

    add_ask_item( ({ "good condition", "condition", "damage", "undamaged",
	"mar", "marred", "mark", "marks" }),
	({ "say A skin's no use if it's damaged.",
	   "say It's hard to use a skin that's marred." }) );

    add_ask_item( "help",
	({ ({ VBFC_ME("give_job"), "say You want to help me?", "ponder",
	   "say Huh. Just bring me a pig skin -- in good condition, mind!" }) }) );

    add_ask_item( ({ "coins", "chore", "quest", "task", "job" }),
	({ ({ VBFC_ME("give_job"), 
           "say You bring me a pig skin - undamaged, mind you - "+
	   "and I'll come up with some coins." }) }) );

    add_ask_item( ({ "skinning", "weapons", "direct", "catch", "tough",
		"force", "attacking", "attack", "kill" }),
	({ "say That pig's tough ... I wouldn't try a direct attack.",
	   "say With that pig, guile is better than force." }) );

    add_ask_item( ({ "indirect", "indirect attack", "approach", "food", "eat",
		"extra", "trick",
		"guile", "greedy", "guts", "greedy guts", "addition",
		"disagree", "disagreed" }),
	({ ({ "say The pig's a real greedy guts ... she might well eat "+
	        "something that disagreed with her.",
    	      "smile nastily" }),
	   ({ "say The pig eats so fast, she'd never notice a little "+
	        "addition to her food.",
    	      "smile nastily" }),
	   ({ "say A little extra in her food might do the trick ...",
    	      "smile nastily" }) }) );

    add_ask_item( ({ "toxic", "toxin", "poison" }),
	({ ({ "whisper @@query_player_name@@ Poison's always better if "+
		   "you want to use the skin.",
	      "@@whisper_poison@@" }),
           ({ "whisper @@query_player_name@@ Weapons damage the skin, but "+
		    "poison leaves no mark.",
	      "@@whisper_poison@@" }),
           ({ "whisper @@query_player_name@@ Poison doesn't mar the skin.",
	      "@@whisper_poison@@" }) }) );

    add_ask_item( ({ "hemlock", "madwort", "sumac" }),
	"whisper @@query_player_name@@ That's supposedly strong poison.");

    add_ask_item( ({ "herb", "herbalist", "herbs" }),
	({ "say I don't know much about herbs.",
	   "say I'm just a hired hand, not a herbalist." }) );

    add_ask_item( ({ "slave", "hired hand", "rest", "work" }),
	({ "say They'd never treat the livestock the way "+
		"they treat me.",
	   "say Raichim is always glaring at me the minute "+
		"I take a bit of rest.",
	   "say I'm a hired hand, not a slave." }) );

    add_ask_item( ({ "cow", "animals", "livestock", "cows" }),
	({ "say The cows are stupid, but they're not much trouble.",
	   "say At least the cows produce some milk. That's more "+
		"than you can say for the pig.",
	   "say Raichim says the milk tastes off. Huh, her frown "+
		"is enough to sour it." }) );
    add_ask_item( "milk",
	({ "say At least the cows produce some milk. That's more "+
		"than you can say for the pig.",
	   "say Raichim says the milk tastes off. Huh, her frown "+
		"is enough to sour it." }) );

    add_ask_item( ({ "neighbor", "neighbors", "druyan" }),
	({ ({ "grin",
	      "say Druyan's sheep are almost as stupid as "+
		"Kellis' chickens." }),
	   ({ "sigh",
	      "say Druyan's cider is good, but she's awfully "+
		"stingy with it." }),
	   ({ "say Druyan's bees have her temper, all right.",
	      "say I stay well away from them." }) }) );
    add_ask_item( ({ "stingy", "apples", "cider", }),
	   ({ "sigh",
	      "say Druyan's cider is good, but she's awfully "+
		"stingy with it." }) );
    add_ask_item( "sheep",
	({ "grin",
	   "say Druyan's sheep are almost as stupid as "+
		"Kellis' chickens." }) );
    add_ask_item( "bees",
	({ "say Druyan's bees have her temper, all right.",
	      "say I stay well away from them." }) );

    add_ask_item( ({ "piddling", "they", "farmers", "owners",
	"nagging", "kellis", "raichim" }),
	({ "say Raichim and Kellis are always nagging me.",
	   "say Raichim thinks she knows everything, and "+
		"Kellis is nearly as bad.",
	   "say Raichim and Kellis, the big land owners. Huh, "+
		"it's just a piddling farm." }) );
    add_ask_item( ({ "land", "farm", }),
	   "say Raichim and Kellis, the big land owners. Huh, "+
		"it's just a piddling farm." );

    add_ask_item( ({ "sirith", "gondor", "lebennin", "minas tirith",
		"mordor", "pelargir", "visit", "travel" }),
    	({ "laugh bitterly",
           "say @@cap_place@@? I'm lucky if I'm allowed to visit "+
		"Druyan!" }) );

} /* create_sirith_farmer */


/***** action and ask routines below here *****/


/*
 * Function name:	catch_question
 * Description	:	intercept /std/act/asking.c's catch_question() to:
 *			1) strip leading "for", "about" and trailing "?"
 *			2) do extra parsing if asking for hints
 *			3) remember the original question
 * Arguments:		string question -- whatever the player asked
 */
public void
catch_question(string question)
{
    string	*tmp_arr,			/* preps/verbs of interest */
		*pig_arr,			/* names of pig */
		stuff1, stuff2, stuff3;		/* tmp strings */

    if (objectp(query_attack()))
    {
	return;	/* no answers if fighting */
    }

    if (strlen(question))
    {
	/* strip off leading "for", "about" and trailing " ?" */
	tmp_arr = ({ "for", "about" });
	if (parse_command(question, ({}), "%p %s", tmp_arr, stuff1))
	{
	    question = stuff1;
	}
	if (sscanf(question, "%s ?", stuff1) ||
	    sscanf(question, "%s?", stuff1))
	{
	    question = stuff1;
	}

	/* match on:
	 * 	[ how do i, can i, should i, does one, ...]
	 *	    skin / poison / attacking / attack / catch / kill
	 *   	    [ a, the, your, that mangy ... ]
	 *	    pig / sow
	 *	[ and bring it home or whatever ]
	 * and set question to the verb.
	 */
	tmp_arr = ({ "skinning", "skin", "poison", "attacking",
		"attack", "catch", "kill" });
	pig_arr = ({ "pig", "sow" });

	if (parse_command(LOW(question), ({}), "%s %p %s %p %s",
	    stuff1, tmp_arr, stuff2, pig_arr, stuff3))
	{
	    if ((question = tmp_arr[0]) == "skin")
	    {
		question = "skinning";
	    }
	}
    }
    ::catch_question(question);
} /* catch_question */


/*
 * Function name:	not_here_func
 * Description	:	called when player asks question & leaves
 * Returns	:	0 -> don't answer the question
 */
public int
not_here_func()
{
     command("sigh");
     command("say I wish fools wouldn't waste my time.");
     return 0;
} /* not_here_func */



/* 
 * Function name:	name_answer
 * Description	:	respond to questions about name
 *
 */
public string
name_answer()
{
    object	tp = TP;
    string	tp_name;

    /* probably unnecessary, since we set not_here_func, but ... */
    if (!objectp(tp))
    {
	return "";
    }

    tp_name = tp->query_real_name();
    if (tp->query_met(TO))
    {
	command("sigh");
	command("say You've got a short memory, "+
	    capitalize(tp_name)+".");
	command("introduce me to "+tp_name);
    }
    else
    {
	command("scowl . "+tp_name);
	command("say Why don't you introduce yourself, "+
	    tp->query_nonmet_name()+"?");
    }
    return "";
} /* name_answer */


/* Function name:       give_job
 * Description  :       Log the giving of the task
 * Returns      :       string "" -- all msgs done here
 */
public string
give_job()
{
    command("hmm");
    START_QUEST(TP, "SIRITH PIG (KILLED)");
    return "";
}

/*
 * Function name:	whisper_poision
 * Description	:	VBFC to tell player about a random poison
 * Returns	:	string "" -- all msgs done here
 */
public string
whisper_poison()
{
    command("ponder");
    command("whisper "+TP->query_real_name()+" I hear that "+
	({ "hemlock", "madwort", "sumac" })[random(3)]+
	" is quite toxic.");
    command("wink sig "+TP->query_real_name());
    return "";
} /* whisper_poison */

/*
 * Function name:	cap_place
 * Description	:	VBFC to capitalize place names for ansers
 * Returns	:	string -- the capitalized name
 */
public string
cap_place()
{
    string question = query_question();
    if (question != "minas tirith")
    {
	return CAP(question);
    }
    return "Minas Tirith";
} /* cap_place */


/*
 * Function name:	enter_inv
 * Description	:	called when something enter's sandros' inv
 * Arguments	:	object obj -- the item
 *		:	object from -- its source
 */
public void
enter_inv(object obj, object from)
{
    /* if the obj is a coin and if sandros already has coins of its type,
     * obj will be null on return from ::enter_inv(), so use wascoin and
     * pluralcoins to remember about it.
     * don't have to worry about drinks (sandros gulps them) or fake
     * coins (sandros drops them) so will not have either in inventory.
     */
    int wascoin,
	pluralcoins;

    DontMove = 1;
    if (wascoin = obj->id("coin"))
    {
	pluralcoins = (obj->num_heap() > 1);
    }

    ::enter_inv(obj, from);

    if (wascoin)
    {
	set_alarm(3.0, 0.0, &accept_coin(obj, from, pluralcoins));
    }
    else if (!objectp(from))
    {
	DontMove = 0;
	return;
    }
    else if (obj->id("pig skin"))
    {
	set_alarm(3.0, 0.0, &accept_pigskin(obj, from));
    }
    else if (obj->query_alco_amount())
    {
	set_alarm(3.0, 0.0, &accept_drink(obj, from));
    }
    else
    {
	set_alarm(3.0, 0.0, &do_give_back(obj, from));
    }
} /* enter_inv */


/*
 * Function name:	do_give_back
 * Description	:	return obj to giver
 * Arguments	:	object obj -- the item
 *		:	object from -- its source
 */
public void
do_give_back(object obj, object from)
{
    if (!objectp(obj))
    {
	DontMove = 0;
        return;
    }
    if (!objectp(from))
    {
	obj->remove_object();
	DontMove = 0;
        return;
    }
    command("say I've no use for this.");
    command("give " + OB_NAME(obj) + " to " +
        from->query_real_name());

    if (objectp(obj) &&
	present(obj, TO))
    {
        command("drop " + OB_NAME(obj));
    }
    DontMove = 0;
} /* do_give_back */


/*
 * Function name:	accept_coin
 * Description	:	make grateful noises
 * Arguments	:	object obj -- the coin object
 *			object from -- the giver
 *			int plural -- true if given > 1 coin
 *
 * since coins are heaps, obj may be null.
 */
public void
accept_coin(object obj, object from, int plural)
{
    if (!objectp(from))
    {
	DontMove = 0;
        return;
    }
    if (!objectp(obj) ||
	MASTER_OB(obj) == "/std/coins")
    {
	if (ENV(from) == ENV())
	{
	    command("say Thanks, "+
		(from->query_met(TO) ? from->query_name() :
		    from->query_nonmet_name() )+".");
	}
	command("emote pockets the "+
	    (plural ? "coins." : "coin."));
    }
    else /* bogus coins */
    {
	command("say I can't spend "+
	    (plural ? "these." : "this."));
	command("give " + OB_NAME(obj) + " to " +
            from->query_real_name());

	if (objectp(obj) && present(obj, TO))
	{
            command("drop " + OB_NAME(obj));
	}
    }
    DontMove = 0;
} /* accept_coin */


/*
 * Function name:	accept_drink
 * Description	:	make grateful noises
 * Arguments	:	object obj -- the drink object
 *			object from -- the giver
 */
public void
accept_drink(object obj, object from)
{
    if (!objectp(obj))
    {
	DontMove = 0;
        return;
    }
    if (!objectp(from))
    {
	obj->remove_object();
	DontMove = 0;
        return;
    }
    if (ENV(from) == ENV())
    {
	command("say Thanks, "+
	    (from->query_met(TO) ? from->query_name() :
		from->query_nonmet_name() )+".");
    }
    command("emote downs the "+obj->query_short()+".");
    command("emote wipes his mouth with the back of his hand.");
    obj->remove_object();
    DontMove = 0;
} /* accept_drink */


/*
 * Function name:	accept_pigskin
 * Description	:	handle gifts of pigskin -- this is where
 *			quest xp is awarded
 * Arguments	:	object obj -- the skin object
 *			object from -- the giver
 */
public void
accept_pigskin(object obj, object from)
{
    string	killer,
		pname,
		realname;


    if (!objectp(obj))
    {
	DontMove = 0;
        return;
    }
	
    if (!objectp(from) ||
	ENV(from) != ENV())
    {
	obj->remove_object();
	DontMove = 0;
	return;
    }

    command("emote inspects the pig skin.");
    realname = from->query_real_name();

    if (from->query_met(TO)) 
    {
	pname = from->query_cap_name();
    }
    else
    {
	pname = from->query_nonmet_name();
    }

    if (!strlen(killer = obj->query_prop(SIRITH_S_WAS_POIS)))
    {
	DEBUG_LOG(realname+" gave bad pig skin.\n");
	command("sniff disdainfully");
	command("say I can't use this skin, "+pname+" -- it's in "+
		"terrible condition.");
	command("give "+OB_NAME(obj)+" to "+realname);

	if (objectp(obj) && present(obj, TO))
	{
            command("drop "+OB_NAME(obj));
	}
	DontMove = 0;
	return;
    }
    if (killer != realname)
    {
	DEBUG_LOG(realname+" gave pig skin belonging to "+killer+".\n");
	command("sneer "+realname);
	command("say Nice skin, "+pname+", but I hear you didn't "+
		"really do the work.");
	command("say So there's no reason I should pay you, is there?");
	command("smile grimly "+realname);
	/* don't drop it */
	obj->remove_object();
	DontMove = 0;
	return;
    }
    obj->remove_object();
    command("nod . "+realname);
    command("say Very nice, "+pname+". I can certainly put this to use.");
    command("grin");
    command("say I'll just have to keep it out of Raichim's sight.");
    command("wink "+realname);
    MONEY_MAKE_GC(SIRITH_PIG_GOLD)->move(TO);
    command("say Here is a little something for your trouble.");
    command("give "+SIRITH_PIG_GOLD+" gold coins to "+realname);
    if (!from->test_bit("Gondor", SIRITH_PIG_GROUP, SIRITH_PIG_BIT))
    {
	from->set_bit(SIRITH_PIG_GROUP, SIRITH_PIG_BIT);
        from->add_exp_quest(SIRITH_PIG_EXP);
        from->adjust_alignment(-SIRITH_PIG_ALIGN);
        from->catch_tell("You feel more experienced!\n");
        LOG_QUEST(from, SIRITH_PIG_EXP, "SIRITH PIG (KILLED)");
	DEBUG_LOG(realname+" gave good pig skin to sandros!\n");
    }
    DontMove = 0;
} /* accept_pigskin */


/*
 * Function name:	oke_to_move
 * Description	:	don't move if just given something
 * Arguments	:	string exit -- the direction to try
 * Returns	:	0 -- don't move
 *			string exit -- move 
 *
 */
public mixed
oke_to_move(string exit)
{
    if (DontMove)
    {
	return 0;
    }
    return ::oke_to_move(exit);
} /* oke_to_move */


/*
 * Function name:	do_defend
 * Description	:	respond to attacks on our livestock
 * Arguments	:	object livestock -- the animal to defend
 *			object attacker -- its attacker
 * sandros won't protect livestock
 */
public void
do_defend(object livestock, object attacker)
{
    command( ({
	"sneer",
	"frown",
	"shrug",
	"grin",
	})[random(4)] );
    if (file_name(ENV()) != HOME)
    {
	move_living("away", HOME);
    }
    else
    {
	command("east");
    }
} /* do_defend */


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
	(SIRITH_FARMS_DIR + "obj/pfork") }) );
    ::arm_me();
    if (objectp(obj = present("tunic", TO)))
    {
	obj->configure("", "brown", "cotton", "well-worn", "");
    }
    if (objectp(obj = present("trousers", TO)))
    {
	obj->configure("much-patched", "brown", "cloth",
		"shabby", "");
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
    command("nod wearily "+tp->query_real_name());
    command("introduce me to "+tp->query_real_name());
} /* react_intro */


/* attacking a disloyal troublemaker is not so bad */
int query_knight_prestige() { return 0; }
