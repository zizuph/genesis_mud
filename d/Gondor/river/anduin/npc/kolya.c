 /*
 * /d/Gondor/river/anduin/npc/kolya.c
 *
 * Copyright (C) 1998 by Nancy L. Mintz (Gnadnar)
 *
 * TBD:
 *	respond to more questions
 *	have chat-like actions to build canoes
 *	forgive attackers only after they do some substantial favor
 *	sell canoes
 *	limit # of canoes sold per interval
 *	buy back canoes?
 *
 * XXX:
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

#define	SAVE_FILE	(RIVER_ANDUIN_DIR+"npc/kolya.o")
#define	CANOE_FILE	(RIVER_ANDUIN_DIR+"obj/canoe")
#define	OARS_FILE	(OBJ_DIR+"oars")

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
public string	default_answer();
public int	not_here_func();
public string	canoe_answer();
public string	build_answer();
public string	teach_answer();
public string	anduin_answer();
public string	sarn_gebir_answer();
public string	journey_answer();
public string	places_answer();
public string	elves_answer();


string		*Enemies = ({ });
static string	OrigQuestion;

/*
 * Function name:	create_gondor_monster
 * Description	:	set up kolya
 */
nomask void
create_gondor_monster()
{
    FIX_EUID;
    set_name( ({ "kolya", "woman" }) );
    set_living_name("kolya");
    set_race_name("human");
    set_gender(G_FEMALE);
    add_adj( ({ "calm", "white-haired" }) );

		/* str, dex, con, int, wis, dis */
    set_stats(({60+random(10), 60+random(10), 60+random(10),
	60+random(10), 60+random(10), 60+random(30)}));
    set_alignment(200);
    set_whimpy(50);

    set_skill(SS_DEFENCE, 50 + random(20));
    set_skill(SS_PARRY, 50 + random(20));
    set_skill(SS_AWARENESS, 70 + random(20));
    set_skill(SS_WEP_KNIFE, 70 + random(20));
    set_skill(SS_WEP_AXE, 70 + random(20));

    set_equipment(ARM_DIR+"studl");

    add_prop(NPC_M_NO_ACCEPT_GIVE, " does not accepts gifts from you.\n");

    /* call npcsize to set CONT_I_HEIGHT, WEIGHT, VOLUME */
    GONDOR_MASTER->npcsize(TO, "tall", "normal");

    create_skill_raise();
    set_up_skills();

    restore_object(SAVE_FILE);

    set_chat_time(10);
    add_chat("A canoe on the water is a beautiful sight!");
    add_chat("Traveling by river can be easier than traveling afoot.");
    add_chat("A good canoe can take you far.");


    set_default_answer(VBFC_ME("default_answer"));
    set_not_here_func("not_here_func");
    set_dont_answer_unseen(1);
    add_ask( ({ "boat", "boats", "canoes", "canoe" }),
	VBFC_ME("canoe_answer") );
    add_ask( ({ "fortnight", "build", "build canoe", }),
	VBFC_ME("build_answer") );
    add_ask( ({ "handle", "boat handling", "teach", "teach me", "skill",
	"skills", "lesson", "lessons", "train", "training", "learn",
	"improve"}),
	VBFC_ME("teach_answer") );
    add_ask( ({ "anduin", "river", "river anduin", "anduin river",
	"great river", "water", }),
	VBFC_ME("anduin_answer") );
    add_ask( ({ "hazard", "hazards", "sarn gebir", "rapids",
	"rapids of sarn gebir", }),
	VBFC_ME("sarn_gebir_answer") );
    add_ask( ({ "travel", "traveling", "journey", "route", }),
	VBFC_ME("journey_answer") );
    add_ask( ({ "pelargir", "the brown lands", "the emyn muil", 
	"brown lands", "emyn muil", "lorien", "lothlorien", }),
	VBFC_ME("places_answer") );
    add_ask( ({ "elven boats", "boats of the elves", "elves", }),
	VBFC_ME("elves_answer") );

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
} /* init_living */


/*
 * Function name:	add_introduced
 * Description	:	respond to introductions
 * Arguments	:	string name -- name of the introduced living
 *
 */
public void
add_introduced(string name)
{
    object	introd;
    /* wizards always know the npc name, so query_met() is true.
     * however, assume that if a wiz intro'd, we should respond in kind.
     */
    if (objectp(introd = present(name, ENV())) &&
	interactive(introd) &&
    	CAN_SEE_IN_ROOM(TO) &&
	CAN_SEE(TO, introd))
    {
	name = CAP(name);
	if (member_array(name, Enemies) < 0)
	{
	    command("bow "+name);
	    if (!introd->query_met(query_name()) ||
	        introd->query_wiz_level())
	    {
		command("introduce me to "+name);
	    }
	    else
	    {
		command("Good to see you again.");
	    }
	}
	else
	{
	    command("say I remember you quite well, "+name+
		" -- although you might wish otherwise.");
	    command("smile grimly");
	}
    }
} /* add_introduced */


