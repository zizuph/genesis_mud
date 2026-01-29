/*
 *	/d/Gondor/common/quest/enchant_seed/rranger.c
 *
 *	An old ranger living in a hut in Druedain Forest.
 *	The ranger gives out and rewards a quest to enchant seeds by
 *	bringing them to an alchemist living in Hobbiton. 
 *
 *	Coded by Elessar 1992
 *
 *	Modification log:
 *	15-Feb-1997, Olorin:	General revision.
 *	02-Sep-1998, Gnadnar:	fix some typos, tidy up.
 */	
#pragma strict_types

inherit "/d/Gondor/common/npc/npc_ranger.c";

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/bits.h"

#define DID_VISIT_ME	  "_did_visit_old_ranger"
#define RANGER_GIVEN_SEED "_old_ranger_gave_seed"
#define QUEST_SEED	 ("/d/Gondor/common/quest/enchant_seed/normseed")
#define ENCHANTED_SEED	 ("/d/Gondor/common/quest/enchant_seed/magseed")
#define RANGER_GUARD     ("/d/Gondor/guilds/rangers/npc/ranger_guard")

//Prototypes
public void	create_ranger();
public void	reset_monster();
public void	arm_me();
public void	enter_inv(object obj, object from);
public void	do_thank(object player);
public void	do_reward(object player);
public void	do_give_back(object obj, object to);
public string	ask_magic();
public string	ask_spellbook();
public string	ask_seed();
public string	ask_task();
public string	ask_rangers();
public string	ask_herbs();
public string	ask_gondor();
public string	ask_ithilien();
public string	ask_lebennin();
public string	ask_sauron();
public string	ask_shire();
public string	ask_rivendell(); public string	ask_orcs();
public void	do_inform(string what, object pl);
public void	pigeon_msg();
public void	clone_guards();
public void	attacked_by(object ob);
public int	special_attack(object victim);

//Global variables
int     Seeds_left,
        Alarm_id;


/*
 * Function name:	create_ranger
 * Description	:	set up the ranger
 */
public void
create_ranger()
{
    set_name(({"man", "ranger", "dunadan", }));
    set_adj(({"old", "rugged", }));
    set_race_name("human");
    set_gender(G_MALE);
    set_long(BSN(
	"This old man looks like he has experienced quite a lot. His "+
	"face is wrinkled and weather-beaten, and his hair gray of age. "+
	"He looks back at you with a gleam of interest in his eyes."));

    set_stats(({ 29, 33, 41, 76, 56, 74 }));
    set_tell_active(1);

    set_skill(SS_WEP_SWORD, 82);
    set_skill(SS_PARRY,     76);
    set_skill(SS_DEFENCE,   75);

    add_prop(CONT_I_HEIGHT,   204);
    add_prop(CONT_I_WEIGHT, 92000);

    add_prop(LIVE_I_NEVERKNOWN, 1);
    remove_prop(NPC_M_NO_ACCEPT_GIVE);

    set_chat_time(4);
    add_chat("I was once a Ranger, you know. That was some time ago though.");
    add_chat("I was wounded in a fight in Ithilien.");
    add_chat("The weather is nice nowadays.");
    add_chat("I've heard rumours of orc-spies in the Firienwood somewhere.");
    add_chat("Now how can I get this seed enchanted?");
    add_chat("Orcs are despicable creatures - they should be disposed of!");
    add_chat("Those Southrons are Men of bad morals and without honour.");

    add_cchat("Stop that right now!");
    add_cchat("Go away, or I shall have to kill you!");
    add_cchat("I have a distaste for goblins and murderers!");
    add_cchat("I am quite capable of fighting you, you know!");

    enable_reset();
    add_ask(({"magic", "about magic",}), VBFC_ME("ask_magic"));
    add_ask(({"spells", "spellbook", "about spellbook"}),
	VBFC_ME("ask_spellbook"));
    add_ask(({"rangers", "ranger", "about rangers",}), VBFC_ME("ask_rangers"));
    add_ask(({"gondor", "about gondor",}), VBFC_ME("ask_gondor"));
    add_ask(({"ithilien", "about ithilien",}), VBFC_ME("ask_ithilien"));
    add_ask(({"lebennin", "about lebennin",}), VBFC_ME("ask_lebennin"));
    add_ask(({"seed", "about seed",}), VBFC_ME("ask_seed"));
    add_ask(({"task", "quest", "for task", "for quest", "about task",
	"about quest"}),
	VBFC_ME("ask_task"));
    add_ask(({"herbs", "about herbs",}), VBFC_ME("ask_herbs"));

    reset_monster();
} /* create_ranger */


