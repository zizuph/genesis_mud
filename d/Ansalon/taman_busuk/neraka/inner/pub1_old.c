/* Ashlar, 5 Jul 97 - The Red Dragon Tavern */
/* Trading code taken from Inn in solace, coded by Nick
   modified by Ashlar */

#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>
#include <money.h>

inherit INNER_IN;
inherit "/lib/trade";
inherit "/d/Ansalon/common/cheater";

#define NUM sizeof(MONEY_TYPES) /* How many types of money do we use? */

int test; /* to indicate that a test is going on, no money given. */
object ob, barkeeper = 0;
object off,m1,m2;

/*
* Prototypes
*/
int move_item(mixed arg);

void
reset_neraka_room()
{
    if (!objectp(barkeeper))
        barkeeper = clone_npc(NNPC + "pbarkeep1");
    
    if (!objectp(off))
        off = clone_npc(NNPC + "humcaptain",({"black","red","blue"})[random(3)]);
    if (!objectp(m1))
        m1 = clone_npc(NNPC + "minotaur");
    if (!objectp(m2))
        m2 = clone_npc(NNPC + "minotaur");
}

void
create_neraka_room()
{
	config_default_trade(); 

    set_short("the Red Dragon Tavern");

    set_long("This is a tavern in the city of Neraka. Smoke from the " +
        "fireplace hangs in the air below the high ceiling. A menu " +
        "hangs in a frame on one wall, and a couple of tables with " +
        "benches for seats, are placed in the middle of the room. " +
        "Since the floor of the tavern is below the level of the " +
        "street outside, there are a few steps leading up to the front " +
        "door to the north.\n");

    add_item(({"door","front door"}),"The front door is sturdy, made of " +
        "thick oak planks. It bears the marks of several boots and not a " +
        "few weapons.\n");
    add_item(({"steps","stone steps"}),"The stone steps are worn from a " +
        "multitude of boots. They lead up to the front door.\n");
    add_item("frame","It is a simple wooden frame, and it holds the menu.\n");
    add_item_inside();
    remove_item("ceiling");
    add_item(({"ceiling","beamed ceiling"}),
        "The beamed ceiling is rather high, and covered in thick smoke.\n");
    add_item("fireplace","A fireplace is set in one corner of the room. " +
        "A fire burns in it, spreading warmth and smoke into the room.\n");
    add_item("fire","The fire burning in the fireplace gives warmth to " +
        "the room. It is crackling and sizzling.\n");
    add_item("smoke","The smoke which is thicker at the ceiling stings " +
        "your eyes a bit.\n");

    add_item(({"patrons","patron"}),"The patrons seem to be enjoying " +
        "their food and drink.\n");

    add_item(({"pricelist","menu"}),
        "It contains some words.\n");
    add_cmd_item(({"pricelist","menu"}),({"read"}),
        ({"@@read_pricelist@@"}));
    add_item(({"table","tables"}),
        "The tables are made of thick oak planks. They are none too clean.\n");
    add_item(({"bench","benches"}),"The benches are made of wooden planks. " +
        "They provide seating at the tables.\n");

    add_exit(NINNER + "r15","north","@@go_north");

    reset_room();
}

int
go_north()
{
    write("You walk up the steps and exit the tavern.\n");
    return 0;
}

string
read_pricelist()
{
    return "+-----------------------+\n" +
           "| The Red Dragon Tavern |\n" +
           "|                       |\n" +
           "| Ale             17 cc |\n" +
           "| Red wine        70 cc |\n" +
           "| Apple brandy   180 cc |\n" +
           "+-----------------------+\n";
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
    string name, str1, str2, str3;
    int *arr, price, num;

    NF("The barkeeper isn't here to answer your call.\n");
    if (!barkeeper || !P(barkeeper, TO))
	    return 0;

    NF(C(query_verb()) + " what?\n");
    if (!str)
	    return 0;

    NF("You seem unable to catch the barkeeper's attention.\n");
    if ((!CAN_SEE(barkeeper,TP)) || (!CAN_SEE_IN_ROOM(barkeeper)))
        return 0;

    if (check_cheater(TP, barkeeper))
        return 1;
        
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

    if (sscanf(str1, "%d %s", num, str1) != 2)
	num = 1;

    switch(str1)
    {
        case "ale":
        case "ales":
        case "mug":
        case "mugs":
        case "mug of ale":
        case "mugs of ale":
        	name = "drink/ale1";
        	price = num * 17;
        	break;
    	case "wine":
    	case "red wine":
    	case "wines":
    	case "red wines":
        	name = "drink/redwine";
        	price = num * 70;
    	    break;
        case "brandy":
        case "brandys":
        case "brandies":
        case "apple brandy":
        case "apple brandys":
        case "apple brandies":
    	    name = "drink/applebrandy";
    	    price = num * 180;
	        break;
        default:
            NF("The barkeeper shakes his head at you, as he cannot " +
                "understand your order.\n");
	        return 0;
    }

    if (num > 10)
    {
        barkeeper->command("say to " + TP->query_real_name() + " I ain't " +
            "carrying more than 10 items!");
        return 1;
    }
    
    if (num < 1)
        cheater_log(this_player(), this_object(), "buy 0 units");

    if (sizeof(arr = pay(price, this_player(), str2, test, 0, str3)) == 1)
    	return 0;  /* pay() handles notify_fail() call */

    write("You pay " + text(exclude_array(arr, NUM, NUM * 2 - 1)) + ".\n");
    if (text(exclude_array(arr, 0, NUM - 1)))
	    write("You get " + text(exclude_array(arr, 0, NUM - 1)) + ".\n");

    barkeeper->command("emote gets to work.");

    return move_item(({name, num, TP}));
}

int
move_item(mixed arg)
{
    object drink, ob;
    string file, name;
    int i, num;

    name = arg[0];
    num = arg[1];
    ob = arg[2];

    for (i = 0; i < 10; i++)
    {
	    num--;
    	file = NOBJ + name;
	    drink = clone_object(file);

    	if (!test && (drink->move(ob)))
	    {
	        ob->catch_msg("You drop the " + drink->short() +
	            " on the floor.\n");
    	    say(QCTNAME(ob) + " drops a " + drink->short() +
	            " on the floor.\n", ob);
	        drink->move(TO);
	    } 
	    else if (!test) 
	    {
	        if (num == 0)
	        {
		        if (arg[1] > 1)
    	    	{
	    	        ob->catch_msg("You get some " + drink->plural_short() +
        		        ".\n");
		            say(QCTNAME(ob) + " buys some " + drink->plural_short() +
		                ".\n", ob);
		        }
		        else 
		        {
		            ob->catch_msg("You get " + drink->short() + ".\n");
	                say(QCTNAME(ob) + " buys " + drink->short() + ".\n",
		                ob);
		        }
	        }
	    }
	    else 
	    {
	        say(QCTNAME(ob) + " seems to be estimating something.\n",
	            ob);
	        return 1;
	    }
	    if (num < 1)
	        break;
    }

    if (num > 0)
	    set_alarm(1.0, 0.0, &move_item(({name, num, ob})));
    return 1;
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
    if (!str || !stringp(str))
	    return 0;

    if (sscanf(str, "buy %s", str1)) 
    {
	    test = 1;
	    write("This would be the result of a buy:\n");
	    i = order(str1);
	    test = 0;
	    return i;
    }
}

