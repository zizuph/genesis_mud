/*
 * /d/Gondor/lebennin/sirith/farms/npc/kellis.c
 * farmer for the pig & cattle farm (sirith/farms/farm1)
 *
 * Copyright (C) 1997 by Nancy L. Mintz (Gnadnar)
 *
 */

#pragma strict_types

inherit "/d/Gondor/lebennin/sirith/farms/npc/farmer";

#include <stdproperties.h>	/* for NPC_M_NO_ACCEPT_GIVE */
#include <ss_types.h>		/* for skills */
#include <macros.h>		/* for QCTNAME	*/
#include <const.h>		/* for G_MALE */
#include "/d/Gondor/defs.h"
#include "../defs.h"

#define	HOME	(SIRITH_FARMS_DIR+"farm1/northyard")

/* prototypes */
public void	create_sirith_farmer();
public varargs	void arm_me();
public int	not_here_func();


/*
 * Function name:	create_sirith_farmer
 * Description	:	set up the npc
 */
public void
create_sirith_farmer()
{
    set_name( ({ "kellis", "man" }) );
    set_living_name("kellis");
    set_race_name("human");
    set_gender(G_MALE);
    add_adj( ({ "stout", "tanned" }) );
		/* str, dex, con, int, wis, dis */
    set_stats(({55+random(10), 45+random(10), 45+random(10),
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
    GONDOR_MASTER->npcsize(TO, "normal", "plump");

    set_chat_time(10);
    add_chat("Raichim's pig is a lot of trouble.");
    add_chat("I wish Sandros would bestir himself.");
    add_chat("Have you seen my chickens? I've got quite a nice flock now.");
    add_chat("I hope the pig isn't in Druyan's fields again.");
    add_chat("Raichim says the milk's been off lately, "+
	"but it tastes fine to me.");
    add_chat("Between the pig and the chickens, we don't have a "+
	"problem with leftovers.");		/* hint, hint */
    add_chat("We manage pretty well on our own here.");
    add_chat("Raichim has a way with animals.");

    set_act_time(10);
    add_act(VBFC_ME("open_it"));
    add_act("emote rubs the back of his neck.");
    add_act("emote gives you a distracted smile.");

    /* respond nicely to questions */
    set_default_answer(
    	({ "peer @@query_player_name@@", "shrug" }) );
    set_not_here_func("not_here_func");
    set_dont_answer_unseen(1);

    add_ask_item( ({ "pig", "pigs", "sow", "sows", "trouble",
	"damage", "fields", "escape" }),
    	({ ({ "sigh",
	      "say That pig is always getting out of her pen.", }),
    	   ({ "sigh",
	      "say We keep the sty latched, but the pig still escapes.", }),
    	   ({ "sigh",
	      "say Raichim might appreciate some help with the pig.", }),
    	   ({ "sigh",
	      "say The pig loves to roam the fields, but she "+
		"damages the crops.", }) }) );
    add_ask_item( ({ "sty", "pen" }),
    	({ ({ "sigh",
	      "say That pig is always getting out of her pen.", }),
    	   ({ "sigh",
	      "say We keep the sty latched, but the pig still escapes.", }) }) );
    add_ask_item( "fields",
    	   ({ "sigh",
	      "say The pig loves to roam the fields, but she "+
		"damages the crops.", }) );

    add_ask_item( ({ "job", "work", "task", "assignment", "chore", "quest",
	"help", "reward", "pay", "payment", "pay me" }),
	"say  You should talk to Raichim about that.");

    add_ask_item( ({ "farm", "garden", "harvest", "crops", "vegetables",
	"manage" }),
	({ "say The garden seems to thrive this year.",
	   "say Oh, our garden is doing well this year.",
	   "say I think we'll have a good harvest this year." }) );

    add_ask_item( ({ "cow", "cows", "livestock", "animals", }),
	({ "say We have some good milk cows.",
	   "say I think the milk is fine, but Raichim "+
		"says it tastes a little off.",
	   "say The cows pretty much take care of themselves." }) );
    add_ask_item( ({ "milk" }),
	({ "say We have some good milk cows.",
	   "say I think the milk is fine, but Raichim "+
		"says it tastes a little off." }) );

    add_ask_item( ({ "chicken", "chickens", "night", "hen", "hens", "flock" }),
	({ "say If we get a few more chickens, I think we can "+
		"start selling some eggs.",
	   "say The chickens keep us well supplied with eggs.",
	   "say I always lock the chickens up at night.",
	   ({ "smile proudly",
	      "say They are a fine flock, aren't they?" }) }) );
    add_ask_item( ({ "egg", "eggs", }),
	({ "say If we get a few more chickens, I think we can "+
		"start selling some eggs.",
	   "say The chickens keep us well supplied with eggs." }) );
    add_ask_item( "night",
	   "say I always lock the chickens up at night.");

    add_ask_item( ({ "leftovers", "scraps", "kitchen scraps",
	"midden", "kitchen midden"}),
	({ "say The pig and the chickens eat any leftovers we have.",
	   "say The pig and the chickens are better than a kitchen midden."}) );

    add_ask_item( ({ "sandros", "mistake", "fire" }),
	({ ({ "sigh",
	      "say I think we made a mistake hiring Sandros." }),
	   ({ "frown",
	      "say We don't get much work out of Sandros." }),
	   "say Druyan says we should fire Sandros." }) );

    add_ask_item( ({ "druyan", "neighbor", "neighbors", }),
	({ ({ "smile",
	      "say Druyan's doing quite well with her sheep." }),
	   ({ "say Druyan makes an excellent cider.",
	      "wink" }),
	   "say Those bees of Druyan's chased me clear off "+
		"the farm once!" }) );
    add_ask_item("sheep",
	({ "smile", "say Druyan's doing quite well with her sheep." }) );
    add_ask_item("cider",
	({ "say Druyan makes an excellent cider.", "wink" }) );
    add_ask_item("bees",
	"say Those bees of Druyan's chased me clear off the farm once!");

    add_ask_item( ({ "raichim", "wife" }),
	({ ({ "smile",
	      "say Raichim can grow anything." }),
	   "say Raichim has quite a way with livestock.",
	   "say Raichim and I have farmed here for years." }) );
} /* create_sirith_farmer */


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
	obj->configure("soft", "brown", "cotton", "loose", "");
    }
    if (objectp(obj = present("trousers", TO)))
    {
	obj->configure("tightly-woven", "heavy", "cloth",
	    "loose-fitting",
	    ", with leather patches reinforcing the knees");
    }
} /* arm_me */


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
