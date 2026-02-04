/*
 * A wheel of fortune. Mortricia 920930
 *
 * Updated 11/28/2018 by Shanoga
 *  - This room/wheel has been very broken for many years, maybe forever
 *  - The wheel can now be bet on properly. Core game mechanics unchanged
 *  - NPCs changed as well to make game more "life-like" to players
 *  - Prizes unchanged, but are now give to players rather than just
 *    cloning into player inventory.
 *
 * Updated Jan 2021 by Lucius
 *  - Misc cleanups
 */
inherit "/std/room";
inherit "/lib/trade";

#include <stdproperties.h>
#include <macros.h>
#include <money.h>
#include <language.h>
#include "/d/Terel/common/terel_defs.h"

#define NUM sizeof(MONEY_TYPES) /* How many types of money do we use? */
#define NF(xxx) notify_fail(xxx) /* Nice shortcut to the notify_fail() :) */

#define CAMP_DIR           MORTRICIADIR + "camp/"
#define WEP_DIR            MORTRICIADIR + "weapons/"
#define ARM_DIR            MORTRICIADIR + "armours/"
#define JOE_ANGRY          ({"grumble", "stomp", "explode", "swear", "growl"})
#define JOE_HAPPY          ({"strut", "giggle", "smile"})
#define TO                 this_object()
#define TP                 this_player()
#define NO_OF_BETS         11
#define HARD_TO_GET_BONUS  60  /* 0 -> always, 100 -> never */

int test, spinning, lucky;
object *bets;
string *to_give;
string winner;
object girl, joe;

void config_trade_data();

void clear_bets();
int check_bets();
object stop_wheel();

public void
reset_room()
{
    if (!girl)
    {
	girl = clone_object(CAMP_DIR + "girl");
	girl->move_living("M", TO);
    }
    if (!joe)
    {
	joe = clone_object(CAMP_DIR + "joe");
	joe->move_living("M", TO);
	MONEY_MAKE_SC(20)->move(joe);
    }
    spinning = 0;
    lucky = 1;
}

public void
create_room()
{
    config_default_trade();

    set_short("Wheel of Chance");
    set_long(
      "This tent locates the famous Wheel of Chance. Here you can " +
      "bet on eleven numbers and win glorious prizes. There is a " +
      "sign at the counter that you can read for more " +
      "instructions. Behind the counter there is a large wooden " +
      "wheel.\n");

    add_item("wheel", "@@my_wheel");
    add_item("bets", "@@my_bets");
    add_item("sign", "It's an ordinary sign.\n");
    add_cmd_item("sign", "read",
      "You can win:\n" +
      "    1 cc...............Sweet Candy\n" +
      "    1 sc...............Eleven silver coins\n" +
      "    1 gc...............Beautiful knife\n" +
      "    1 pc...............Excellent sword and armours\n\n" +
      "You perform a bet with\n" +
      "    'bet on x [with <type of coin>]'\n" +
      "where x is a number in the range 1-11. Copper is the\n" +
      "default <type of coin>. Check your bets with\n" +
      "    'look at bets' or 'exa bets'\n" +
      "Example:\n" +
      "    'bet on 5 with silver'\n" +
      "Also 'bet <type of coin> on x' works, and you can bet on\n" +
      "several different numbers during a round of bets.\n" +
      "Sometimes you might win an extra bonus prize if you are lucky!\n"
    );
    add_prop(ROOM_I_INSIDE, 1);

    bets = allocate(NO_OF_BETS + 1);
    to_give = allocate(NO_OF_BETS + 1);

    add_exit(CAMP_DIR + "camp_06", "north", 0);
    add_exit(CAMP_DIR + "camp_08", "west", 0);
    add_exit(CAMP_DIR + "camp_10", "south", 0);
    reset_room();
}

public string
my_wheel()
{
    string str;

    if (spinning) {
	str = "The wooden wheel is rotating.\n";
    } else {
	str = "The wooden wheel has stopped on " + LANG_WNUM(lucky) +
	".\n";
    }
    return str;
}

