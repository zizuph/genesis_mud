/*
 * /d/Gondor/lebennin/sirith/farms/npc/druyan.c
 * farmer for the sheep farm (sirith/farms/farm2)
 *
 * Copyright (C) 1997 by Nancy L. Mintz (Gnadnar)
 *
 */

#pragma strict_types

inherit "/d/Gondor/lebennin/sirith/farms/npc/farmer";

#include <stdproperties.h>	/* for NPC_M_NO_ACCEPT_GIVE */
#include <ss_types.h>		/* for skills */
#include <macros.h>		/* for QCTNAME	*/
#include <const.h>		/* for G_FEMALE */
#include "/d/Gondor/defs.h"
#include "../defs.h"

#define	HOME	(SIRITH_FARMS_DIR+"farm2/house")

/* prototypes */
public void	create_sirith_farmer();
public void	reset_monster();
public void	catch_question(string question);
public int	not_here_func();
public string	cider_answer();

static int	Have_cider = 1;	/* has a mug of cider */
static string	OrigQuestion; /* need to know if asked "for cider" */


/*
 * Function name:	create_sirith_farmer
 * Description	:	set up the npc
 */
public void
create_sirith_farmer()
{
    set_name( ({ "druyan", "woman" }) );
    set_living_name("druyan");
    set_race_name("human");
    set_gender(G_FEMALE);
    add_adj( ({ "calm", "dark-eyed" }) );
		/* str, dex, con, int, wis, dis */
    set_stats(({45+random(10), 45+random(10), 45+random(10),
	45+random(10), 45+random(10), 45+random(30)}));
    set_alignment(200);
    set_skill(SS_DEFENCE, 20 + random(20));
    set_skill(SS_AWARENESS, 20 + random(20));
    set_skill(SS_WEP_KNIFE, 20 + random(20));
    /* farmers are pretty handy with pitchforks */
    set_skill(SS_WEP_POLEARM, 50 + random(20));
    set_random_move(200+random(60));
    set_monster_home(HOME);

    add_prop(NPC_M_NO_ACCEPT_GIVE, " does not accepts gifts from you.\n");
    /* call npcsize to set CONT_I_HEIGHT, WEIGHT, VOLUME */
    GONDOR_MASTER->npcsize(TO, "short", "plump");

    set_equipment( ({ (ARM_DIR + "tunic"),
	    (SIRITH_FARMS_DIR + "obj/boots"),
	    (ARM_DIR + "trousers"),
	    (SIRITH_FARMS_DIR + "obj/pfork") }) );

    /* XXX once add seasons to descs, chats should reflect season */
    set_chat_time(10);
    add_chat("Sheep may be stupid, but they're less trouble than pigs.");
    add_chat("The bees have been very irritable lately.");
    add_chat("The potatoes and carrots look very good this year.");
    add_chat("I think I'll have enough apples to make a big batch "+
	"of cider.");
    add_chat("Raichim and Kellis are good neighbors.");
    add_chat("Sandros is bone lazy; I doubt he's ever worked a full "+
	"day in his life.");
    add_chat("I hope that pig stays out of my garden!");

    set_act_time(10);
    add_act(VBFC_ME("open_it"));
    add_act("emote knocks some mud off her boots.");
    add_act("emote gives you a questioning look.");

    /* respond nicely to questions */
    set_default_answer(
    	({ "peer @@query_player_name@@", "shrug" }) );
    set_not_here_func("not_here_func");
    set_dont_answer_unseen(1);

    add_ask_item( ({ "pen", "lure" }),
	"say Raichim's sow is always escaping from the pen, "+
	    "and it's quite a job to lure her back once she's out." );
    add_ask_item( ({ "barley", "loss" }),
	({ "say That pig trampled the better part of my barley "+
	        "last month.",
	    "say Though to speak fairly, Raichim did "+
	        "reimburse me for the loss, but still, it's a nuisance." }) );

    add_ask_item( ({ "pig", "pigs", "sow", "sows", "trouble",
	"nuisance", "escape", }), 
	({ "say Raichim's sow is always escaping from the pen, "+
		"and it's quite a job to lure her back once she's out.",
	   ({ "say That pig trampled the better part of my barley "+
		  "last month.",
	      "say Though to speak fairly, Raichim did "+
		  "reimburse me for the loss, but still, it's a nuisance.", }),
	   ({ "say Has the pig escaped again?  You'd better speak to "+
		"Raichim or Kellis about it.",
	      "say Thank heavens, I'm not responsible for that sow." }), }) );

    add_ask_item( ({ "farm", "garden", "harvest",  "crops", }),
	({ "say The crops are doing very well this year; "+
		"it will be a good harvest.",
	   "say It's going to be a bumper harvest this year. "+
		"I'll be hard-pressed to find enough storage.",
	   "say Yes, the crops are coming along nicely." }) );
    
    add_ask_item( ({ "vegetables", "potatoes", "carrots", "apples" }),
	({ "say The @@query_question@@ are doing very well this year; "+
		"it will be a good harvest.",
	   "say It's going to be a bumper harvest this year. "+
		"I'll be hard-pressed to find enough storage.",
	   "say Yes, the @@query_question@@ are coming along nicely." }) );

    add_ask_item( ({ "bee", "bees", "honeybee", "honeybees" }),
	({ "say The bees never sting me, but they're not so friendly "+
		"with strangers.",
	   "say My bees make a fine honey. I get a good price for "+
		"it in Pelargir.",
	   ({ "say I'm not sure why, but the bees have been acting "+
		  "rather disturbed lately.",
	      "say I do hope no one's trying to rob my hives." }) }) );
    add_ask_item( ({ "sting", "strangers" }),
	"say The bees never sting me, but they're not so friendly "+
	    "with strangers.");
    add_ask_item( ({ "honey", "price", "pelargir", }),
	"say My bees make a fine honey. I get a good price for it in Pelargir.");
    add_ask_item( ({ "hives", "disturbed", "rob" }),
	({ "say I'm not sure why, but the bees have been acting "+
		  "rather disturbed lately.",
	   "say I do hope no one's trying to rob my hives." }) );


    add_ask_item( ({ "sheep", }),
       ({ "say I get plenty of wool from my sheep",
	  "say Sheep aren't very smart, I'm afraid.",
	  "say The sheep aren't much trouble." }) );
    add_ask_item( ({ "stupid", "smart", }),
	  "say Sheep aren't very smart, I'm afraid.");
    add_ask_item( ({ "wool" }),
	  "say The sheep aren't much trouble.");

    add_ask_item( ({ "sandros", "farmhand", "lazy", "trouble-maker" }),
	({ ({ "frown",
	      "say Sandros is nothing but a lazy trouble-maker.", }),
	   ({ "sigh",
	      "say I don't know why Raichim and Kellis keep Sandros on -- "+
		   "he's good for nothing.", }),
	   ({ "frown",
	      "say Sandros is a sorry excuse for a farmhand.", }) }) );

    add_ask_item( ({ "raichim", "kellis", "next farm", "neighbors", "farmers" }),
	({ ({ "smile",
	      "say Raichim and Kellis are good farmers." }),
	   "say I couldn't ask for better neighbors -- even "+
		"though they do keep that pig.",
	   "say Raichim and Kellis can grow just about anything. "+
		"They're born farmers." }) );

    add_ask_item( ({ "job", "work", "task", "assignment", 
	"chore", "quest", "help" }),
	({ "say I'm afraid I don't have any work for you. "+
		"You might ask Raichim or Kellis on the next farm over. ",
	   "say I've got everything well in hand here, thanks. "+
		"Perhaps Raichim would have a job for you; hers is "+
		"a larger farm.",
	   "say Thank you, but I don't need any extra help now. "+
		"Why don't you check with Kellis or Raichim?  They "+
		"sometimes hire on extra labour." }) );

    add_ask_item( ({ "cider", "for cider", "mug", "treat" }),
	VBFC_ME("cider_answer") );
} /* create_sirith_farmer */


