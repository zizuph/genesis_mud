/* A version of the Questmaster in Krynn 

   Made by Nick
*/

#include "/d/Krynn/common/defs.h"
#include "../local.h"
#include "quest_m.h"
#include <ss_types.h>
#include <language.h>
#include <stdproperties.h>
#include <macros.h>
#include <const.h>

inherit M_FILE

object passer; /* Who is trying to pass something */
int ptype;     /* What type of quest is he trying to pass */

/*
 * Prototypes
 */
int check_valid_type(string str);
int give_reward(int type);
int query_quest_number(int type, object ob);
int inc_quest_number(int type, object ob);
int set_quest_number(int type, int num, object ob);
int give_tour_card();
int do_ask(int type);
int do_pass(int type);
int check_more_quests(int type, int num);
void my_kick(object actor, string adverb);

EMOTE_HOOK

/*
 * Function name: create_monster
 * Description:   Create the monster
 */
void
create_krynn_monster()
{
    int i;

    ptype = -1;

    set_name("tarshir");
    add_name("quest master");
    add_name("questmaster");
    add_name("quest_master");
    
    set_race_name("elf");
    set_living_name("qmaster");
    set_gender(G_MALE);
    set_long("This is Tarshir, the Quest master, he is sitting on the soft " +
	     "rug juggling fireballs. It seems he's very experienced, " +
	     "better not mess with him.\n");

    set_alignment(300 + random(100));

    if (IS_CLONE)
    {
        set_act_time(40);
    	add_act(({"sigh", "say Not much action here nowadays."}));
    	add_act("stare");
    	add_act("giggle");
    	add_act("twiddle");
	add_emote_hook("smile",1.0,&command("smile"));
	add_emote_hook("bow",1.0,&command("nod"));
	add_emote_hook("poke",1.0,&command("say Ohh no! Another Tricky fan."));
	add_emote_hook("kick",1.0,my_kick);
    }

    for (i = 0; i < 6; i++)
        set_base_stat(i, 80 + random(20));
    set_skill(SS_DEFENCE, 80 + random(20));

    set_all_attack_unarmed(40, 53);
    set_all_hitloc_unarmed(50);

    ALWAYSKNOWN;
    add_prop(OBJ_I_NO_ATTACK, 1);
    add_prop(OBJ_I_NO_MAGIC_ATTACK, 1);
    add_prop(LIVE_S_EXTRA_SHORT, ", the Quest master");

    add_ask("[small] [major] 'adventure' / 'quest' / 'tour' / 'reward'",
	    "point at sign",1);
}

/*
 * Function name: init
 * Description:   Add some commands to the visitors
 */
void
init_living()
{
    ADA("reward"); /* Get a reward */
    ADA("ask");    /* Ask about new quests */
    ADA("get");    /* Get a touristing card */
    ADA("pass");   /* pass over a quest, it was too hard? */
}

/*
 * Function name: reward
 * Description:   The player wants a reward, shall we give one?
 * Arguments:     str - describing what quest want reward for
 * Returns:       1/0
 */
int
reward(string str)
{
    int type;

    type = check_valid_type(str);

    if (type >= 0)
    {
	if (type == QUEST)
	{
	    command("say Well I don't give any rewards for bigger quests.\n");
	    command("smile " + TP->query_real_name());
	    return 1;
	}
	if (give_reward(type))
	    say(QCTNAME(TP) + " got a nice reward.\n");
	else
	    say(BS(QCTNAME(TP) + 
		" tried to get a reward but was not worthy one.", 70));
	return 1;
    }

    NF("What kind of reward did you want?\n");
    return 0;
}

/*
 * Function name: ask
 * Description:   The player wants to know what quests there are
 * Arguments:     str - the string to tell what quests we want to know
 * Returns:       1/0
 */
int
ask(string str)
{
    int type, i;

    type = check_valid_type(str);

    if (type >= 0)
    {
	i = do_ask(type);
	if (!i)
	  write("There are no more quests for you to solve of that type.\n");
	if (i == 2)
	  write("There are no quests for you to solve of that type yet.\n");
	say(QCTNAME(TP) + " asks about some " + ATYPES[type] + ".\n");
	return 1;
    }

    NF("I didn't understand what you wanted to ask about.\n");
    return 0;
}

/*
 * Function name: get
 * Description:   get command, used to get a prospering card
 * Arguments:     str - the string, if not a right prosp command
 *                      we send it away to the proper give.
 * Returns:       1/0
 */
int
get(string str)
{
    int num;

    if ((str == "touristing card") || (str == "tour"))
    {
	num = query_quest_number(TOURISTING, TP) + 1;
	if (check_more_quests(TOURISTING, num))
	    give_tour_card();
	else
	    write("Too bad there isn't any more touristing for " +
		  "you to do now.\n");
	return 1;
    }
    return 0;
}

/*
 * Function name: pass
 * Description:   A possibility to pass a quest
 * Arguments:     str - what type to pass
 * Returns:       1/0
 */