/* attacking peaceful crafters ... tsk tsk */
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
    clone_object(WEP_DIR+"handaxe")->move(TO, 1);
    command("emote snatches an axe from the tools on the wall.");
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
    command("out");
    if (ENV() != env)
    {
	/* ok, we weren't blocked -- vanish into the river */
	command("emote wades into the river.");
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
	    QCTNAME(pl)+" murmurs something to "+QTNAME(TO)+".\n", pl);
    }
    if (!pl->query_met("kolya"))
    {
	command("peer cautiously "+pl->query_name());
	command("say Have we met? I'm afraid I don't remember you.");
	return 0;
    }
    return 1;
} /* visible_and_known */



/************** begin skills code **************/
/*
 * Function name:	set_up_skills
 * Description	:	init the skills taught by kolya
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
    string	name,
		skill;
    int		steps;

    if (!visible_and_known(TP, 1))
    {
	return 1;
    }
    name = TP->query_name();
    if (member_array(name, Enemies) >= 0)
    {
	command("scowl "+name);
	command("say Do you think I've forgotten you, "+name+"?");
	command("say I don't deal with people who attack me.");
	return 1;
    }
    if (!strlen(arg))
    {
	return ::sk_improve(arg);
    }
    arg = LOW(arg);
    name = name;
    if (sscanf(arg, "%s %d", skill, steps) != 2)
    {
	skill = arg;
	steps = 1;
    }
    if (skill != SKILL_NAME)
    {
	return ::sk_improve(arg);
    }
    if (steps > 1)
    {
	command("sigh patiently");
	command("say Don't be in such a rush, "+name+".");
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
    command("nod approvingly "+TP->query_name());
    write(process_string(QCTNAME(TO))+" teaches you " +
	sk_tdesc[snum][0]+".\n");
    write("You achieve the rank of "+rank+".\n");
    LSAY(process_string(QCTNAME(TO))+" teaches ",
	" "+sk_tdesc[snum][1]+" and helps "+OBJECTIVE(TP)+
	" to reach the rank of "+rank+".");
} /* sk_hook_raise_rank */


/*
 * Function name:	sk_hook_write_header
 * Description	:	Write the header to the improve or learn list
 * Arguments	:	int lessons - How many steps we are talking about
 */
public void
sk_hook_write_header(int lessons)
{
    if (!lessons)
    {
        lessons = 1;
    }
    command("smile "+TP->query_name());
    command("say These are the skills in which I can teach you");
    command("say one lesson or more.");
    write("  Skill:                Cost:      "+
          "Next level:           Max level:\n"+
          "--------------------------------------"+
          "--------------------------------------\n");
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
    command("smile "+TP->query_name());
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
    command("smile "+TP->query_name());
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
    command("smile ruefully "+TP->query_name());
    command("say I cannot teach you any more "+skill+".");
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
    command("smile "+TP->query_name());
    command("say These are the skills in which I can teach you");
    command("say one lesson or more.");
    write("  Skill:                Cost:      "+
          "Next level:           Max level:\n"+
          "--------------------------------------"+
          "--------------------------------------\n");
    tell_room(ENV(TO),
	QCTNAME(TO) + " recites a list of skills for "
	+ QTNAME(TP) + ".\n", TP);
} /* sk_hook_skillisting */


/************** end skills code **************/


/************** begin questions code **************/

