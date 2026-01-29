/*
 * Trainer goblin - quest master for level 1
 * Boreaulam, April 2012
 *
 * Cotillion - 2020-10-04
 * - Fixed type confusion
 */
#pragma save_binary
#pragma strict_types


#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>

#include "defs.h"
inherit "/lib/skill_raise";
inherit "/lib/guild_support";


inherit "/std/monster";
inherit "/d/Sparkle/lib/quest_reward";
inherit MAKE_MONEY;

void start_quest();
void add_def_skill();
void set_up_skills();
string *train_text(int skill);


/*
 * Function name:        create_monster
 * Description  :        constructor for the object
 */
void
create_monster()
{
    set_adj("skillful");
    set_adj("experienced");
    set_short("skillful experienced goblin");
    set_race_name("goblin");

    set_long("The skillful experienced goblin is an excellent fighter. " +
             "He seems friendly and ready to teach adventurers " +
             "some skills. He is muttering to himself, and appears " +
             "troubled by something. Perhaps you can <ask> him if " +
             "he needs help." +
             "\n");

    add_prop(OBJ_M_NO_ATTACK, "It would not be a wise move to attack "+
    						  "such an experienced fighter.\n");
    add_prop(LIVE_M_NO_ACCEPT_GIVE, 0);
	set_base_stat(SS_STR, 40 + random(10));
	set_base_stat(SS_DEX, 30 + random(10));
	set_base_stat(SS_CON, 40 + random(10));
	set_base_stat(SS_INT, 20 + random(10));
	set_base_stat(SS_WIS, 30 + random(10));
	set_base_stat(SS_DIS, 20 + random(10));
    set_skill(SS_WEP_SWORD, 90 + random(10));
    set_skill(SS_WEP_AXE, 90 + random(10));
    set_skill(SS_WEP_KNIFE, 90 + random(10));
    set_skill(SS_PARRY, 90 + random(10));
    set_skill(SS_DEFENCE, 90 + random(10));
    set_skill(SS_UNARM_COMBAT, 90 + random(10));
    set_skill(SS_BLIND_COMBAT, 90 + random(10));
    set_skill(SS_AWARENESS, 80 + random(10));

	add_ask( ({ "task", "help", "quest"}),
	        "@@ask_help@@", 1);
	add_ask( ({ "armour", "goblin armour"}),
	        "@@ask_armour@@", 1);
	set_default_answer("@@ask_default");

	add_chat("Where is my armour?");
	add_chat("Some training can require specific items.");
	add_chat("I can train your skills.");
    set_chat_time(20);
    set_act_time(20);
    set_cchat_time(10);
    set_cact_time(10);

    set_up_skills();


} /* create_monster */

/*
 * Function name:		init
 * Description  :		init room
 */
void
init_living()
{
    ::init_living();
    init_skill_raise();
    init_guild_support();
} /* init */

/*
 * Function name:        ask_help
 * Description  :        result for ask "help"
 */
string
ask_help()
{
	if(this_player()->test_bit("Sparkle",
	GOBLIN_ARMOURER_GROUP,
	GOBLIN_ARMOURER_BIT)) {
		return "say You've helped me already. Thanks.";
	} else {
		command("frown");
		start_quest();
		return "say Please, find my armour. I've lost it somewhere around. I " +
			   "cannot teach students how to defend themselves without it!";
   }
} /* ask_help */

/*
 * Function name:        ask_default
 * Description  :        result for ask for unknown asks
 */
string
ask_default()
{
	if(!this_player()->test_bit("Sparkle",
	GOBLIN_ARMOURER_GROUP,
	GOBLIN_ARMOURER_BIT)) {
		return "The skillful experienced goblin says: I could use some help.\n";
    }
	return "The skillful experienced goblin says: I am grateful for your " +
	"help but I am too busy with training right now.\n";
} /* ask_default */

/*
 * Function name:        ask_armour
 * Description  :        result for ask "armour"
 */
string
ask_armour()
{
	if(!this_player()->test_bit("Sparkle",
	GOBLIN_ARMOURER_GROUP,
	GOBLIN_ARMOURER_BIT)) {
		command("sigh sadly");
		start_quest();
    }
	return "say It is a platemail made of iron. I don't believe that " +
		   "someone stole it. It is useless now, but it was my first " +
		   "armour and I use it to show how armours protect students " +
		   "as we spar in training.";
} /* ask_armour */

/*
 * Function name:        start_quest
 * Description  :        setup quest property with random value
 */
