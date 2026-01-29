/*
 * /d/Gondor/river/anduin/npc/halabor.c
 *
 * Copyright (C) 1998 by Nancy L. Mintz (Gnadnar)
 *
 * TBD:
 *	forgive attackers only after they do some substantial favor
 *	sell boats
 *	limit # of boats sold per interval
 *	buy back boats?
 *	chats, actions, etc 
 *	more question (fishcamp, beornings, mirkwood, ...)
 *
 * XXX:
 *	does this name work? hala + bor == watch / guard + stone ?
 *	what is the correct skill cost factor?  i think i want this
 *		to be more expensive than default, but how much more?
 *	what is the max we want to teach here?
 */

#pragma strict_types

inherit "/d/Gondor/std/monster";
inherit "/lib/skill_raise";

#include <stdproperties.h>	/* for NPC_M_NO_ACCEPT_GIVE	*/
#include <ss_types.h>		/* for skills			*/
#include <macros.h>		/* for CAN_SEE, etc		*/
#include <const.h>		/* for G_FEMALE			*/
#include "/d/Gondor/defs.h"
#include "../anduin.h"
#include "../carrock2lorien/fishcamp.h"

#define	INTRO_DELAY	3.0
#define	SAVE_FILE	(RIVER_ANDUIN_DIR + "npc/halabor.o")
#define	BOAT_FILE	(RIVER_ANDUIN_DIR + "obj/boat")
#define	OARS_FILE	(OBJ_DIR + "oars")

#define	SKILL_DESC	"to maneuver boats"
#define	SKILL_NAME	"boat handling"

/* re cost factor (thanks, mercade!): the cost factor is a percentage of
 * the default cost of a skill.  so, a cost factor of 100 is default,
 * more expensive skills have a factor > 100.  for mudlib skills,
 * the default cost factor is 100 and so lots of code just passes a 0
 * to sk_add_train.  since this is NOT a mudlib skill, we can't do that.
 */
#define	SKILL_COSTF	130	/* XXX */
#define	SKILL_MAX	25	/* XXX */


/* prototypes */
public void	create_gondor_monster();
public void	init_living();
public void	add_introduced(string name);
public void	react_intro(object tp);
public int	query_knight_prestige();
public void	attacked_by(object ob);
public void	run_away();
public void	forgive(mixed offender);
public int	visible_and_known(object pl, int murmur);
public void	set_up_skills();
public int	sk_improve(string arg);
public void	sk_hook_raise_rank(int snum, int to_lev, int cost);
public void	sk_hook_write_header(int lessons);
public int	sk_hook_no_list_learn();
public int	sk_hook_no_list_improve();
public int	sk_hook_improved_max(string skill);
public void	sk_hook_skillisting();
public void	catch_question(string question);
public int	not_here_func();
public string	teach_answer();
public mixed	do_buy(string arg);
public varargs string	sk_fix_cost(int snum, int steps);


string		*Enemies = ({ });
static string	OrigQuestion;

/*
 * Function name:	create_gondor_monster
 * Description	:	set up halabor
 */
