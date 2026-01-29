
/* Iron Delving Tavern transplanted from Inn in solace, coded by Nick...
 * ....Navarre July 3rd 2006, fixed typo, changed meny to menu
 *
 * /d/Ansalon/estwilde/iron_delving/tavern.c
 *
 * Vitwitch 12/2020:
 * -- Named the Dwarvenfug Tavern on account of its smokiness 
 * -- First venue to stock Iron Delving Brewery outputs
 * -- Menu changed
 */


#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include <stdproperties.h>
#include <macros.h>
#include <money.h>
#include "/d/Ansalon/common/brewcraft/brewcraft.h"
#include "/d/Ansalon/guild/dwarf/guild.h"

inherit DWARF_IN;
inherit "/lib/trade";
inherit "/d/Ansalon/common/cheater";

#define PATRON_I_HAS_FOUND_TRAPDOOR   "_patron_i_has_found_trapdoor"
#define NUM sizeof(MONEY_TYPES) /* How many types of money do we use? */

int test; /* to indicate that a test is going on, no money given. */
object ob;
object patron, scout, guard0, guard1, guard2;

int move_item(mixed arg);
int go_west();

void
reset_dwarf_room()
{
    if(!objectp(guard0))
    {
        guard0 = clone_object(LIVING + "dwarf_tavern_guard");
        guard0->arm_me();
        guard0->move(TO);
    }

    if(!objectp(guard1))
    {
        guard1 = clone_object(LIVING + "dwarf_tavern_guard");
        guard1->arm_me();
        guard1->move(TO);
    }

    if(!objectp(guard2))
    {
        guard2 = clone_object(LIVING + "dwarf_tavern_guard");
        guard2->arm_me();
        guard2->move(TO);
    }

    if(!objectp(patron))
    {
	patron = clone_object(LIVING + "patron");
	patron->arm_me();
	patron->move(TO);
    }
    if(!objectp(scout))
    {
	scout = clone_object(LIVING + "vryl");
	scout->arm_me();
	scout->move(TO);
    }
}

int
go_west()
{
    if(objectp(guard1) || objectp(guard2) || objectp(guard0))
    {
	if(TP->query_race_name() == "goblin" ||
           TP->query_race_name() == "minotaur" ||
           TP->query_race_name() == "ogre" ||
           TP->query_prop(DWARF_ENEMY))
	{
	    if(!CAN_SEE(guard1, TP) && !CAN_SEE(guard2, TP) && !CAN_SEE(guard0,TP) )
	    {
	       write("While the guards can't see you, you find the way too narrow " +
                     "to sneak past without alerting them.\n");
	       return 1;
	    }
	    write("The dwarf guards stop you from going west.\n");
	    return 1;
	}
	if(BANISHED(TP))
	{
	    if(!CAN_SEE(guard1, TP) && !CAN_SEE(guard2, TP) && !CAN_SEE(guard0,TP) )
	    {
	       write("While the guards can't see you, you find the way too narrow " +
                     "to sneak past without alerting them.\n");
	       return 1;
	    }
	    guard0->command("spit");
	    guard1->command("spit");
	    guard2->command("say You ain't going that way chum!");
	    return 1;
	}
	return 0;
    }
    return 0;
}

string
find_trapdoor()
{
    TP->add_prop(PATRON_I_HAS_FOUND_TRAPDOOR,1);
    return "By tracing out the floor with your fingers, "+
          "you find a trapdoor by which you can now go <down>.\n";
}

block_if_not_found()
{
  if (TP->query_prop(PATRON_I_HAS_FOUND_TRAPDOOR))
    return 0;
  write("There is no obvious exit down.\n");
  return 1;
}

unseen_if_not_found()
{
  if (TP->query_prop(PATRON_I_HAS_FOUND_TRAPDOOR))
    return 0;
  return 1;
}

public void
hook_smelled(string str)
{
    write("Smoke, smoke everywhere; obscuring all other scents.\n");
}


/*
* Function name: create_room
* Description:   Set up default trade and configure it if wanted.
   */
