inherit "/std/room";
inherit "/lib/trade";

#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/sys/money.h"

#define TP this_player()
#define NUM sizeof(MONEY_TYPES) /* How many types of money do we use? */
#define NF(xxx) notify_fail(xxx) /* Nice shortcut to the notify_fail() :) */

int test; /* to indicate that a test is going on, no money given. */

/*
 * Prototypes
 */
object drunk;
object make_drink(string name, string adj, string long, int weight,
		  int volume, int soft, int alco);
void config_trade_data();
		  
/*
 * Function name: create_room
 * Description:   Set up default trade and cofigure it if wanted.
 */
reset_room(arg){
if(drunk) return 0;
drunk=clone_object("/d/Terel/mecien/valley/city/drunk");
drunk->move(this_object());
}

void
create_room()
{
    config_default_trade();
    set_short("The Raven Roost");
    set_long(break_string(
	     "This is a small tavern, it is lined with rows on " +
	     "fine pine benches and tables. Black lanterns hang from "  + 
	     "the rafters, providing a small light for this place. " +
	     "Up in these rafters are countless statuettes of many " +
	     "different kinds of birds, but most prominant are those "+
	     "of the raven. Tapestries of rich cloth line the walls, on " +
	     "which are depicted crests and emblems of noble families. " +
	     "A large counter is at the west side of the room, it is the " +
	     "bar, over which hangs a menu. Next to the menu is a plaque " +
	     "on which is inscribed a mystic ward. There is a large chair " +
	     "sitting next to the fireplace on the south wall.\n", 70));
    

   add_item("chair", "It is a large ebony chair.\n");
   add_item("benches", "They are made of fine pine.\n");
   add_item("table", "They are long and wide, fashioned of pine.\n");
  add_item("lanterns", "They are black metal, burning bright from the rafters.\n");
   add_item("statuettes", "They are of numerous birds.\n");
   add_item("tapestries", "They bear the crests, devices and emblems\n"
    + "of many nobles and mighty heroes.\n"
   );
  add_item(({"bar", "counter"}), "It is where the drinks are made and\n"
   + "served. Carved of white pine, it is very beautiful.\n");
   add_item("plaque", "It is inscribed with a mystical ward, that being\n"
   + "a silver star circled by emerald serpents.\n");
    /*
	config_trade_data();
    */
    add_exit("/d/Terel/mecien/valley/city/street3", "east", 0);

    add_item("menu", "We have the following to please you:\n\n" +
                     "ale      10cc\n" +
                     "wine     65cc\n" +
                     "brandy   70cc\n" +
                     "liquor  250cc\n");

   add_cmd_item("menu", "read", "WE have the following to please you:\n" +
                     "ale      10cc\n" +
                     "wine     65cc\n" +
                     "brandy   70cc\n" +
                     "liquor  250cc\n");
    add_prop(ROOM_I_INSIDE,1);  /* This is a real room */

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
    if (this_player()->query_real_name() == "mecien") {
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

    if (!str) {
	NF("buy what?\n");
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
    case "wine":
	/* Stout, alco is 7% */
	name = "wine";
	adj = "red";
	long = "A refreshing and fragrant, sweet red wine.\n";
	weight = 540;
	volume = 540;
	soft = 540;
	alco = 38;
	price = 65;
	break;
    case "ale":
	/* Beer, alco is 4% */
	name = "ale";
	adj = "light";
	long = "A very light beer.\n";
	weight = 100;
	volume = 100;
	soft = 100;
	alco = 4;
	price = 10;
	break;
    case "brandy":
	/* Special, alco is 40% */
	name = "brandy";
	adj = "sweet";
	long = "It is a sweet brandy.\n";
	weight = 62;
	volume = 62;
	soft = 62;
	alco = 25;
	price = 70;
	break;
    case "liquor":
	/* Vodka, alco is 60%, now that leaves 80% and 96% ;-/ */
	name = "liquor";
	adj = "cherry";
	long = "A strange and powerful cherry liquor.\n";
	weight = 84;
	volume = 84;
	soft = 84;
	alco = 70;
	price = 250;
	break;
    default:
	NF("I don't understand what you want to buy.\n");
	return 0;
    }
  
  if(present("protector_ring", TP)) price = price/2;
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
    drink->set_short();
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
