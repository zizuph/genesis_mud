/*
 * /d/Gondor/minas/rooms/wtpub.c
 * 
 * The White Tree Pub of Minas Tirith - modified by Elessar,
 * coded by Nick.
 *
 * 17 June 1998, Gnadnar: inherit ~gondor/std/room, cleanup.
 *
 * 26 March 2007, Toby: Fixed short desc in drinks and typo in buying.
 */

#pragma strict_types

inherit "/d/Gondor/std/room";
inherit "/lib/trade";

#include <stdproperties.h>
#include <macros.h>
#include <money.h>

#include "/d/Gondor/defs.h"

#define NUM sizeof(MONEY_TYPES) /* How many types of money do we use? */

object	Drunk;

/* Prototypes */
public void	create_gondor();
public void	reset_room();
public void	init();
public int	order(string str);
public object	make_drink(string name, string adj, string long, int weight,
		  int volume, int soft, int alco);
public mixed	read_menu(string str);


/*
 * Function name:	create_gondor
 * Description	:	Set up the pub
 */
public void
create_gondor()
{
    config_default_trade();
    set_short("The White Tree Pub");
    set_long(BSN(
	"The White Tree Pub is where Gondorians gather in the "+
	"evenings, exchanging news and stories over a glass of "+
	"ale or some cool wine. There's a menu hanging on the wall "+
	"behind the counter."));
    
    add_item( ({ "pricelist", "menu", }), &read_menu("menu"));
    add_item( ({ "wooden planks", "planks", "floor", }),
	   "The wooden planks are swept clean.\n");
    add_item( ({ "plaster", "ceiling", "wall", "walls", }),
	   "Walls and ceiling are a creamy plaster that appears "+
	    "to have been painted recently.\n");
    add_item( ({ "work area", "bar", "counter" }),
	   "The chest-high counter separates the work area "+
	    "from the rest of the pub.\n");
	
    
    add_exit("/d/Gondor/minas/s2crc3", "north", 0);
    add_prop(ROOM_I_INSIDE,1);

    reset_room();
} /* create_gondor */


/*
 * Function name:	reset_room
 * Description	:	restore the drunk 
 */
public void
reset_room()
{
    Drunk = clone_npc(Drunk, MINAS_DIR+"npc/drunk");
} /* reset_room */

/*
 * Function name:	init
 * Description	:	Initalize the pub actions
 */
public void
init()
{
    ::init();
    add_action(order,		"buy");
    add_action(order,		"order");
    add_action(read_menu,	"read");
} /* init */


/*
 * Function name:	order
 * Description	:	The buyer orders a drink
 * Arguments	:	string str - whatever the player typed.
 *			presumably, it's the name of drink and possibly
 *			description on how to pay and get the change
 */
public int
order(string str)
{
    object	drinkob,
		tp = TP;
    string	name, adj, long, drink, paystr, changestr;
    int		*arr, price, alco, weight, volume, soft, silent, i;

    if (!str)
    {
	NF0("The bartender says: What do you wanna order?\n");
    }

    /*
     * Has the player defined how payment will be done and drink
     * change to get back?
     */  
    if (sscanf(str, "%s for %s and get %s", drink, paystr, changestr) != 3)
    {
	/* Well, maybe player has defined how payment will be done? */
	changestr = "";
        if (sscanf(str, "%s for %s", drink, paystr) != 2)
	{
	    paystr = "";
	    drink = str;
	}
    }

    switch(drink)
    {
    case "ale":
	/* Stout, alco is 7% */
	name = "ale";
	adj = "White Tree";
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
	adj = "Dorwinion";
	long = "It's a cool wine from Dorwinion, the region far "+
		"east of Mirkwood.\n";
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
	long = "It's a strong, dark brew from Bree, a village east of "+
		"the Shire.\n";
	weight = 62;
	volume = 62;
	soft = 62;
	alco = 25;
	price = 75;
	break;
    case "spirit":
	/* Vodka, alco is 60%, now that leaves 80% and 96% ;-/ */
	name = "spirit";
	adj = "Gondorian";
	long = "It looks hot and strong indeed.\n";
	weight = 84;
	volume = 84;
	soft = 84;
	alco = 50;
	price = 250;
	break;
    default:
	NF0("The bartender says: I don't understand what you "+
	    "want to buy.\n");
    } /* switch drink */
  
    drinkob = make_drink(name, adj, long, weight, volume, soft, alco);
    /* No drink messege  */
    if (!drinkob)
    {
	log_file("wtpub", ctime(time())+"failed to create drink "+name+"\n");
	NFN0("The bartender says: Oh! I'm cursed -- I can't seem to "+
	   "make that drink! Please tell a wizard.");
    }

    silent = 0;
    arr = pay(price, tp, paystr, 0, 0, changestr, silent);

    if (sizeof(arr) == 1)
    {
	if (arr[0] == 1)
	{
	    notify_fail("You have to give me more to choose from, "+
		"that isn't enough.\n");
	}
        else if(arr[0] == 2)
	{
	    notify_fail("You don't carry that kind of money!!!\n");
	}
	return 0;  /* pay() handles notify_fail() call */
    }


    WRITE("You give the barkeeper "+
	text(exclude_array(arr, NUM, NUM*2-1))+". ");
    if (text(exclude_array(arr, 0, NUM-1)))
    {
	WRITE("You get "+text(exclude_array(arr, 0, NUM-1))+". ");
    }
    
    if ((drinkob->move(tp)))
    {
	write("You drop the "+name+" on the floor.\n");
	say(QCTNAME(tp)+" drops a "+name+" on the floor.\n");
	drinkob->move(TO);
    }
    else
    {
	write("You get your "+name+".\n");
	say(QCTNAME(tp)+" buys a "+name+".\n");
    }
    return 1;
} /* order */


/*
 * Function name:	make_drink
 * Description	:	Set up the drink
 * Arguments	:	string name -- its name
 *			string adj -- adjective
 *			string long -- description
 *			int weight -- how much it weigs
 *			int volume -- volume occupied
 *			int soft -- soft amount
 *			int alco -- alcohol amount
 */
public object
make_drink(string name, string adj, string long, int weight,
	   int volume, int soft, int alco)
{
    object drink;
    
    drink = clone_object("/std/drink");

    /* get rid of the short already set by /std/drink. */
    drink->set_short(lower_case(adj + " " + name));

    drink->set_name(name);
    if (strlen(adj))
    {
	drink->set_adj(adj);
    }
    drink->set_long(long);
    drink->set_soft_amount(soft);
    drink->set_alco_amount(alco);
    drink->add_prop(OBJ_I_WEIGHT, weight);
    drink->add_prop(OBJ_I_VOLUME, volume);

    return drink;
} /* make_drink */


/*
 * Function name:	read_menu
 * Description	:	VBFC for item + response to "read"
 * Arguments	:	string str -- whatever the player typed
 * Returns	:	string "" if this were called via exa the item
 *			int 1 if called successfully via "read"
 *			int 0 if called unsuccessfully via "read"
 */
public mixed
read_menu(string str)
{
    if (str != "menu" &&
        str != "pricelist")
    {
	NF0("Read what?\n");
    }
    write("White Tree Pub - Menu\n\n"+
      "  White Tree Ale         (brewed in the cellar) - 14 cc.\n"+
      "  Wine from Dorwinion          (special-import) - 25 cc.\n"+
      "  Strong brew from Bree  (brought in last week) - 75 cc.\n"+
      "  Gondorian Spirit (a recipe from the old days) - 250 cc\n\n");
    if (QVB != "read")
    {
	return "";
    }
    return 1;
} /* read_menu */