/*
 * Function name:	reset_monster
 * Description	:	replenish seeds
 */
public void
reset_monster()
{
    ::reset_monster();
    Seeds_left = 4;
} /* reset_monster */

/*
 * Function name:	arm_me
 * Description	:	set up our equipment
 */
public void
arm_me()
{
    FIX_EUID

    clone_object(WEP_DIR + "dlsword")->move(TO);
    command("wield longsword");
    clone_object(ARM_DIR + "drcloak")->move(TO);
    command("wear cloak");
    clone_object(ARM_DIR + "dlboots")->move(TO);
    command("wear boots");
} /* arm_me */


/*
 * Function name:	enter_inv
 * Description	:	mask parent to respond to gifts
 * Arguments	:	object obj -- the entering object
 *			object from -- its source
 */
public void
enter_inv(object obj, object from)
{
    ::enter_inv(obj, from);

    if (!objectp(from) ||
	!living(from) ||
	!objectp(obj))
    {
       return;
    }

    if (MASTER_OB(obj) != ENCHANTED_SEED)
    {
        set_alarm(3.0, 0.0, &do_give_back(obj, from));
    }
    else if (from->test_bit("Gondor", GONDOR_GROUP, ENCHANT_SEED_BIT))
    {
        set_alarm(4.0, 0.0, &do_thank(from));
    }
    else
    {
        // We have to do this check to prevent multiple rewards!
        if (!Alarm_id)
	{
            Alarm_id = set_alarm(4.0, 0.0, &do_reward(from));
	}
    }
} /* enter_inv */


/*
 * Function name:	do_thank
 * Description	:	just thank player if s/he has already done
 *			the quest
 * Arguments	:	object player -- the source of the seed
 */
public void
do_thank(object player)
{
    if (!objectp(player))
    {
	return;
    }
    if (ENV(player) != ENV(TO))
    {
        command("say Oh well, I didn't even get the chance to thank the "
          + player->query_race_name()+".");
        return;
    }
    if (player->query_prop("_gondor_i_got_thanks"))
    {
        command("say Thanks again for your help!");
        command("wave");
        return;
    }
    player->add_prop("_gondor_i_got_thanks", 1);
    command("say Thanks again for your help!");
    command("say Here is an attanar - hope it will be helpful!");
    command("say The attanar berry will heal you a little when you eat it.");
    clone_object(HERB_DIR + "attanar")->move(TO);
    command("give berry to "+player->query_real_name());
    command("wave");
} /* do_thank */


/*
 * Function name:	do_reward
 * Description	:	reward player for enchanted seed quest
 * Arguments	:	object player -- the lucky player
 */
public void
do_reward(object player)
{
    object  pouch;

    Alarm_id = 0;

    if (!objectp(player))
    {
	return;
    }
    if (player->test_bit("Gondor", GONDOR_GROUP, ENCHANT_SEED_BIT))
    {
	/* "cannot happen" */
	do_thank(player);
	return;
    }
    if (ENV(player) != ENV(TO))
    {
        command("say Oh well, I didn't even get the chance to reward the "
          + player->query_race_name()+".");
        return;
    }

    FIX_EUID
    command("say I thank you, my friend!");
    player->set_bit(GONDOR_GROUP, ENCHANT_SEED_BIT);
    player->add_exp_quest(ENCHANT_SEED_EXP);
    player->adjust_alignment(70);
    LOG_QUEST(player, ENCHANT_SEED_EXP, "ENCHANT SEED");
    pouch = clone_object(RANGER_DIR + "obj/herbpouch");
    pouch->add_prop(CONT_I_CLOSED, 0);
    clone_object(HERB_DIR+"attanar")->move(pouch);
    clone_object(HERB_DIR+"attanar")->move(pouch);
    clone_object(HERB_DIR+"suranie")->move(pouch);
    clone_object(HERB_DIR+"tuo")->move(pouch);
    pouch->add_prop(CONT_I_CLOSED, 1);
    pouch->move(TO, 1);

    if (IS_RANGER(player))
    {
        command("say I would reward you with a copy of the spellbook of "
          + "the Rangers.");
        command("say But now, my supply of spellbooks is lost.");
        command("say I will at least give you some reward - here!");
        player->catch_msg("You feel more experienced.\n");
        command("give pouch to "+player->query_real_name());
        command("say There you are! A herbpouch and some herbs!");
        command("say Hope it will help.");
    }
    else
    {
        command("say I must think of some way to reward you....");
        command("ponder");
        command("say Oh yes! I'll give you a few healing herbs!");
        command("say That will always come in handy.");
        command("smile");
        player->catch_msg("You feel more experienced.\n");
        command("give pouch to "+player->query_real_name());
        command("say There you are! You can probably buy more herbs "+
	    "from Lothmir.");
        command("say He can tell you more about these herbs, if you like.");
        command("smile");
    }
    command("say Now, good luck out there, and thanks again!");
    command("wave");
} /* do_reward */