public string
my_bets()
{
    int i;
    string str = "";

    for (i=1; i<=NO_OF_BETS; i++)
    {
	if (bets[i] == TP) {
	    str = str + " " + LANG_WNUM(i);
	}
    }
    if (str == "") return "None of the bets are yours.\n";

    return "These are your bets:" + str + "\n";
}

/*
 * Function name: config_trade_data
 * Description:   Here we configure our own settings for the trade data
 */
void
config_trade_data()
{
    /*
      set_money_give_max("@@give_max");
      set_money_give_out(({2000, 200, 20, 2}));
      set_money_give_reduce(({0, "@@give_red_silv", 2, 1}));
      set_money_accept(({1, 1, 1, 1}));
      set_money_greed_buy(100);
      set_money_greed_sell(100);
      set_money_greed_change(100);
      set_money_values();
      set_money_types();
    */
}

/*
 * Function name: give_red_silver
 * Description:   An example of how to use a VBFC, here put in the give_reduce array.
 * Returns:       The number of silver coins to reduce, randomized
 */
int give_red_silv() { return random(4); } /* for more variations */

/*
 * Function name: give_max
 * Description:   VBFC, see how we can change settings depending on who the buyer is
 *                Easy to give a guild member a much better bargain than another
 *                player. Or maybe there will be a charm spell in the game.......
 * Returns:       The max money the pub will ever give out as change, well we will
 *                probably never exceed this limit ;-)
 */
int
give_max()
{
    return 10000;
}


/*
 * Function name: try_a_bet
 * Description:   The gambler tries to do a bet
 * Arguments:     str - defining the bet
 */
public int
try_a_bet(string str)
{
    string name, str1, str2, str3;
    int *arr, price, bet, silent, i;

    if (!str) {
	NF("Bet on what?\n");
	return 0;
    }
    if (!girl) {
	NF("You can't do that! The girl is dead!\n");
	return 0;
    }
    if (!spinning) {
	NF("New bets aren't accepted right now!\n");
	girl->command("smile");
	return 0;
    }

    /* Has the player defined how bet will be done? */  

    if (sscanf(str, "on %s with %s", str1, str2) != 2)
    {
	if (sscanf(str, "on %s", str1) != 1) {
	    if (sscanf(str, "%s on %s", str2, str1) != 2) {
		NF("I don't understand your bet.\n");
		return 0;
	    }
	} else {
	    str2 = "copper";
	}
    }
    str3 = "";

    switch (str1) {
    case "1":
    case "one":
	bet = 1;
	break;
    case "2":
    case "two":
	bet = 2;
	break;
    case "3":
    case "three":
	bet = 3;
	break;
    case "4":
    case "four":
	bet = 4;
	break;
    case "5":
    case "five":
	bet = 5;
	break;
    case "6":
    case "six":
	bet = 6;
	break;
    case "7":
    case "seven":
	bet = 7;
	break;
    case "8":
    case "eight":
	bet = 8;
	break;
    case "9":
    case "nine":
	bet = 9;
	break;
    case "10":
    case "ten":
	bet = 10;
	break;
    case "11":
    case "eleven":
	bet = 11;
	break;
    default:
	NF("I don't understand what number you want to bet on.\n");
	return 0;
    }

    if (bet < 1 || bet > NO_OF_BETS) {
	NF("I don't understand what number you want to bet on.\n");
	return 0;
    }

    switch(str2)
    {
    case "copper":        /* A copper bet */
	name = "candy";
	price = 1;
	break;
    case "silver":        /* A silver bet */
	name = "11 silver coins";
	price = 12;
	break;
    case "gold":          /* A gold bet */
	name = "knife";
	price = 144;
	break;
    case "platinum":      /* A platinum bet */
	name = "sword and armours";
	price = 144*12;
	break;
    default:
	NF("I don't understand what you want to bet with.\n");
	return 0;
    }

    /* Check here if bet is ok. */
    if (bets[bet] == TP) {
	NF("You have already a bet on that number!\n");
	return 0;
    }
    if (bets[bet] != TO) {
	NF("That number is occupied by someone else!\n");
	return 0;
    }

    silent = 0;
    str2 = "";

    if (sizeof(arr = pay(price, TP, str2, test, 0, str3, silent)) == 1)
    {
	if (arr[0] == 1)
	    NF("You have to give me more to choose from, that isn't enough.\n");
	else if(arr[0] == 2)
	    NF("You don't carry that kind of money!\n");
	return 0;  /* pay() handles notify_fail() call */
    }

    /* This is how to detect if the player dropped some of the change. */
    /* Then if you had set the silent flag in the pay command you would */
    /* then say something about it here. */
    /*
	if (arr[sizeof(arr) - 1] 
	    write("You couldn't hold all the change.\n");
    */

    write("You pay " + text(exclude_array(arr, NUM, NUM*2-1)) + ".\n");
    if (text(exclude_array(arr, 0, NUM-1)))
	write("You get " + text(exclude_array(arr, 0, NUM-1)) + ".\n");

    if (!test)
    {
	bets[bet] = TP;
	to_give[bet] = name;
	write("You bet on number " + LANG_WNUM(bet) + ".\n");
	say(QCTNAME(TP) + " places a bet on number " +
	  LANG_WNUM(bet) + ".\n");
    }
    else
    {
	write("You bet on number " + LANG_WNUM(bet) + ".\n");
    }

    set_alarm(1.0, 0.0, &girl->action_one());
    if (present(joe)) set_alarm(0.5, 0.0, &joe->place_bet());

    return 1;
}