nomask void
create_gondor_monster()
{
    FIX_EUID;
    set_name( ({ "halabor", "woman" }) );
    set_living_name("halabor");
    set_race_name("human");
    set_gender(G_FEMALE);
    add_adj( ({ "thin", "wizened" }) );

    /* str, dex, con, int, wis, dis */
    set_stats( ({ (40 + random(10)), (40 + random(10)), (40 + random(10)),
	(40 + random(10)), (40 + random(10)), (40 + random(30)) }) );
    set_alignment(200);
    set_whimpy(50);

    set_skill(SS_DEFENCE, (50 + random(20)));
    set_skill(SS_PARRY, (50 + random(20)));
    set_skill(SS_AWARENESS, (70 + random(20)));
    set_skill(SS_WEP_KNIFE, (50 + random(20)));
    set_skill(SS_WEP_AXE, (50 + random(20)));

    set_equipment( ({ (ARM_DIR + "fjacket"),
    	 (ARM_DIR + "ltrousers") }) );

    add_prop(NPC_M_NO_ACCEPT_GIVE, " does not accepts gifts from you.\n");

    /* call npcsize to set CONT_I_HEIGHT, WEIGHT, VOLUME */
    GONDOR_MASTER->npcsize(TO, "tall", "skinny");

    create_skill_raise();
    set_up_skills();

    restore_object(SAVE_FILE);

    set_not_here_func("not_here_func");
    set_dont_answer_unseen(1);
    /*set_ask_log("halabor.log");*/

    set_default_answer(
	({ ({ "peer @@query_player@@",
	      "say I'm afraid I don't know.",
	   }),
	   ({ "shrug",
	      "say Sorry, I don't know.",
	   }),
	})

    );
    add_ask_item( ({ "maneuver boats", "handle boats", "boat handling",
	"teach", "teach me", "skill", "skills", "lesson", "lessons",
	"train", "training", "learn", "improve"}),
	VBFC_ME("teach_answer"));

    add_ask_item(
	({ "boat", "boats", }),
	({ "say We use our boats hard, but they stand up to it pretty well.",
	   "say Our boats are well built, but nothing like the " +
		   "Elven boats.",
	   "say It's a pleasure to watch a boat on the water.",
	})
    );
    add_ask_item(
	({ "buy boat", "buy a boat", "sell me boat", "sell me a boat",
	   "to sell me boat", "to sell me a boat" }),
	VBFC_ME("do_buy"));


    add_ask_item( 
	({ "anduin", "river", "river anduin", "anduin river",
	   "great river", "water", 
	}),
	({ ({ "say It's a long journey down the Anduin.",
	      "say But in spite of the hazards, it's the best route.",
	   }),
	   ({ "say Negotiating the Anduin requires some skill.",
	      "say And beware of Sarn Gebir -- skill will not save " +
		  "you there!",
	   }),
	})
    );

    add_ask_item( 
	({ "hazard", "hazards", "sarn gebir", "rapids",
	   "rapids of sarn gebir", 
	}),
	({ ({ "say The rapids of Sarn Gebir are deadly!",
	      "shiver",
	      "say No one has ever come through them alive.",
	   }),
	   ({ "say Sarn Gebir would smash our boats to splinters.",
	      "say I doubt anyone could survive those rapids.",
	   }),
	   ({ "say I have never heard of anyone surviving the " +
	    	  "rapids of Sarn Gebir.",
	      "say Even the boats of the Elves would fail you " +
	    	  "there.",
	   }),
	})
    );
    add_ask_item(
	({ "travel", "traveling", "journey", "route", }),
	({ "say The Great River is your best route for " +
	    	"traveling south from here.",
	   "say The Anduin flows all the way to Pelargir.",
	   "say The Anduin is the best route through the " +
	    	"Brown Lands and the Emyn Muil.",
	})
    );
    add_ask_item(
	({ "pelargir", "mouth of the Anduin",
	   "mount of Anduin",
	}),
	({ ({ "say Pelgarir lies at the mouth of the Anduin, or " +
	           "so I hear.",
	      "say I've never been there myself.",
	   }),
	})
    );
    add_ask_item(
	({ "the brown lands", "brown lands" }),
	({ ({ "say The Brown Lands are well-named.",
	      "say Bleak, cheerless -- nothing lives there.",
	   }),
	})
    );
    /* XXX ask gorboth what he wants said */
    add_ask_item(
	({ "the emyn muil", "emyn muil", }),
	({ "say The Emyn Muil is difficult terrain.",
	   "say Traveling afoot in the Emyn Muil is slow and painful.",
	})
    );
    add_ask_item(
	({ "lorien", "lothlorien" }),
	({ ({ "say The woods of Lothlorien are fair, but few " +
	           "who travel there emerge unchanged.",
	   }),
	})
    );
    add_ask_item(
	({ "elven boats", "boats of the elves", "elves", }),
	({ "say The boats of the Elves are the finest I know.",
	   ({ "sigh enviously",
	      "say I wish I had an Elven boat.",
	   }),
	})
    );
} /* create_gondor_monster */