/*
 * Function name:	catch_question
 * Description	:	intercept /std/act/asking.c's catch_question() in order
 *			to 1) strip leading "about " and trailing "?" and
 *			2) do extra parsing if asking for hints
 *			3) remember the question
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
    tmpstr = TP->query_name();
    if (member_array(tmpstr, Enemies) >= 0)
    {
	/* ignore enemies */
	if (!random(5))
	{
	    command("scowl "+tmpstr);
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
 * Function name:	default_answer
 * Description	:	give the default response to questions
 */
public string
default_answer()
{
    string	question = query_question();
    if (strlen(question))
    {
#ifdef XXX
	DEBUG_LOG(TP->query_name()+" questions: '"+
	    ((question != OrigQuestion) ? OrigQuestion+"' -> '" : "")+
		question+"'\n");
#endif /* XXX */
    }
    command("peer "+TP->query_name());
    command("say I don't understand your question.");
    return "";
} /* default_answer */


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
 * Function name:	canoe_answer
 * Description	:	responds to questions about canoes
 * Returns	:	null string ... response is gen'd via command()
 *
 * add_ask( ({ "boat", "boats", "canoes", "canoe" }),
 */
public string
canoe_answer()
{
    command("say I build and sell canoes.");
    command("say I can also teach you how to handle one -- it's "+
	"not as easy as you might think!");
    command("wink cheerfully "+TP->query_name());
    if (TP->query_wiz_level())
    {
	command("hmm");
	command("say Since you are a wizard ...");
	command("emote deftly unties the knot.");
	command("emote removes a canoe from the rack.");
	command("emote ties the rope securely again.");
	command("emote drops a canoe and some oars on the floor of the cave.");
	clone_object(CANOE_FILE)->move(ENV(TP));
	clone_object(OARS_FILE)->move(ENV(TP));
    }
    return "";
} /* canoe_answer */


/*
 * Function name:	build_answer
 * Description	:	responds to questions about building
 * Returns	:	null string ... response is gen'd via command()
 *
 * add_ask( ({ "fortnight", "build", "build canoe" }),
 */
public string
build_answer()
{
    command("say It takes a fortnight of solid work to build a canoe.");
    command("say And that's if everything goes well!");
    return "";
} /* build_answer */


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
 * Function name:	anduin_answer
 * Description	:	responds to questions about the anduin
 * Returns	:	null string ... response is gen'd via command()
 *
 * add_ask( ({ "anduin", "river", "river anduin", "anduin river",
 *	"great river", "water", }),
 */
public string
anduin_answer()
{
    switch (random(2))
    {
    case 0:
	command("say It's a long journey down the Anduin.");
	command("say But in spite of the hazards, it's the best route.");
	break;
    default:
	command("say Negotiating the Anduin requires some skill.");
	command("say And beware of Sarn Gebir -- skill will not save "+
	    "you there!");
	break;
    }
    return "";
} /* anduin_answer */


/*
 * Function name:	sarn_gebir_answer
 * Description	:	responds to questions about the anduin
 * Returns	:	null string ... response is gen'd via command()
 *
 * add_ask( ({ "hazard", "hazards", "sarn gebir", "rapids",
 *	"rapids of sarn gebir", }),
 */
public string
sarn_gebir_answer()
{
    switch (random(3))
    {
    case 0:
	command("say The rapids of Sarn Gebir are deadly!");
	command("shiver");
	command("say No one has ever come through them alive.");
	break;
    case 1:
	command("say Sarn Gebir would smash my canoes to splinters.");
	command("say I doubt anyone could survive those rapids.");
	break;
    default:
	command("say I have never heard of anyone surviving the "+
	    "rapids of Sarn Gebir.");
	command("say Even the boats of the Elves would fail you "+
	    "there.");
	break;
    }
    return "";
} /* sarn_gebir_answer */


/*
 * Function name:	journey_answer
 * Description	:	responds to questions about journeys
 * Returns	:	null string ... response is gen'd via command()
 *
 * add_ask( ({ "travel", "traveling", "journey", "route", }),
 */
public string
journey_answer()
{
    switch (random(3))
    {
    case 0:
	command("say The Great River is your best route for "+
	    "traveling south from here.");
	break;
    case 1:
	command("say The Anduin flows all the way to Pelargir.");
	break;
    default:
	command("say The Anduin is the best route through the "+
	    "Brown Lands and the Emyn Muil.");
	break;
    }
    return "";
} /* journey_answer */


/*
 * Function name:	places_answer
 * Description	:	responds to questions about specific places
 * Returns	:	null string ... response is gen'd via command()
 *
 * add_ask( ({ "pelargir", "the brown lands", "the emyn muil", 
 *	"brown lands", "emyn muil", "lorien", "lothlorien", }),
 */
public string
places_answer()
{
    switch (query_question())
    {
    case "pelargir":
	command("say Pelgarir lies at the mouth of the Anduin, or "+
	    "so I hear.");
	command("say I've never been there myself.");
	break;
    case "the brown lands":
    case "brown lands":
	command("say The Brown Lands are well-named.");
	command("say Bleak, cheerless -- nothing lives there.");
	break;
    case "the emyn muil":
    case "emyn muil":
	/* XXX ask gorboth what he wants said */
	command("say The Emyn Muil is difficult terrain.");
	command("say Traveling there afoot is slow going.");
	break;
    case "lorien":
    case "lothlorien":
	command("say The woods of Lothlorien are fair, but few "+
	    "who travel there emerge unchanged.");
	break;
    }
    return "";
} /* places_answer */


/*
 * Function name:	elves_answer
 * Description	:	responds to questions about elves
 * Returns	:	null string ... response is gen'd via command()
 *
 * add_ask( ({ "elven boats", "boats of the elves", "elves", })
 */
public string
elves_answer()
{
    switch (random(2))
    {
    case 0:
	command("say The boats of the Elves are the finest I know.");
	break;
    default:
	command("sigh enviously");
	command("say I wish I had the skill of the Elven boatwrights.");
	break;
    }
    return "";
} /* elves_answer */
