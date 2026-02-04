/* This is how a simple pub could look like useing the trade object
   I have written.

   Made by Nick

   Copied from /doc/examples/trade/pub.c by Vader, and adpated
   for use in the Terel domain.  Modified on 6/27/92
   This version was then copied by Mortricia for use in the gypsy camp
*/

inherit "/std/room";
inherit "/lib/trade";

#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/sys/money.h"
#include "/d/Terel/common/terel_defs.h"

#define NUM sizeof(MONEY_TYPES) /* How many types of money do we use? */
#define NF(xxx) notify_fail(xxx) /* Nice shortcut to the notify_fail() :) */

#define CAMP_DIR     MORTRICIADIR + "camp/"
#define TO           this_object()
#define TP           this_player()
#define BSN(mess)    break_string(mess + "\n", 70)

int test;
object barkeep, drunk;

object make_drink(string name, string adj, string long, int weight,
		  int volume, int soft, int alco);
void config_trade_data();

void
reset_room()
{
    if (!barkeep) {
        barkeep = clone_object(CAMP_DIR + "bartender");
        barkeep -> move(TO);
    }
    if (!drunk) {
       drunk = clone_object(CAMP_DIR + "drunk");
       drunk -> move(TO);
    }
}

void
create_room()
{
    config_default_trade();

    set_short("Tent pub");
    set_long(BSN(
       "This is the pub of the gypsy camp. The tent which houses " +
       "this pub is worn, but that shouldn't affect the stuff " +
       "they serve people here, although the stuff will certainly " +
       "affect you. Some tables have been put here but most of " +
       "the people seem to gather around the bar counter. " +
       "There is a menu on the wall behind the counter. " +
       "To the north is another part of this tent where they " +
       "appear to be serving food."
    ));

    add_item(({"table", "tables"}), BSN(
       "These tables have seen alot of use over the years. " +
       "They are of a kind that makes them easily transportable."
    ));

    add_item(({"chair", "chairs"}), BSN(
       "These chairs have seen alot of use over the years. " +
       "They are of a kind that makes them easily transportable."
    ));

    add_item(({"counter"}), BSN(
       "The wooden counter bear the marks of many bottles and " +
       "glasses."
    ));

    add_item(({"people"}), BSN(
       "They are of all kinds: dwarves, humans etc. But what they " +
       "have in common is that they are all drunk."
    ));

    add_item("menu", "You can read it, unless you're too drunk of course.\n");
    add_cmd_item("menu", "read",
       "   A Silver Beer             12 cc\n" +
       "   A Gypsy Grog              70 cc\n" +
       "   A Green Whiskey           260 cc\n" +
     "Try 'buy whiskey', or if you wish to specify what\n" +
     "coins to use, type 'buy whiskey with silver'.  If you\n" +
     "want to see the result of buying something with certain\n" +
     "coins, type 'test buy <name> with <coin>'.\n");
    
   add_prop(ROOM_I_INSIDE, 1);
/*
	config_trade_data();
 */
   add_exit(CAMP_DIR + "camp_03", "east", 0);
   add_exit(CAMP_DIR + "tent_inn", "north", 0);

   reset_room();
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
     if (lower_case(TP -> query_real_name()) == "mortricia") {
	write("Ah, you can buy for much more than the others.\n");
	return 20000;
    }
    return 10000;
}


/*
 * Function name: init
 * Description:   Initalize the pub actions
 */
void
init()
{
    ::init(); /* Since it's a room this must be done. */
    add_action("order", "buy");
    add_action("order", "order");
    add_action("test", "test");
}

/*
 * Function name: order
 * Description:   The buyer orders a drink
 * Arguments:     str - name of drink an possibly description on how to pay and
 *                      get the change
 */
