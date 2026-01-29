inherit "/std/room.c";
inherit "/lib/trade";

#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/sys/money.h"

#define BS(mes) break_string(mes,70)
#define NUM 4 /* How many types of money do we use? */
#define NF(xxx) notify_fail(xxx) /* Nice shortcut to the notify_fail() :) */
#define PATH "/d/Wiz/falke/"
#define DPATH "/d/Wiz/falke/obj/drinks/"

int test; /* to indicate that a test is going on, no money given. */

/*
 * Prototypes
 */

void
create_room()
{
   object board;

   config_default_trade();
   set_short("Angalon-Wizards-in-exile's Lounge");
   set_long(BS("A lounge created for the angalon wizards in exile.  This "+
      "room is appointed with all "+
      "the furnishings needed to help wizards relax from the stresses of "+
      "moving.\n"));

   add_my_desc(BS("This room is now equipped with a wet bar. Type <list> "+
	"to see what you can drink.\n"));

   add_item("furnishings", BS("Included in the room's furnishings are "+
      "some very comfortable chairs, recliners, and couches; ideal for "+
      "'relax'ation.  There are shelves filled with tomes of all "+
      "descriptions which one can 'read', and several tables are setup "+
      "with a variety of diversions.\n"));

   add_exit("/d/Wiz/falke/foyer", "falkes");
   add_exit("/d/Genesis/wiz/virtual", "virtual");

    board = clone_object ( "std/board" );
    board->set_board_name (PATH+ "boards/lounge" );
    board->set_num_notes ( 40 );
    board->set_anonymous ( 0 );
    board->set_err_log ( "boards/err_lounge" );
    board->set_remove_lvl ( 15 );
    board->move ( this_object() );

}

void
init()
{
    add_action("order", "buy");
    add_action("order", "order");
    add_action("test", "test");
   add_action("Read", "read");
   add_action("Relax", "relax");
   add_action("list", "list");
   ::init();
}

int
Read()
{
   write(BS("You select one of your favorite volumes from the shelves, "+
      "find yourself a comfortable seat, and settle down for a good read.\n"));
   return 1;
}

int
Relax()
{
   write("You find a place to sit, take a deep breath, and relax.....\n");
   return 1;
}
/* This is how a simple pub could look like useing the trade object
   I have written.

   Made by Nick    hacked in by Karvenith 
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
    string name, adj, long, str1, str2, str3, change;
    int *arr, price, alco, weight, volume, soft, silent, i;

    if (!str) {
	NF("buy what?\n");
	return 0;
    }

    /* Has the player defined how payment will be done and what
     * change to get back? */  
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
    case "small beer":
    case "beer":
	/* Stout, alco is 7% */
        name = "beer";
	break;
    case "cider":
    case "apple cider":
    case "Royals apple cider":
	/* Beer, alco is 4% */
        name = "cider";
	break;
    case "water":
    case "leyya's water":
    case "Leyya's water":
	/* Special, alco is 40% */
        name = "water";
	break;
    case "fire":
    case "falcon's fire":
    case "Falcon's fire":
	/* Vodka, alco is 60%, now that leaves 80% and 96% ;-/ */
        name = "fire";
	break;
    default:
	NF("That drink isn't available here.\n");
	return 0;
    }
   drink = clone_object(DPATH+name);
  
    /* No drink messege  */
    if (!drink)
    {
	NF("Error in creating drink.\n");
	return 0;
    }

    silent = 0;
    
    
    if (!test && (drink->move(this_player())))
    {
	write("You drop the " + name + " on the floor.\n");
	say(QCTNAME(this_player()) + " drops one " + name + " on the floor.\n");
	drink->move(this_object());
    }
    else if (!test)
    {
	write("You get your " + name + ".\n");
	say(QCTNAME(this_player()) + " gets a " + name + ".\n");
    }
    else
	say(break_string(QCTNAME(this_player()) +
		" seems to be estimating something.\n", 78));

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
    if (!str)
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

int
list() {

    write(
	     "This is the listing of drinks you may order in the lounge.\n\n" +
             "   Small beer                 \n" +
             "   Royal apple cider          \n" +
             "   Leyya's water              \n" +
             "   Falcon's fire              \n\n" +
	     "Order the drink of your choice.\n"+
	     "Try 'test buy beer' to see what would happen\n" +
	     "if you typed 'buy beer'.\n\n" +
	     "");
    
	     return 1;
	}