/*
 * Function name:	do_give_back
 * Description	:	return coins
 * Arguments	:	object obj -- the gift
 *			object to -- its source
 *
 * XXX why don't we return all gifts?
 */
public void
do_give_back(object obj, object to)
{
    if (!obj->id("coin"))
    {
	command("smile");
        return;
    }

    command("say You don't have to give me that.");
    command("give " + OB_NAME(obj) + " to " +
        to->query_real_name());

    if (objectp(obj) &&
	ENV(obj) == TO)
    {
        command("drop " + OB_NAME(obj));
    }
} /* do_give_back */


/*
 * Function name:	ask_magic
 * Description	:	respond to questions about magic
 * Returns	:	string "" -- response written before return
 */
public string
ask_magic()
{
    set_alarm(1.0, 0.0, &do_inform("magic1", TP));
    return"";
} /* ask_magic */

/*
 * Function name:	ask_spellbook
 * Description	:	respond to questions about spellbook
 * Returns	:	string "" -- response written before return
 */
public string
ask_spellbook()
{
    set_alarm(4.0, 0.0, &do_inform("magic", TP));
    return "";
} /* ask_spellbook */

/*
 * Function name:	ask_seed
 * Description	:	respond to questions about seed
 * Returns	:	string "" -- response written before return
 */
public string
ask_seed()
{
    command("think");
    set_alarm(4.0, 0.0, &do_inform("seeds", TP));
    return "";
} /* ask_seed */

/*
 * Function name:	ask_task
 * Description	:	respond to questions about task/quest
 * Returns	:	string "" -- response written before return
 */
public string
ask_task()
{
    command("smile");
    set_alarm(3.0, 0.0, &do_inform("task", TP));
    return "";
} /* ask_task */

/*
 * Function name:	ask_rangers
 * Description	:	respond to questions about rangers
 * Returns	:	string "" -- response written before return
 */
public string
ask_rangers()
{
    command("nod");
    set_alarm(3.0, 0.0, &do_inform("rangers", TP));
    return "";
} /* ask_rangers */

/*
 * Function name:	ask_herbs
 * Description	:	respond to questions about herbs
 * Returns	:	string "" -- response written before return
 */
public string
ask_herbs()
{
    command("nod");
    set_alarm(4.0, 0.0, &do_inform("herbs", TP));
    return "";
} /* ask_herbs */

/*
 * Function name:	ask_gondor
 * Description	:	respond to questions about gondor
 * Returns	:	string "" -- response written before return
 */
public string
ask_gondor()
{
    command("smile");
    set_alarm(4.0, 0.0, &do_inform("gondor", TP));
    return "";
} /* ask_gondor */

/*
 * Function name:	ask_ithilien
 * Description	:	respond to questions about ithilien
 * Returns	:	string "" -- response written before return
 */
public string
ask_ithilien()
{
    set_alarm(4.0, 0.0, &do_inform("ithilien", TP));
    return "";
} /* ask_ithilien */

/*
 * Function name:	ask_lebennin
 * Description	:	respond to questions about lebennin
 * Returns	:	string "" -- response written before return
 */
public string
ask_lebennin()
{
    set_alarm(3.0, 0.0, &do_inform("lebennin", TP));
    return "";
} /* ask_lebennin */

/*
 * Function name:	ask_sauron
 * Description	:	respond to questions about sauron
 * Returns	:	string "" -- response written before return
 */