public int
g_cmd(string str)
{
    int i, prize_value;
    object who, b_obj, p_obj;
    string prize, str1;

    if (!strlen(str))
	return 0;

    str1 = "copper";
    if (sscanf(str, "all %s", str1) == 1) {
	str = "all";
    }

    if (str == "all")
    {
	if ("/secure/master"->query_wiz_dom(TP->query_real_name()) == "Terel") {
	    for (i=1; i<=NO_OF_BETS; i++) {
		try_a_bet("on " + i + " with " + str1);
	    }
	    return 1;
	}
	return 0;
    }

    if (TP != girl)
	return 0;

    if (str == "clear")
    {
	clear_bets();
	return 1;
    }

    if (str == "stop")
    {
	who = stop_wheel();
	if (!who || who == TO || who == girl) {
	    girl->command("say No winner!");
	    if (joe && present(joe, TO))
	    {
		joe->command(JOE_ANGRY[random(sizeof(JOE_ANGRY))]);
		set_alarm(2.0, 0.0, &joe->enable_betting(0));
	    }
	    return 1;
	}
	say("The winner is " + QTNAME(who) + "!\n");
	prize = to_give[lucky];
	say(capitalize(who->query_pronoun()) + " wins: " +
	  prize + "\n");
	if (!present(who, TO)) {
	    say("The winner is not here! What a waste!\n");
	    return 1;
	}

	if (joe && present(joe, TO))
        {
	    if (who != joe)
	    {
		joe->command(JOE_ANGRY[random(sizeof(JOE_ANGRY))]);
		set_alarm(2.0, 0.0, &joe->enable_betting(0));
	    }
	    else
	    {
		joe->command(JOE_HAPPY[random(sizeof(JOE_HAPPY))]);
		set_alarm(2.0, 0.0, &joe->enable_betting(1));
	    }
	}

	if (prize == "candy")
        {
	    p_obj = clone_object(CAMP_DIR + "candy");
	    p_obj->move(girl);
	    girl->command("emote reaches into a bag of candy behind the " +
	      "counter and grabs some candy.");
	    girl->command("give candy to " + who->query_name());
	    prize_value = 0;
	}
	if (prize == "11 silver coins")
        {
	    p_obj = MONEY_MAKE_SC(11);
	    p_obj->move(girl);
	    girl->command("emote reaches into the moneybag behind the " +
	      "counter and pulls out some coins.");
	    girl->command("give 11 silver coins to " + who->query_name());
	    prize_value = 6;            
	}
	if (prize == "knife")
        {
	    p_obj = clone_object(WEP_DIR + "p_knife");
	    p_obj->move(girl);
	    girl->command("emote reaches up to a shelf behind the " +
	      "counter and gets a knife.");
	    girl->command("give knife to " + who->query_name());
	    prize_value = 72;
	}
	if (prize == "sword and armours")
        {
	    p_obj = clone_object(WEP_DIR + "p_sword");
	    p_obj->move(girl);
	    p_obj = clone_object(ARM_DIR + "p_helmet");
	    p_obj->move(girl);
	    p_obj = clone_object(ARM_DIR + "p_shield");
	    p_obj->move(girl);
	    p_obj = clone_object(ARM_DIR + "p_mail");
	    p_obj->move(girl);
	    girl->command("emote reaches up to a shelf behind the " +
	      "counter and grabs some armours.");
	    girl->command("give sword to " + who->query_name());
	    girl->command("give armours to " + who->query_name());
	    prize_value = 864;
	}
	if (random(100) + 1 >= HARD_TO_GET_BONUS)
	{
	    b_obj = clone_object(CAMP_DIR + "b_ring");
	    b_obj->inscript("This ring works as a permit in " +
	      "the gypsy camp.\n  Show it to the " +
	      "guards. It's personal.");
	    b_obj->add_prop("_gypsy_permit", who->query_name());
	    b_obj->add_prop(OBJ_I_VALUE, prize_value);
	    b_obj->move(girl);
	    girl->command("say " + capitalize(who->query_pronoun()) +
	      " also wins the secret bonus prize!\n");
	    girl->command("emote reaches up to a lockbox behind the " +
	      "counter and grabs the prize.");
	    girl->command("give ring to " + who->query_name());
	}
	return 1;
    }
    return 0;
}