/*
 * Function name:	init_living
 * Description	:	add the train/buy verbs
 */
public void
init_living()
{
    ::init_living();
    init_skill_raise();
    add_action(do_buy, "buy");	/* XXX necessary when use real shop code? */
} /* init_living */


/*
 * Function name:	add_introduced
 * Description	:	schedule a response to introductions
 * Arguments	:	string name -- name of the introduced living
 *
 */
public void
add_introduced(string name)
{
    if (!objectp(query_attack()) &&
	interactive(TP) &&
    	CAN_SEE_IN_ROOM(TO) &&
	CAN_SEE(TO, TP))
    {
	set_alarm(INTRO_DELAY, 0.0, &react_intro(TP));
    }
}

/*
 * Function name:	react_intro
 * Description	:	respond to introductions
 * Arguments	:	object tp -- the player
 */
public void
react_intro(object tp)
{
    string	obname,
		name;
    if (!objectp(tp) ||
	ENV(tp) != ENV(TO))
    {
	return;
    }
    name = tp->query_name();
    if (member_array(name, Enemies) < 0)
    {
	obname = OB_NAME(tp);
        command("bow " + obname);
	/* wizards always know the npc name, so query_met() is true.
	 * however, assume that if a wiz intro'd, we should respond in kind.
	 */
        if (!tp->query_met(name) ||
            tp->query_wiz_level())
        {
    	    command("introduce me to " + obname);
        }
        else
        {
    	    command("Good to see you again.");
        }
    }
    else
    {
        command("say I remember you quite well, " + name +
    	    " -- although you might wish otherwise.");
        command("smile grimly");
    }
} /* add_introduced */


/* attacking peaceful fishers ... tsk tsk */
public int	query_knight_prestige()	{ return -8; }


/*
 * Function name:	attacked_by
 * Description	:	Called when we are attacked.
 * Arguments	:	object ob -- the attacker
 */
public void
attacked_by(object ob)
{
    string	name = ob->query_name();

    if (member_array(name, Enemies) < 0)
    {
	Enemies += ({ name });
	save_object(SAVE_FILE);
    }
    if (sizeof(query_weapon(-1)))
    {
	return;
    }
    clone_object(WEP_DIR + "handaxe")->move(TO, 1);
    /* XXX might want to have her wear a belt */
    command("emote snatches an axe from her belt.");
    command("wield axe");
    return;
} /* attacked_by */


/*
 * Function name:	run_away
 * Description	:	make a quick getaway
 */
public void
run_away()
{
    object	env = ENV();
    command("swim in river");
    if (ENV() != env)
    {
	/* ok, we weren't blocked -- vanish into the river */
	command("emote dives into the river.");
	all_inventory(TO)->remove_object();
	remove_object();
    }
} /* run_away */


/*
 * Function name:	forgive
 * Description	:	remove someone from the enemies list
 * Arguments	:	mixed offender: object -- the person
 *				     or string -- their name
 */
public void
forgive(mixed offender)
{
    string	name;
    if (objectp(offender))
    {
	name = offender->query_name();
    }
    else
    {
	name = CAP(offender);
    }
    Enemies -= ({ name });
    save_object(SAVE_FILE);
}



/*
 * Function name:	visible_and_known
 * Description	:	refuse to deal with people in dark room,
 *			invisible people, or people we don't know
 * Arguments	:	object pl -- the person in question
 *			int murmur -- if true, have person murmur
 * Returns	:	1 if ok, 0 if not.
 */