void
create_dwarf_room()
{
    config_default_trade();
    set_short("The Dwarvenfug Tavern in Iron Delving");
    set_long("@@long_descr");
    add_prop(ROOM_I_NO_CLEANUP, 1);

    add_item(({"roof","ceiling","low roof","low ceiling"}),
      "This tavern has a low ceiling, most likely because most " +
      "its patrons are dwarves. It is barely visible on "+
      "account of the thick smoky fug filling the room.\n");

    add_item(({"pipe smoke","smoke","bluey-grey pipe smoke"}),
      "Smoke from dwarven pipes hangs thickly in this tavern. "+
      "Its earthy aroma goes some way to obscure the sour tang " +
      "of dwarf sweat and goblin blood that lurks in this place.\n");

    add_item(({"stout bar","stout wooden bar","bar","wooden bar"}),
      "A stout bar made of wood. Is that a menu on top of it?\n");

    add_item("menu","A simple menu; barely visible through the smoke. "+
             "You could try reading it if you can get close enough "+
             "to see it clearly.\n");

    add_item(({"small window","window","brewery"}),
      "You feel a window sash and pane on the east wall. This must be the " +
      "legendary window on the Iron Delving brewery to the east! "+
      "A dwarven brewery! It fires the imagination with the promise of slaking "+
      "the most dire of thirsts. Pity you can't see the window through "+
      "the smoke.\n");

    add_item(({"eastern wall","wall"}),
      "In the eastern wall there is reputedly a small window; "+
      "but no one has seen it for some time on account of the smoke.\n");

    add_item(({"floor","wooden floor"}),
      "You can hear that the floor is mostly solid stone, but that sections of it "+
      "sound like they are made from wood. Perhaps you could get down on hands " +
      "and knees and conduct a search below the level of the smoke.\n");

    add_search(({ "floor", "wooden floor", "wood" }), 3, "find_trapdoor",1);

    add_cmd_item("menu", "read", "@@read");

    add_exit(IRON + "brewery1","down","@@block_if_not_found",0,"@@unseen_if_not_found");

    add_exit(IRON + "r12","west","@@go_west");

    reset_dwarf_room();
}


string
long_descr()
{
    return "You stand under the low ceiling of a dwarven " +
    "tavern within the town of Iron Delving. Bluey-grey " +
    "pipe smoke hangs thickly in the air here, as pipe smoking " +
    "along with heavy drinking is a favourite past time of " +
    "most hill dwarves. So thick, warm and aromatic is the smoke " +
    "and other odours that this place has come to be known as " +
    "The Dwarvenfug. In the eastern wall there is reputed to be a small window; " +
    "alleged to look out on the works of the Iron Delving Brewery. The beer "+
    "here has to come from somewhere, so maybe the legend is true. "+
    "The floor is mostly solid stone; but there must be some wooden "+
    "sections too -- creaking unseen under the tread of dwarven boots. "+ 
    "A stout wooden bar at the back of the room is illuminated through the "+
    "haze by rows of guttering candles. Perhaps a menu stands upon it.\n";
}

void
init()
{
    ::init(); /* Since it's a room this must be done. */
    add_action("order", "buy");
    add_action("order", "order");
    add_action("test", "test");
}

int
read(string str)
{
    string brewstring0, brewstring1;

    brewstring0 = "   Iron Delving Export Brew       24 cc\n ";
    brewstring1 = "     ( " + BREWCRAFT_MENU + " )\n";

    write("" +
      " \n\n" +
      "   THE DWARVENFUG TAVERN \n" +
      "             of IRON DELVING \n" +
      "                      \n" +
      "                +-+   \n" +
      "   =============| |   \n" +
      "               `:_;'  \n" +
      "                 `    \n" +
      " \n" + brewstring0 + brewstring1 + "\n" +
      "   Dwarven spirit                220 cc\n\n" +
      "   Iron Rations                   70 cc\n\n\n" +
      "   Dwarven Fuggy (tobacco)        12 cc\n\n" +
      "\n" +
      "The barman will not let you buy more \n" +
      "than ten items at once. \n\n");
    return 1;
}

int
order(string str)
{
    string name, str1, str2, str3;
    int *arr, price, num;


    NF("buy what?\n");
    if (!str)
	return 0;

    if (check_cheater(TP, "the barman"))
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
    case "brew":
    case "brews":
    case "craft brew":
    case "craft brews":
    case "iron delving craft brew":
    case "iron delving craft brews":
        name = "brewcraft_beermug";
        price = num * 24;
        break;
    case "spirit":
    case "spirits":
    case "dwarven":
    case "dwarven spirit":
	name = "spirit";
	price = num * 220;
	break;
    case "rations":
    case "iron rations":
	name = "rations";
	price = num * 70;
	break;
    case "fuggy":
    case "fuggies":
    case "tobacco":
    case "tobaccos":
    case "dwarven tobacco":
    case "dwarven tobaccos":
    case "dwarven fuggy":
    case "dwarven fuggies":
	name = "tobacco";
	price = num * 12;
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

	file = EOBJ + name;
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

