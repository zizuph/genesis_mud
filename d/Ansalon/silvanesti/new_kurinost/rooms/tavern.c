/*
 * tavern.c
 *
 */
#pragma strict_types

// I N C L U D E D   F I L E S
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/common/clock/clock.h"
#include "local.h"
#include <money.h>

inherit INSIDEBASE;
inherit "/lib/trade";
inherit "/d/Ansalon/common/cheater";

#define NUM sizeof(MONEY_TYPES) /* How many types of money do we use? */
#define DRAC  "/d/Krynn/std/sivak"
#define DRAC2  "/d/Krynn/std/aurak"

int move_item(mixed arg);
int test; /* to indicate that a test is going on, no money given. */
object ob, tyberus, drac1, drac2, drac3;
public void setup_tells();
public string show_light();

// P U B L I C   F U N C T I O N S
/*
 *  FUNCTION : reset_kurinost_room
 *  Arguments: none
 *  Returns  : void
 * 
 *  Reset the room.
 *
 */
public void
reset_kurinost_room()
{
     if (!objectp(drac1)) 
     {
         drac1 = clone_object(DRAC);
         drac1->set_color("green");
         drac1->move(TO, 1);
     }

     if (!objectp(drac2)) 
     {
         drac2 = clone_object(DRAC);
         drac2->set_color("green");
         drac2->move(TO, 1);
     }

     if (!objectp(drac3)) 
     { 
         drac3 = clone_object(DRAC2);
         drac3->set_color("green");
         drac3->move(TO, 1);
     }

    if(!objectp(tyberus))
    {
        tyberus = clone_object(RSLIVING + "tyberus");
        tyberus->sit_down();
        tyberus->move(TO, 1);
    }

    if(objectp(tyberus) && (!tyberus->query_attack()))
        tyberus->sit_down();
}


/*
 *  FUNCTION : create_kurinost_room
 *  Arguments: none
 *  Returns  : void
 * 
 *  Create the room.
 *
 */
public void
create_kurinost_room()
{
    config_default_trade();

    set_short("a dimly lit tavern");
    set_long("In stand within a dimly lit tavern. It has clearly been assembled " +
        "quickly with minimal effort, its crude workmanship allowing " +show_light()+
        " through the many crooked fittings in the walls and ceiling. Spartanly " +
        "furnished, the main feature of the tavern is a long wooden bar with many " +
        "barrels of grog piled up behind it. A pricelist sits on the bar that you " +
        "could read.\n");

    add_item(({ "tavern", "dimly lit tavern" }), 
        "You stand within a dimly lit tavern, used by the forces of the Green " +
        "Dragonarmy when off duty.\n");
    add_item(({"walls","wall","ceiling","fittings","crooked fittings","gaps"}),
        "The walls have been crudely fitted, with many gaps letting light and wind " +
        "through... ironically providing most of the light for this tavern through " +
        "them. The ceiling is little better, and looks like it would need regular " +
        "patching after seasonal storms blow through.\n");
    add_item(({"long wooden bar","wooden bar","bar"}),
        "A long wooden bar runs along the back of the tavern, unadorned apart from " +
        "a pricelist sitting in the middle of it.\n");
    add_item(({"pricelist","menu"}),
        "@@read_pricelist");
    add_item(({"barkeeper", "barman"}) ,"A non-descript rugged human serves silently " +
        "behind the bar here.\n");
    add_item(({"barrels","barrel","grog","barrels of grog"}),
        "Taking up around a third of the tavern floor space are barrels of grog.\n");

    add_exit(RSROOMS + "dcamp6x3", "out", "@@leave_tavern");

    add_cmd_item("pricelist", "read", "@@read_pricelist");

    setuid();
    seteuid(getuid());

    setup_tells();
    KURINOSTMAP;

    reset_kurinost_room();
}

string
read_pricelist()
{
    return "          PRICELIST:\n\n" +
           "          Small beer - 1 silver coin\n" +
           "          Imported brew - 2 silver coins\n" +
           "          Wine - 6 silver coins\n" +
           "          Dwarven spirits - 1 gold and 7 silver coins\n\n" +
           "          No tabs or IOUs honoured! No coin, no drink!\n\n";
}

/*
 *  FUNCTION : show_light
 *  Arguments:
 *  Returns  :
 * 
 *  Returns a string with the light that enters the tower.
 *
 */
public string
show_light()
{
    switch (GET_TIMEOFDAY)
    {
    case TOD_NIGHT:
        return "pale moonlight";

    case TOD_DAWN:
        return "faint sunlight";

    case TOD_DAY:
        return "glittering sunlight";

    case TOD_TWILIGHT:
        return "fading sunlight";
    }
}


/*
 *  FUNCTION : setup_tells
 *  Arguments: none
 *  Returns  : void
 * 
 *  Sets the basic tells of the rocky shores of Silvanesti.
 *
 */
public void
setup_tells()
{
    set_tell_time(400);

    add_tell("Pale light from the entrance sends shadows dancing around " +
        "the tavern.\n");

    add_tell("A distant scream from the camp outside carries " +
        "through the walls of the tavern.\n");

    add_tell("A gentle breeze blows through the cracks in the walls, " +
        "carrying the stench of decay and smoke into the tavern.\n");

    add_tell("The barkeeper silently runs a dirty rag over the long wooden bar.\n");
}

public int
leave_tavern()
{
    write("You push your way through the rickety door out of the tavern.\n");
    return 0;
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

    NF("buy what?\n");
    if (!str)
	return 0;

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
    case "beer":
    case "beers":
    case "small":
    case "small beer":
	name = "beer";
	price = num * 12;
	break;
    case "brew":
    case "brews":
    case "imported":
    case "imported brew":
	name = "beer1";
	price = num * 24;
	break;
    case "wine":
    case "wines":
    case "sweet":
    case "sweet wine":
	name = "wine";
	price = num * 72;
	break;
    case "spirit":
    case "spirits":
    case "dwarven":
    case "dwarven spirit":
	name = "d_spirit";
	price = num * 228;
	break;
    default:
	NF("I don't understand what you want to buy.\n");
	return 0;
    } 
    if (num > 10)
    {
	NF("The barkeeper says: I aint carrying more than 10 items!\n");
	return 0;
    }
    if (num < 1)
        cheater_log(this_player(), this_object(), "buy 0 units");
    if (sizeof(arr = pay(price, this_player(), str2, test, 0, str3)) == 1)
	return 0;  /* pay() handles notify_fail() call */
    write("You pay " + text(exclude_array(arr, NUM, NUM * 2 - 1)) + ".\n");
    if (text(exclude_array(arr, 0, NUM - 1)))
	write("You get " + text(exclude_array(arr, 0, NUM - 1)) + ".\n");
    write("The barkeeper gets to work.\n");
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
	file = "/d/Ansalon/balifor/flotsam/obj/drink/" + name;
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