public string
ask_sauron()
{
    set_alarm(4.0, 0.0, &do_inform("sauron", TP));
    return "";
} /* ask_sauron */

/*
 * Function name:	ask_shire
 * Description	:	respond to questions about shire
 * Returns	:	string "" -- response written before return
 */
public string
ask_shire()
{
    set_alarm(4.0, 0.0, &do_inform("shire", TP));
    return "";
} /* ask_shire */

/*
 * Function name:	ask_rivendell
 * Description	:	respond to questions about rivendell
 * Returns	:	string "" -- response written before return
 */
public string
ask_rivendell()
{
    set_alarm(4.0, 0.0, &do_inform("rivendell", TP));
    return "";
} /* ask_rivendell */

/*
 * Function name:	ask_orcs
 * Description	:	respond to questions about orcs
 * Returns	:	string "" -- response written before return
 */
public string
ask_orcs()
{
    set_alarm(4.0, 0.0, &do_inform("orcs", TP));
    return "";
} /* ask_orcs */


/*
 * Function name:	do_inform
 * Description	:	here is where we really respond to questions
 * Arguments	:	string what -- the topic
 *			object pl -- the player who asked
 */
public void 
do_inform(string what, object pl)
{
    if (!objectp(pl) ||
	ENV(pl) != ENV())
    {
	/* no point in nattering on if they're gone */
	return;
    }
    switch (what)
    {
    case "magic1":
        command("say Ah - you are interested in magic, are you?");
        command("nod");
        command("say So was I. I gave that up when my spellbook disappeared, "
             +  " I'm too old to gather spells for a new book.");
        command("think");
        set_alarm(6.0, 0.0, &do_inform("magic", pl));
        break;
    case "magic":
        command("say The magic of the Rangers is not powerful, since there");
        command("say are other qualities about us. However, the magic is");
        command("say helpful - we can heal and rest others with it.");
        command("think");
        set_alarm(6.0, 0.0, &do_inform("magic2", pl));
        break;
    case "magic2":
        command("say I know of someone who still takes interest in magic "+
	    "though.");
        command("say He lives in Lebennin.");
        command("ponder");
        set_alarm(6.0, 0.0, &do_inform("leb_ranger", pl));
        break;
    case "task":
        command("say Ah! I supply the Rangers with herbs.");
        command("say But there is one important herb I have problems with.");
        command("say You must help me with that.");
        command("say As a reward, I can give you something useful, I suppose.");
        set_alarm(6.0, 0.0, &do_inform("seeds", pl));
        break;
    case "ranger":
    case "rangers":
        command("say Yes, I was once a Ranger of Ithilien.");
        command("say Ithilien became too dangerous for me, so I moved here.");
        command("say This is a much safer and more peaceful place.");
        command("say Besides, there are Rangers near, which makes it even safer.");
        command("sigh");
        break;
    case "seeds":
        command("say I don't know how to enchant the seeds of the lothore,");
        command("say and only the enchanted seeds will grow.");
        if (Seeds_left--)
        {
            if (pl->query_prop(RANGER_GIVEN_SEED))
            {
                command("say I hope you can make do with the one I gave you.");
                command("say I do not have any further to give you.");
                return;
            }
            clone_object(QUEST_SEED)->move(TO,1);
            command("drop seed");
            pl->add_prop(RANGER_GIVEN_SEED, 1);
            command("say Oops! My hands are not as steady as before.");
            command("say Good luck with it!");
        }
        else
        {
            command("say And now I have no more seeds left.");
            command("sigh");
        }
        break;
    case "gondor":
        command("smile");
        command("say Gondor is the fairest land - second to Ithilien.");
        command("say They are preparing for war in Minas Tirith, I've heard.");
        command("say I think they will need help to survive though.");
        break;
    case "ithilien":
        command("sigh");
        command("say Ithilien! Ah....fair forests, fragrant flowers,");
        command("say green meadows......");
        command("say But now it is taken by the enemy.");
        command("sniff");
        break;
    case "herbs":
        command("say Herbs, you say? Oh yes, I know some herbs.");
        command("say There are several kinds growing in this forest,");
        command("say and I harvest them for the Rangers now and then.");
        command("say You can probably find some redweed just outside,");
        command("say and maybe even a lothore, if you're lucky.");
        command("smile");
        break;
    case "shire":
        command("smile");
        command("say The Shire, you say? That is a place far up north.");
        command("say The Halflings live there, or hobbits, they call themselves.");
        command("say The Rangers of the North are protecting them in secret.");
        break;
    case "lebennin":
        command("say Yes, I know where Lebennin is.");
        command("say Lebennin are the lands and vales south of Minas Tirith,");
        command("say west of the Anduin, and north of Pelargir.");
        command("say Fertile lands, they are, and many dwell there,");
        command("say as farmers or cattle-herders.");
        command("smile");
        command("say I even know of a Ranger who lives there.");
        command("say Ex-ranger, I should say. He's very interested in "+
	    "Numenorean magic.");
        command("ponder");
        break;
    case "leb_ranger":
        command("say He was, or perhaps still is, a Ranger of Gondor,");
        command("say a dabbler in magic. Scholarly in his ways,");
        command("say he has been searching for lost lore,");
        command("say Numenorean lore, and even Elven lore. Magic.");
        command("say I guess he will accept visitors, at least if he knows");
        command("say that you are coming. I will see to that.");
        command("say I'll send a pigeon to him telling him you are coming.");
        command("say Look for a small hut near Pelargir, and you'll find him.");
        command("wave");
        pl->add_prop(DID_VISIT_ME,1);
        set_alarm(4.0, 0.0, pigeon_msg);
        break;
    case "sauron":
    case "evil one":
        command("emote ");
        command("say Don't ever mention that name!");
        command("say He has spies everywhere!");
        break;
    case "orcs":
        command("growl");
        command("say Personally: I hate orcs!");
        command("say They are servants of evil, and will never");
        command("say be able to think of anything but evil deeds.");
        command("say I fear that there are orcs in Gondor even now!");
        command("sigh");
        break;
    case "rivendell":
    case "imladris":
        command("shrug");
        command("say "+CAP(what)+"? What's that?");
        break;
    default:
        if (!random(4))
	{
            command("say Hmm. I don't think I quite understand.");
	}
        break;
    }
} /* do_inform */