public int
visible_and_known(object pl, int murmur)
{
    if (!CAN_SEE_IN_ROOM(TO))
    {
	command("say I'm sorry, but I can't see a thing in here.");
	command("say Do you have a torch, perhaps?");
	return 0;
    }
    if (!CAN_SEE(TO, pl))
    {
	command("peer cautiously");
	command("say Who is that? I can't see you!");
	return 0;
    }
    if (murmur)
    {
	tell_room(ENV(TO), 
	    QCTNAME(pl) + " murmurs something to " + QTNAME(TO) + ".\n", pl);
    }
    if (!pl->query_met("halabor"))
    {
	command("peer cautiously " + pl->query_name());
	command("say Have we met? I'm afraid I don't remember you.");
	return 0;
    }
    return 1;
} /* visible_and_known */



/************** begin skills code **************/
/*
 * Function name:	set_up_skills
 * Description	:	init the skills taught by halabor
 */
public void
set_up_skills()
{
    sk_add_train(SS_BOAT_HANDL, ({ SKILL_DESC, SKILL_DESC, }),
	SKILL_NAME, SKILL_COSTF, SKILL_MAX);
} /* set_up_skills */


/*
 * Function name:	sk_improve
 * Description	:	handle attempts to improve skills
 * Arguments	:	string arg -- whatever the player typed
 * Returns	:	1 if we know recognize the arg, 0 if not
 */
public int
sk_improve(string arg)
{
    string	name;
    int		steps;

    if (!visible_and_known(TP, 1))
    {
	return 1;
    }
    name = TP->query_name();
    if (member_array(name, Enemies) >= 0)
    {
	command("scowl " + OB_NAME(TP));
	command("say Do you think I've forgotten you, " + name + "?");
	command("say I don't deal with people who attack me.");
	return 1;
    }
    if (!strlen(arg))
    {
	return ::sk_improve(arg);
    }
    arg = LOW(arg);
    name = name;
    if (arg == SKILL_NAME)
    {
	steps = 1;
    }
    else if (!sscanf(arg, SKILL_NAME + " %d", steps))
    {
	return ::sk_improve(arg);
    }
    if (steps > 1)
    {
	command("sigh patiently");
	command("say Don't be in such a rush, " + name + ".");
	command("say It took me years to learn what I know.");
	return 1;
    }
    return ::sk_improve(arg);
} /* sk_improve */


/*
 * Function name:	sk_hook_raise_rank
 * Description	:	player trained successfully -- write/say msgs
 * Arguments	:	int snum -- skill trained
 *			int to_lev -- level reached
 *			int cost -- how much paid
 */
public void
sk_hook_raise_rank(int snum, int to_lev, int cost)
{
    string	rank,
		long_str;

    rank = sk_rank(to_lev);
    command("nod approvingly " + TP->query_name());
    write(process_string(QCTNAME(TO)) + " teaches you " +
	sk_tdesc[snum][0] + " with the skill of " +
	LANG_ADDART(rank) + ".\n");
    LSAY(process_string(QCTNAME(TO)) + " teaches ",
	" " + sk_tdesc[snum][0] + " with the skill of " +
	LANG_ADDART(rank) + ".");

} /* sk_hook_raise_rank */


/*
 * Function name:	sk_hook_write_header
 * Description	:	Write the header to the improve or learn list
 * Arguments	:	int lessons - How many steps we are talking about
 */
public void
sk_hook_write_header(int lessons)
{
    tell_room(ENV(TO),
	QCTNAME(TO) + " recites a list of skills for "
          + QTNAME(TP) + ".\n", TP);
} /* sk_hook_write_header */


/*
 * Function name:	sk_hook_no_list_learn
 * Description	:	write the "No more unknown skills" msg
 * Returns	:	1 (always)
 */
public int
sk_hook_no_list_learn()
{
    command("smile " + TP->query_name());
    command("say I cannot teach you any new skill!");
    command("say You might try to improve skills that you have,");
    command("say or you will have to seek other teachers elsewhere.");
    return 1;
} /* sk_hook_no_list_learn */


/*
 * Function name:	sk_hook_no_list_improve
 * Description	:	write the "no more skills to teach" msg
 * Returns	:	1 (always)
 */
