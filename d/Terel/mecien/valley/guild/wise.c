/* Creative rights reserved to Mecien(Jeff Babcock) and team. */
/* A version of the Questmaster in Krynn 
   modified by Mecien
   Made by Nick
*/
#include <ss_types.h>
#include <language.h>
#include <stdproperties.h>
#include <macros.h>

#define PATH "/d/Terel/mecien/valley/guild/"
#define ADA add_action
#define TP this_player()
#define NF notify_fail

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

/*
 * Function name: create_monster
 * Description:   Create the monster
 */
void
create_monster()
{
    int i;

    set_name("emystir");
    set_living_name("emystir");
    set_adj("great");

    set_short("Emystir the Wise-One");
    set_long("This is a giant white owl. It seems very mysterious, its\" +
	"great eyes watching all that moves. Gray streaks run through\n" +
	"its wings, black ribs adorn its breast. Its ears dark, looking\n" +
        "anlmost like horns. Its beak sharp and strong. It looks to be a\n" +
        "ancient creature.\n");
    set_alignment(900); 
    add_name("lord");
    add_name("wise-one");

    if (IS_CLONE)
    {
        set_act_time(4);
    	add_act("stare");
    	add_act("giggle");
    	add_act("twiddle");
        trig_new("%s 'attacks' %s", "kill");
  	trig_new("%s 'bows' %s", "my_bow");
    }

    for (i = 0; i < 6; i++)
        set_base_stat(i, 90 + random(30));
        set_skill(SS_DEFENCE, 150);

    set_all_attack_unarmed(40, 53);
    set_all_hitloc_unarmed(75);

    ALWAYSKNOWN;
    add_prop(OBJ_I_NO_ATTACK, 1);

    ::create_monster();
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
    int type;

    type = check_valid_type(str);

    if (type >= 0)
    {
	if (!do_ask(type))
	    write("Emystir hoots: I have nothing on that subject\n");
	say(QCTNAME(TP) + " asks about some " + ATYPES[type] + ".\n");
	return 1;
    }

    NF("Emystir seems confused.\n");
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
	    write("Too bad there aren't any more touristing for " +
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
	if (type == QUEST)
	{
	    command("say I cannot allow that\n");
	    command("glare " + TP->query_real_name());
	    return 1;
	}
	if (do_pass(type))
	    say(QCTNAME(TP) + " seeks a different " + ATYPES[type] + ".\n");
	else
	    say(BS(QCTNAME(TP) + 
		" was given no wisdom.", 70));
	return 1;
    }

    NF("Emystir looks confused.\n");
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
	write("Emystir think you have done all he has.\n");
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
	    ob->remove_object();
    } else {
	name = QUEST_DIR + SH_ATYPES[type] + num;
        tmp = name->reward(TP);
    }

    /* The file object takes care of the reward */ 
    /* and the reward message to the player. */
    /* Even if the player didn't get any reward. */

    if (tmp == 1)
    {
	write("Emystir raises his wings over you and imbues you with power.\n");
	inc_quest_number(type, TP);
    }
    if (tmp > 0)
	return 1;
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
	sum += base * ob->test_bit("Terel", GROUP[type], E_BIT[type] - i);
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
	    num ++;
	    name->aks(TP);
	}
	if (num == 1)
	    write("Emystir has no quests of that nature.\n");
    }
    else
    {
	num = query_quest_number(type, TP) + 1;

        while (check_more_quests(type, num))
	{
	    name = QUEST_FILE(type, num);
	    num ++;
	    if (i = name->ask(TP))
		break;
	}
	if (i != 1)
	    return 0;

        while (check_more_quests(type, num))
	{
	    name = QUEST_FILE(type, num);
	    num ++;
	    if (name->ask())
	    {
		write("Emystir hoots: If you do that you can then...\n");
		name->ask(TP);
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
 	    write("Emystir summons a darkness that takes away some of\n" +
		  "your experience.\n");
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
    call_out("give_back", 1, ob);
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
    command("say I have no use for " + LANG_ADDART(ob->short()));
    command("say keep it");
    command("frown");
}

/*
 * Function name: kill
 * Description:   Don't kill him, nor anyone else.
 * Arguments:     the arg given.
 * Returns:       1 if right arg.
 */
int
kill(string str1, string str2) 
{
    object ob, poor;

    str2 = extract(str2, 0, strlen(str2) - 3);
    ob = present(lower_case(str1), environment(TO));
    poor = present(lower_case(str2), environment(TO));

    if (ob && (str2 == "you"))
    {
	command("say Shame on you " + str1 + ".");
    	stop_fight(ob);
    	ob->stop_fight(TO);
	write(BS(
	    "Well...Just when you tought you would hit the quest master, " +
	    "he mumbels a word and is gone. Just to appear behind you and " +
	    "give you a hard kick. OUCH!!",70));
        say(QCTNAME(ob) + " tries to attack the quest master.\n" +
	    "But the quest master mumbels a word and is right behind " + 
	    ob->query_objective() + "\n" +
	    "and gives " + ob->query_objective() + " a hard kick.\n");
	ob->move_living("down flying through the air", STAND_DIR +
	    "solace/village/solace14");
    	return 1;
    }
    if (poor)
	command("say Poor " + str2 + ".");
    return 1;
}

/*
 * Function name: my_kick
 * Description:   React on a kick
 * Arguments:     the strings you get from trigactions
 * Returns:       1
 */
int
my_kick(string s1, string s2, string s3)
{
    object kicker;

    if (s2 != "you.") return 1;
    s1 = lower_case(s1);
    if (kicker = present(s1,environment(this_object())))
    {
    	call_out("command", 1, "glare " + s1);
	call_out("command", 1, "say Whatch it!");
    }
    return 1;
}

/*
 * Function name: my_poke
 * Description:   React on a poke
 * Arguments:     the strings you get from trigactions
 * Returns:       1
 */
int
my_poke(string s1, string s2, string s3)
{
    if (s2 != "you") return 1;
    call_out("command", 1, "say Ohh no! Another Tricky fan.");
    return 1;
}

/*
 * Function name: my_bow
 * Description:   react on a bow
 * Arguments:     string you get from trigactions
 * Returns:       1
 */
int
my_bow(string s1, string s2)
{
    call_out("command", 1, "nod");
    return 1;
}

/*
 * Function name: my_smile
 * Description:   react on a smile
 * Arguments:     string you get from trigactions
 * Returns:       1
 */
int
my_smile(string s1, string s2)
{
  call_out("command", 1, "smile");
  return 1;
}

/*
 * Function name:
 * Description:
 * Arguments:
 * Returns:
 */