/*
 * Function name:	pigeon_msg
 * Description	:	send a pigeon
 */
public void
pigeon_msg()
{
    tell_room(ENV(TO), BSN(
        "The old ranger writes a brief message on a piece of paper and "+
        "ties it to the leg of a carrier pigeon, which he then sends off."));
} /* pigeon_msg */



/*
 * Function name:	clone_guards
 * Description	:	clone up some guards to protect the ranger
 */
public void
clone_guards()
{
    int n;
    object tmp;

    FIX_EUID

    tell_object(find_player("elessar"), "DEBUG: Old ranger: clone_guards called.\n");
    n = sizeof(filter(all_inventory(ENV(TO)), &->id("ranger")));
    if (n < 6)
    {
        tell_object(find_player("elessar"), "DEBUG: Old ranger: clone should happen.\n");
        tmp = clone_object(RANGER_GUARD);
        tmp->arm_me();
        tmp->move_living("into the hut", ENV(TO));
        tmp->command("say " + ONE_OF_LIST(({"Now, what's going on here?",
           "I thought I heard fighting!", "Enemies!"})));
        if (TO->query_attack())
        {
            tmp->do_attack(TO->query_attack());
            TO->query_attack()->attack_object(tmp);
        }
        set_alarm(5.0, 0.0, clone_guards);
    }
} /* clone_guards */



/*
 * Function name:	attacked_by
 * Description	:	respond to an attack
 * Arguments	:	object ob -- the attacking object
 */
public void
attacked_by(object ob)
{
    tell_object(find_player("elessar"), "DEBUG: Old ranger: attacked by called.\n");
    if (!present("_ranger_guard", ENV(TO)))
        clone_guards();
    ::attacked_by(ob);
} /* attacked_by */



/*
 * Function name:	special_attack
 * Description	:	Called from the external combat object's heart_beat
 *                	routine. We summon guards when attacked.
 * Arguments	:	object victim -- the person we're fighting
 * Returns	:	int -- 0 if we want this round to continue
 *			       1 if we are done with this round
 */
public int
special_attack(object victim)
{
    if (!present("_ranger_guard", ENV(TO)))
    {
        clone_guards();
    }
    return ::special_attack(victim);
} /* special_attack */