int
order(string str)
{
    object drink;
    string name, adj, long, str1, str2, str3;
    int *arr, price, alco, weight, volume, soft, silent, i;
    
    if(!barkeep) {
       NF("You can't do that!  The bartender is dead!\n");
       return 0;
      }

    if (!str) {
	NF("Buy what?\n");
	return 0;
    }

    /* Has the player defined how payment will be done and what change to get back? */  
    if (sscanf(str, "%s with %s and get %s", str1, str2, str3) != 3)
    {
    /* Well, maybe player has defined how payment will be done atleast? */
	str3 = "";
        if (sscanf(str, "%s with %s", str1, str2) != 2)
	{
	    str2 = "";
	    str1 = str;
	}
    }

    switch(str1)
    {
    case "beer":        /* Beer, alco is 4% */
	name = "beer";
        adj = "silver";
        long = "It's a small beer, oddly, silver in colour.\n";
	weight = 100;
	volume = 100;
	soft = 100;
	alco = 4;
	price = 12;
	break;
   case "grog":      /* Grog, alco is 25% */
        name = "grog";
        adj = "gypsy";
        long = "A special grog popular among the gypsies.\n";
	weight = 62;
	volume = 62;
	soft = 62;
	alco = 25;
        price = 70;
	break;
   case "whiskey":      /* Whiskey alco is 60% */
        name = "whiskey";
        adj = "green";
        long = "It's the whiskey that is sold in Big Rock Pub in Calathin. \n" +
	       "But the gypsies found a couple of barrels lying on the road.\n";
	weight = 84;
	volume = 84;
	soft = 84;
	alco = 50;
        price = 260;
	break;
    default:
	NF("I don't understand what you want to buy.\n");
	return 0;
    }
  
    drink = make_drink(name, adj, long, weight, volume, soft, alco);
    /* No drink messege  */
    if (!drink)
    {
	NF("Error in creating drink.\n");
	return 0;
    }

    silent = 0;
    
    if (sizeof(arr = pay(price, this_player(), str2, test, 0, str3, silent)) == 1)
    {
	if (arr[0] == 1)
	    NF("You have to give me more to choose from, that isn't enough.\n");
        else if(arr[0] == 2)
	    NF("You don't carry that kind of money!!!!!!!!!\n");
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
    
    if (!test && (drink->move(this_player())))
    {
	write("You drop the " + name + " on the floor.\n");
	say(QCTNAME(this_player()) + " drops one " + name + " on the floor.\n");
	drink->move(this_object());
    }
    else
	if (!test)
	{
	    write("You get your " + name + ".\n");
	    say(QCTNAME(this_player()) + " buys a " + name + ".\n");
	}
    else
	say(break_string(QCTNAME(this_player()) + " seems to be estimating something.\n",78));

    return 1;
}

/*
 * Function name: make_drink
 * Description:   Set up the drinks
 * Arguments:     A lot of drink data to be set
 */
object
make_drink(string name, string adj, string long, int weight,
	   int volume, int soft, int alco)
{
    object drink;
    
    drink = clone_object("/std/drink");

    /* Some silly functions you have to call inorder to get rid of the name
	and short, already set by /std/drink. Hope this will change. */
    drink->set_short(adj + " " + name);
    /* There now we can do what weve come for. */

    drink->set_name(name);

    if (strlen(adj)>0)
	drink->set_adj(adj);

    drink->set_long(long);
    drink->set_soft_amount(soft);
    drink->set_alco_amount(alco);
    drink->add_prop(OBJ_I_WEIGHT, weight);
    drink->add_prop(OBJ_I_VOLUME, volume);

    return drink;
}

/*
 * Function name: test
 * Description:   To allow the buyer to see what would happen with change and
 *                payment depending on how the buyer chooses to pay.
 * Arguments:     str - name of drink an possibly description on how to pay and
 *                      get the change
 */
int
test(string str)
{
    int i;
    string str1;
    
    NF("Test what?\n");
    
    if (sscanf(str, "buy %s", str1)) {
	test = 1;
	write("This would be the result of a buy:\n");
	i = order(str1);
	test = 0;
	return i;
    }
}