/*
 * Function name: test
 * Description:   To allow the gambler to see what would happen with change and
 *                payment depending on how the gambler chooses to pay.
 * Arguments:     str -  bet on x [with y]  (default: y="copper")
 */
public int
test_cmd(string str)
{
    int i;
    string str1;

    NF("Test what?\n");
    if (!strlen(str))
	return 0;

    if (sscanf(str, "bet %s", str1))
    {
	test = 1;
	write("This would be the result of a bet:\n");
	i = try_a_bet(str1);
	test = 0;
	return i;
    }
    else
    {
	return 0;
    }
}

/*
 * Function name: init
 * Description:   Initalize the wheel actions
 */
public void
init()
{
    ::init(); /* Since it's a room this must be done. */
    add_action(try_a_bet, "bet");
    add_action(test_cmd, "test");
    add_action(g_cmd, "g_cmd");
}

void
clear_bets()
{
    int i;

    if (girl)
	girl->command("shout Betting is now open!");
    if (joe)
	joe->enable_betting();
    for (i=0; i<=NO_OF_BETS; i++) {
	bets[i] = TO;
    }
    spinning = 1;
}

int
check_bets()
{
    int ii, jj;

    jj=0;

    for (ii=1; ii<=NO_OF_BETS; ii++) {
	if (bets[ii] != TO) {
	    jj++;
	}
    }
    return jj;
}

object
stop_wheel()
{
    int i, ii, jj;
    string str;
    object winner = TO;

    if (!girl)
        return winner;

    if (check_bets() == 0)
        return winner;

    for (ii=1; ii<=NO_OF_BETS; ii++) {
	if (bets[ii] == TO) {
	    bets[ii] = girl;
	}
    }
    girl->command("say No more bets taken!");

    say("The wheel slows down...\n");

    spinning = 0;
    girl->game_finished();

    lucky = random(NO_OF_BETS) + 1;
    for (ii=lucky - NO_OF_BETS + 1; ii<=lucky; ii++) {
	if (ii < 1) {
	    jj = NO_OF_BETS + ii;
	} else {
	    jj=ii;
	}
	say("" + jj + " ");
    }

    say("\n  ...and stops on " + LANG_WNUM(lucky) + "!\n");

    winner = bets[lucky];

    return winner;
}