public int
sk_hook_no_list_improve()
{
    command("smile " + TP->query_name());
    command("say There are no more skills that I can help you improve.");
    command("say Perhaps you would feel like learning a new skill?");
    command("say Failing that, you will have to seek other teachers elsewhere.");
    return 1;
} /* sk_hook_no_list_improve */


/*
 * Function name:	sk_hook_improved_max
 * Description	:	write the "cannot raise further" msg
 * Arguments	:	string skill -- the skill attempted
 * Returns	:	1 (always)
 */
public int
sk_hook_improved_max(string skill)
{
    command("smile ruefully " + TP->query_name());
    command("say I cannot teach you any more " + skill + ".");
    command("say You will have to seek knowledge elsewhere.");
    return 1;
} /* sk_hook_improved_max */

/*
 * Function name:	sk_hook_skillisting
 * Description	:	list all the skills
 */
public void
sk_hook_skillisting()
{
    tell_room(ENV(TO),
	QCTNAME(TO) + " recites a list of skills for " +
	QTNAME(TP) + ".\n", TP);
} /* sk_hook_skillisting */


/************** end skills code **************/


/************** begin questions code **************/

/*
 * Function name:	catch_question
 * Description	:	intercept /std/act/asking.c's catch_question() in order
 *			to 1) ignore enemies
 *			2) strip leading "about " and trailing "?"
 *			3) do extra parsing if asking for hints
 *			4) remember the question
 * Arguments:		string question -- whatever the player asked
 */