/*
 * Function name:	reset_monster
 * Description	:	reset cider
 */
public void
reset_monster()
{
    ::reset_monster();
    Have_cider = 1;
} /* reset_monster */


/*
 * Function name:	catch_question
 * Description	:	mask parent to remember original question
 *			of which someone asks a question.
 * Arguments	:	question - The question as put
 */
public void
catch_question(string question)
{
    OrigQuestion = question;
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
     return 0;
} /* not_here_func */

/*
 * Function name:	cider_answer
 * Description	:	respond to questions about cider
 * Returns	:	null string ... response is gen'd via command()
 *
 *   add_ask_item( ({ "cider", "for cider", "mug", "treat" }),
 *
 */
public string
cider_answer()
{
    object cider;

    /* might have a glass of cider in inventory, if last "give" failed */
    if (objectp(cider = present("cider", TO)) ||
        (Have_cider && 
         objectp(cider = clone_object(SIRITH_FARMS_DIR+"obj/cider"))))
    {
    	if (!cider->move(TO))
	{
	    Have_cider = 0;
	    command("say I do happen to have one mug left ...");
	    command("give cider to "+TP->query_real_name());
	    return "";
	}
	cider->remove_object();
    }
    if (query_question() == "for cider")
    {
	command("say I'm sorry, but I don't have any cider just now.");
    }
    else if (!random(2))
    {
	command("say I do make good cider, though it's I who say it.");
    }
    else
    {
	command("say A mug of cider is a treat after a day in the fields.");
    }
    return "";
} /* cider_answer */