int
pass(string str)
{
    int type;

    type = check_valid_type(str);

    if (type >= 0)
    {
	if ((passer != TP) || (ptype != type))
	{
	    passer = TP;
	    ptype = type;
	    write("You could lose experience by passing, and you won't be \n" +
		"able to solve the quest. Try to pass again if you still\n" +
		"want to.\n");
	    return 1;
	}

	ptype = -1;

	if (type == QUEST)
	{
	    command("say The bigger quests are not passable you know.\n");
	    command("smile " + TP->query_real_name());
	    return 1;
	}
	if (do_pass(type))
	    say(QCTNAME(TP) + " gave up and passed a " + ATYPES[type] + ".\n");
	else
	    say(BS(QCTNAME(TP) + 
		" tried to pass over something but couldn't.", 70));
	return 1;
    }

    NF("What kind did you want to pass?\n");
    return 0;
}

/*
 * Function name: check_valid_type
 * Description:   check what quest type the string is
 * Arguments:     str - hopefully describing a quest type
 * Returns:       The quest type or -1
 */
int
check_valid_type(string str)
{
    int type, i;

    type = -1;

    for (i = 0; i < NUM_OF_TYPES; i++)
	if ((str == ATYPES[i]) || (str == SH_ATYPES[i]))
	{
	    type = i;
	    break;
        }

    return type;
}

/*
 * Function name: check_more_quests
 * Description:   check if there is at least one more quest of this type
 * Arguments:     type - the type of quest to check
 * Returns:       1/0
 */
int
check_more_quests(int type, int num)
{
    string name;

    name = QUEST_FILE(type, num);
    if (file_size(name) >= 0)
	return 1;
    return 0;
}

/*
 * Function name: give_tour_card
 * Description:   give the player a touristing card
 * Returns:       1/0 depending if the player got a card
 */
int
give_tour_card()
{
    string name;
    int num;

    num = query_quest_number(TOURISTING, TP) + 1;
    while ((present(SH_ATYPES[TOURISTING] + num, TP)) &&
		check_more_quests(TOURISTING, num + 1))
	num++;

    if ((present(SH_ATYPES[TOURISTING] + num, TP)) ||
	(!check_more_quests(TOURISTING, num)))
    {
	write("I'm afraid you already have all the touristing cards " +
	      "available.\n");
	return 0;
    }

    name = QUEST_FILE(TOURISTING, num);
    if (clone_object(name)->move(TP))
    {
	write("You cannot carry anything more, no card for you.\n");
	return 0;
    }

    say(QCTNAME(TP) + " gets a touristing card.\n");
    write("You get yourself a touristing card.\n");

    return 1;
}
    
/*
 * Function name: give_reward
 * Description:   give the player a reward if he has one to collect
 * Arguments:     type - the type of reward to get
 * Returns:       1/0
 */
int
give_reward(int type)
{
    int num, tmp;
    string name;
    object ob;
    
    num = query_quest_number(type, TP) + 1;
    if (!check_more_quests(type, num))
      {
	  write("You won't get any reward since there is no quest available.\n");
	  return 0;
      }
    
    if (type == TOURISTING)
      {
	  ob = present(SH_ATYPES[type] + num, TP);
	  if (!ob)
	    {
		write("You have to get the card first and then do the " +
		      "touristing, now you won't get a reward.\n");
		return 0;
	    }
	  tmp = ob->reward(TP);
	  if (tmp > 0) 
	    {
		/* QUEST_LOGGER->solve_quest(SH_ATYPES[type] + num,TP,tmp); */
		ob->remove_object();
	    }
      } 
    else 
      {
	  name = QUEST_DIR + SH_ATYPES[type] + num;
	  tmp = name->reward(TP);
	  /* QUEST_LOGGER->solve_quest(SH_ATYPES[type] + num,TP,tmp);*/
      }

    /* The file object takes care of the reward */ 
    /* and the reward message to the player. */
    /* Even if the player didn't get any reward. */
    
    if (tmp > 0) 
      {
	  write("The quest master touches you and you feel more experienced.\n");
	  inc_quest_number(type,TP);
	  return 1;
      }
    return 0;
}

/*
 * Function name: query_quest_number
 * Description:   Gives the stage the player is on of that quest type
 * Arguments:     type - the type
 * 		  ob - the object to check
 * Returns:       the number the player stands on
 */
int
query_quest_number(int type, object ob)
{
    int i, sum, base;

    /* The bits is valued like a standard binary number. For tour it's like: */
    /* Group 0, bit 0   1   2   3   4   5                                    */
    /*              32  16  8   4   2   1                                    */
    /* i.e The lowest number of the bit is in the number the one that values */
    /* the most.                                                             */

    base = 1;
    for (i = 0; i < NUM_OF_BIT[type]; i++)
    {
	sum += base * ob->test_bit("Krynn", GROUP[type], E_BIT[type] - i);
	base *= 2;
    }

    return sum;
}

/*
 * Function name: set_quest_number
 * Description:   Set the stage in the player for that quest type
 * Arguments:     type - the type
 * 		  ob - the object to do the set in
 *		  num - the number to set
 * Returns:       the number the player stands on
 */