void
start_quest()
{
	if(!this_player()->query_prop(GCL1_QUEST_PROP))
		this_player()->add_prop(GCL1_QUEST_PROP, random(3)+1);
} /* start_quest */


/*
 * Function name:        show_hook
 * Description  :        respond to person showing the armour
 */
public void
show_hook(object ob)
{
    if (ob->id(LEVEL1_QUEST_PLATEMAIL))
    {
        set_alarm(1.0, 0.0, &command("say That's my armour! Give it here!"));
    }
    else if (this_player()->query_prop(GCL1_QUEST_PROP))
    {
        set_alarm(1.0, 0.0, &command("say What is that? It's not my armour."));
    }
    else
    {
        set_alarm(1.0, 0.0, &command("eyebrow probingly"));
    }
}

/*
 * Function name:        give_coin
 * Description  :        destruct quest armour
 */
void
give_coin(object player)
{
	make_platinum(1);
	command("say That's for your help.");
	command("give coin to " + OB_NAME(player));
} /* give_coin */


/*
 * Function name:        enter_inv
 * Description  :        reward person returning armour
 */
public void
enter_inv(object ob, object from)
{
    if(ob->id(LEVEL1_QUEST_PLATEMAIL))
    {
        if(interactive(from))
        {
            if(this_player()->test_bit("Sparkle",
            GOBLIN_ARMOURER_GROUP,
            GOBLIN_ARMOURER_BIT)) /* not supposed to happen */
            {
                command("hmm " + TP->query_name());
                command("say You've helped me already.");
                TP->catch_msg("You don't feel more experienced.\n");
            }
            else
            {
                command("thank " + TP->query_name());
                command("say Great! Now I will be able to teach my " +
                    "students how to defend themselves!");
		        give_reward(TP,
                        GOBLIN_ARMOURER_GROUP,
                        GOBLIN_ARMOURER_BIT,
                        GOBLIN_ARMOURER_EXP,
                        "goblin_armourer");
                set_alarm(1.0, 0.0, &give_coin(this_player()));
            }
            add_def_skill();
			this_player()->remove_prop(GCL1_QUEST_PROP);
            ::enter_inv(ob,from);

            set_alarm(1.0,0.0, &ob->remove_object());
        }
    }
	else
	{
        if(interactive(from))
        {
			command("say That's not what I asked for.");
			::enter_inv(ob,from);
			set_alarm(2.0,0.0,"drop_the_object",ob);
		}
	}
} /* enter_inv */



/*
 * Function name:        drop_the_object
 * Description  :        drop not quest armour
 */
void
drop_the_object(object ob)
{
	command("say I don't need this.");
    command("drop " + ob->query_short());
} /* drop_the_object */

/*
 * Function name:        add_def_skill
 * Description  :        adds defense skills
 */
void
add_def_skill()
{
    sk_add_train(SS_DEFENCE, train_text(SS_DEFENSE), 0, 0, 30);
} /* add_def_skill */

/*
 * Function name:		set_up_skills
 * Description  :		init trainable skills
 */
void
set_up_skills()
{
    sk_add_train(SS_WEP_AXE, train_text(SS_WEP_AXE), 0, 0, 30);
    sk_add_train(SS_WEP_CLUB, train_text(SS_WEP_CLUB), 0, 0, 30);
    sk_add_train(SS_WEP_KNIFE,   train_text(SS_WEP_KNIFE),   0, 0, 30);
    sk_add_train(SS_LOC_SENSE,   train_text(SS_LOC_SENSE),    0, 0, 30);
    sk_add_train(SS_TRACKING,   train_text(SS_TRACKING),    0, 0, 30);
    sk_add_train(SS_HUNTING,   train_text(SS_HUNTING),    0, 0, 30);
} /* set_up_skills */

/*
 * Function name:		train_text
 * Description  :		returns train text
 */
string *
train_text(int skill)
{
    string what, does, *text;

    switch(skill)
    {
    case SS_WEP_AXE:
	what = "use a axe";
	does = what;
	break;

    case SS_WEP_CLUB:
	what = "use a club	";
	does = what;
	break;

    case SS_WEP_KNIFE:
	what = "use a knife";
	does = what;
	break;

    case SS_LOC_SENSE:
	what = "know your location";
	does = what;
	break;

    case SS_TRACKING:
	what = "track a creature";
	does = what;
	break;

    case SS_HUNTING:
	what = "hunt an enemy";
	does = what;
	break;

    case SS_DEFENSE:
	what = "defend in combat";
	does = what;
	break;

    default:
	what = "do nothing. THIS IS A BUG";
	does = "meditate";
	break;
    }
    return ({what, does});
} /* train_text */
