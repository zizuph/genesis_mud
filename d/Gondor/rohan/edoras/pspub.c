/* The Proud Stag Pub of Edoras - modified by Elessar,
   coded by Nick.
*/

inherit "/d/Gondor/common/room";
inherit "/lib/trade";

#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/sys/money.h"

#define NUM sizeof(MONEY_TYPES) /* How many types of money do we use? */
#define NF(xxx) notify_fail(xxx) /* Nice shortcut to the notify_fail() :) */

int test; /* to indicate that a test is going on, no money given. */
object drunk;

/*
 * Prototypes
 */
object make_drink(string name, string adj, string long, int weight,
		  int volume, int soft, int alco);
void config_trade_data();
		  
/*
 * Function name: create_room
 * Description:   Set up default trade and cofigure it if wanted.
 */
void
create_room()
{
    config_default_trade();
    set_short("The Proud Stag Pub");
    set_long(break_string(
	     "You are in the Proud Stag Pub in Edoras. Here the "+
             "Rohirrims gather in the evenings, exchanging news and " +
	     "stories over a glass of beer or some cool wine. "+
      "A blond-haired and blue-eyed bartender stands behind the "+
      "counter, washing glasses and eyeing his customers. "+
	     "There's a menu hanging on the wall behind the counter. "+
	     "The exit out to the street is west.\n",75));
    
    /*
	config_trade_data();
    */
    add_item("menu","Proud Stag Pub - Menu\n\n"+
    "  Proud Stag Beer        (brewed in the cellar) - 14 cc.\n"+
    "  Wine from Ithilien           (special-import) - 25 cc.\n"+
    "  Strong brew from Bree  (brought in last week) - 75 cc.\n"+
    "  Eorlinga Spirit  (a recipe from the old days) - 250 cc\n\n");
    add_item("bartender","He has long, blonde hair and blue eyes, like a true man of Rohan.\n");
    
    add_exit("/d/Gondor/rohan/edoras/stairs1","west",0);
    add_prop(ROOM_I_INSIDE,1);  /* This is a real room */
    drunk = clone_object("/d/Gondor/rohan/edoras/npc/drunk2");
    drunk->move(this_object());
}

do_read(string str)
{
  if(!str) return 0;
  if(str != "menu") return 0;
  write("Proud Stag Pub - Menu\n\n"+
    "  Proud Stag Beer        (brewed in the cellar) - 14 cc.\n"+
    "  Wine from Ithilien           (special-import) - 25 cc.\n"+
    "  Strong brew from Bree  (brought in last week) - 75 cc.\n"+
    "  Eorlinga Spirit  (a recipe from the old days) - 250 cc\n\n");
  return 1;
}

add_drunk() {
  if (drunk) return 1;
  drunk = clone_object("/d/Gondor/rohan/edoras/npc/drunk2");
  drunk->move(this_object());
  return 1;
}

reset_room() {
  add_drunk();
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
    if (this_player()->query_real_name() == "elessar") {
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
    add_action("do_read", "read");
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

    if (!str) {
	NF("The bartender says: What do you wanna order?\n");
	return 0;
    }

    /* Has the player defined how payment will be done and what change to get back? */  
    if (sscanf(str, "%s for %s and get %s", str1, str2, str3) != 3)
    {
    /* Well, maybe player has defined how payment will be done atleast? */
	str3 = "";
        if (sscanf(str, "%s for %s", str1, str2) != 2)
	{
	    str2 = "";
	    str1 = str;
	}
    }

    switch(str1)
    {
    case "beer":
	/* Stout, alco is 7% */
	name = "beer";
	adj = "Proud Stag";
	long = "It's very dark but smells like a sweet beer.\n";
	weight = 340;
	volume = 320;
	soft = 320;
	alco = 2;
	price = 14;
	break;
    case "wine":
	/* Beer, alco is 4% */
	name = "wine";
	adj = "Ithilien";
	long = "It's a cool wine from Dorwinion, the region far east of Mirkwood.\n";
	weight = 100;
	volume = 100;
	soft = 100;
	alco = 10;
	price = 25;
	break;
    case "brew":
	/* Special, alco is 40% */
	name = "brew";
	adj = "strong";
	long = "It's a strong, dark brew from Bree, a village east of the Shire.\n";
	weight = 62;
	volume = 62;
	soft = 62;
	alco = 25;
	price = 75;
	break;
    case "spirit":
    case "eorlinga spirit":
	/* Vodka, alco is 60%, now that leaves 80% and 96% ;-/ */
	name = "spirit";
	adj = "Eorlinga";
	long = "It looks hot and strong indeed.\n";
	weight = 84;
	volume = 84;
	soft = 84;
	alco = 50;
	price = 250;
	break;
    default:
	NF("The bartender says: I don't understand what you want to buy.\n");
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
	write("The bartender drops some of your change on the floor,\n"+
        "as you couldn't carry more.\n");
*/

    write("You give the barkeeper " + text(exclude_array(arr, NUM, NUM*2-1)) + ".\n");
    if (text(exclude_array(arr, 0, NUM-1)))
	write("You get " + text(exclude_array(arr, 0, NUM-1)) + ".\n");
    
    if (!test && (drink->move(this_player())))
    {
	write("You drop the " + name + " on the floor.\n");
	say(QCTNAME(this_player()) + " drops a " + name + " on the floor.\n");
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
    drink->set_short();
    /* There now we can do what weve come for. */

    drink->set_name(name);

    if (strlen(adj)>0)
	drink->set_adj(adj);

    drink->set_long(long);
    drink->set_short(adj + " " + name);
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