int
set_quest_number(int type, int num, object ob)
{
    int *base, i;

    if (num < 0)
	return -1;

    base = ({ 1, 2, 4, 8, 16, 32, 64, 128, 256 }); /* Just add if needed */

    for (i = NUM_OF_BIT[type] - 1; i >= 0; i--)
	if ((num / base[i]) > 0)
	{
	    ob->set_bit(GROUP[type], E_BIT[type] - i);
	    num -= base[i];
	} else {
	    ob->clear_bit(GROUP[type], E_BIT[type] -i);
	}

    return query_quest_number(type, ob);
}

/*
 * Function name: inc_quest_number
 * Description:   Increments the stage the player is on of that quest type
 * Arguments:     type - the type
 *		  ob - the object to be incremented :)
 * Returns:       the number the player stands on
 */
int
inc_quest_number(int type, object ob)
{
    return set_quest_number(type, query_quest_number(type, ob) + 1, ob);
}


/*
 * Function name: do_ask
 * Description:   performs a ask about a new quest if there is one
 * Arguments:     type - the type of quest 
 * Returns:       1/0
 */
int
do_ask(int type)
{
    string name;
    int num, i;

    if (type == QUEST)
    {
  /* Now this call ask() in every quest, even the ones solved by the player */
	num = 1;
	while (check_more_quests(type, num))
	{
	    name = QUEST_FILE(type, num);
	    num++;
	    i = i | (name->ask(TP));
	}
	if (num == 1)
	    write("There are currently no quests of this type.\n");
	return i;
    }
    else
    {
	num = query_quest_number(type, TP) + 1;

        while (check_more_quests(type, num))
	{
	    name = QUEST_FILE(type, num);
	    num++;
	    if (i = name->ask(TP))
		break;
	}
	if (i != 1)
	    return i;

        while (check_more_quests(type, num))
	{
	    name = QUEST_FILE(type, num);
	    num++;
	    if (name->ask())
	    {
		write("\nAfterwards there is this one more to do:\n\n");
		if (name->ask(TP) == 2)
		  write("Come back to me after you have grown a little and ask again.\n");
		break;
	    }
	}
    }

    return 1;		
}

/*
 * Function name: do_pass
 * Description:   performs a pass command
 * Arguments:     type - the type of quest 
 * Returns:       1/0
 */
int
do_pass(int type)
{
    string name;
    object ob;
    int num, tmp;

    num = query_quest_number(type, TP) + 1;

    if (!check_more_quests(type, num))
    {
	write(BS("The quest master explains to you that there is no " +
	      "current " + ATYPES[type] + " for you to do and that means " +
	      "you can't pass.", 70));
	return 0;
    }

    if (!check_more_quests(type, num + 1))
    {
	write(BS("The quest master explains to you that there are no " +
	      ATYPES[type] + " after the current one and there for no pass " +
	      "is granted.", 70));
	return 0;
    }

    name = QUEST_FILE(type, num);

    if (tmp = name->pass(TP))
    {
	if (tmp == 1)
    	{
 	    write("The quest master touches you and you feel less " +
		  "experienced.\n");
	    inc_quest_number(type, TP);
	}

	if (type == TOURISTING)
	{
	    if (ob = present(SH_ATYPES[type] + num, TP))
		ob->remove_object();
	}
	return 1;
    }

    return 0;		
}

/*
 * Function name: enter_inv
 * Description:   To prevent things to be given to this object
 * Arguments:     like in std/object
 */
void
enter_inv(object ob, object from)
{
    set_alarm(1.0,0.0,"give_back", ob);
    if (ob->move(from))
	ob->move(environment(from));
}

/*
 * Function name: give_back
 * Description:   Get the text out on screen
 */
void
give_back(object ob)
{
    command("say I don't want " + LANG_ADDART(ob->short()));
    command("say I'll put it back.");
    command("frown");
}

/*
 * Function name: kill
 * Description:   Don't kill him, nor anyone else.
 * Arguments:     the arg given.
 * Returns:       1 if right arg.
 */
void
attacked_by(object ob)
{
    ::attacked_by(ob);
    if (ob)
    {
	command("say Shame on you " + ob->query_name() + ".");
    	stop_fight(ob);
    	ob->stop_fight(TO);
	write("Well...Just when you thought you would hit the quest master, " +
	      "he mumbles a word and is gone. Just to appear behind you and " +
	      "give you a hard kick. OUCH!!\n");
	say(QCTNAME(ob) + " tries to attack the quest master.\n" +
	    "But the quest master mumbles a word and is right behind " + 
	    ob->query_objective() + "\n" +
	    "and gives " + ob->query_objective() + " a hard kick.\n");
	ob->move_living("down flying through the air",
			STAND_DIR + "solace/new_village/main_road5");
    }
}

/*
 * Function name: my_kick
 * Description:   React on a kick
 * Arguments:     the strings you get from trigactions
 * Returns:       1
 */
void
my_kick(object actor, string adverbs)
{
    command("glare " + actor->query_real_name());
    command("say Watch it!");
}

/*
 * Function name:
 * Description:
 * Arguments:
 * Returns:
 */