public void
catch_question(string question)
{
    string tmpstr;

    if (!visible_and_known(TP, 0))
    {
	return;
    }
    if (objectp(query_attack()))
    {
	return;	/* no answers if fighting */
    }
    if (member_array(TP->query_name(), Enemies) >= 0)
    {
	/* ignore enemies */
	if (!random(5))
	{
	    command("scowl " + OB_NAME(TP));
	    command("emote turns away.");
	}
	return;
    }

    OrigQuestion = question;
    question = LOW(question);
    /* strip off leading "about " and trailing " ?" */
    if (sscanf(question, "about %s", tmpstr))
    {
	question = tmpstr;
    }
    if (sscanf(question, "%s ?", tmpstr) ||
	sscanf(question, "%s?", tmpstr))
    {
	question = tmpstr;
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
    command("shrug");
    command("say Too busy to wait for an answer, I guess.");
    return 0;
} /* not_here_func */


/*
 * Function name:	teach_answer
 * Description	:	responds to questions about teaching 
 * Returns	:	null string ... response is gen'd via command()
 *
 * add_ask( ({ "handle", "boat handling", "teach", "teach me", "skill", 
 *	"skills", "lesson", "lessons", "train", "training", "learn",
 *	"improve"}),
 */
public string
teach_answer()
{
    if (TP->query_skill(SS_BOAT_HANDL) < SKILL_MAX)
    {
	sk_list(-1);
    }
    else
    {
	command("smile ruefully "+TP->query_name());
	command("say There's nothing more for me to teach you.");
	command("say You will have to seek knowledge elsewhere.");
    }
    return "";
} /* teach_answer */


/*
 * Function name:	do_buy
 * Description	:	handle selling a boat
 * Arguments	:	string arg -- player's arg if verb is "buy"
 * Returns	:	mixed -- int 0/1 if verb is "buy"
 *				 string "" if verb is "ask"
 * XXX may have to change when use real shop code
 */
public mixed
do_buy(string arg)
{
    string	vb = QVB;
    object	*boats;

    if (vb == "buy")
    {
	if (arg != "boat" &&
	    arg != "a boat")
        {
	    /* XXX ick. better to say "what did you want to buy?",
	     * can we assume we're the only merchant here?
	     */
	    NF0("Buy what?\n");
	}
	if (member_array(TP->query_name(), Enemies) >= 0)
	{
	    /* ignore enemies */
	    if (!random(5))
	    {
		command("scowl " + OB_NAME(TP));
		command("emote turns away.");
	    }
	    return 1;
	}
    }

    boats = filter(filter(all_inventory(ENV(TO)),
			  &->id("boat")),
		   not @ &->id(BROKEN_BOAT_NAME));
    if (sizeof(boats))
    {
	/* perfectly good boat in room */
	command("point " + OB_NAME(boats[0]));
	command("say That boat seems fine.");
    }
    else if (!TP->query_wiz_level())
    {
	command("say I'm sorry, but we don't have any boats to spare just now.");
	command("say Perhaps in a few days ...");
    }
    else
    {
	command("hmm");
	command("emote disappears behind the shelter for a moment.");
	command("emote returns, dragging a boat.");
	clone_object(BOAT_FILE)->move(ENV(TP));
	command("bow " + OB_NAME(TP));
	command("say Consider it a gift, O Wizard.");
	/* XXX what about oars? */
    }

    if (vb == "buy")
    {
	return 1;
    }
    return "";
} /* do_buy */


/*
 * Function name:	sk_fix_cost
 * Description	:	Fix each line in the improve/learn list
 * Arguments	:	int snum  - The skill to check
 *			int steps - How many steps player wants to raise
 * Returns	:	A formatted string to be said
 *
 * Mask parent to make the response look more natural. Probably would
 * be faster to swipe the code from parent and only format it once,
 * instead of re-formatting the parent's already formatted string.
 * However, I don't want to risk swiped code getting out of sync with 
 * mudlib, so lets just eat the cost of re-formatting.
 *
 * We don't have to worry about nonmet descs here, since we won't 
 * deal with people until they intro.
 */
public varargs string
sk_fix_cost(int snum, int steps)
{
    string	tmpstr,
		*results,
		*subs,
		next,
		myname,
		max;
    int 	i,	/* offset of next level in array */
		j;	/* offset of max level in array */

    tmpstr = ::sk_fix_cost(snum, steps);

    results = filter(explode(tmpstr, " "), strlen);
    if (sizeof(results) < 4)
    {
	return tmpstr;
    }

    /* we could probably just hardcode Halabor, but ... */
    myname = query_name();

    /* cost field is either n + " copper" or "---".
     * determine offset of subsequent fields accordingly.
     */
    i = ((results[2] != "---") ? 4 : 3);

    subs =  sk_query_sub_levels();
    /* pull together text desc of next level */
    if (member_array(results[i], subs) >= 0)
    {
	next = results[i] + " " + results[i+1];
	j = i + 2;
    }
    else
    {
	next = results[i];
	j = i + 1;
    }

    /* pull together text desc of max level */
    if (member_array(results[j], subs) >= 0)
    {
	max = results[j] + " " + results[j+1];
    }
    else
    {
	max = results[j];
    }

    /* now format it nicely */
    if (i == 4)
    {
	tmpstr = myname + " says: I can teach you how " + SKILL_DESC +
	    " with the skill of " + LANG_ADDART(next) +
	    " for " + results[2] +
	    " copper " + (results[2] != "1" ? "coins. " : "coin. ");
	if (next != max)
	{
	   tmpstr += "The most I can do is teach you " + SKILL_DESC +
	   " with the skill of " + LANG_ADDART(max) + ".\n";
	}
	else
	{
	    tmpstr += "I cannot teach you more than this.\n";
	}
    }
    else
    {
	tmpstr = myname + " says: I'm afraid I cannot teach you how " +
	    SKILL_DESC + " with the skill of " + LANG_ADDART(next) + ". " +
	    "The most I can do is teach you " + SKILL_DESC +
	    " with the skill of "+ LANG_ADDART(max) + ".\n";
    }
    if (steps > 1)
    {
	tmpstr += myname + " says: Know, too, that you cannot rush the " +
	    "process. It takes time to learn this properly.\n";
    }
    tmpstr += myname + " smiles.\n" + myname +
	" says: All you need do is '" + QVB + " " + SKILL_NAME + "'.\n";
    return tmpstr;
} /* sk_fix_cost */
