/* Tantallon coded by Nick */

#include "/d/Krynn/common/defs.h"
#include "local.h"

inherit TANTALLON_INSIDE;

#include <stdproperties.h>
#include <macros.h>
#include <money.h>

/*
 * Prototypes
 */
object make_drink(string name, string adj, string long, int weight,
		  int volume, int soft, int alco);

load_drunk()
{
    clone_object(MON + "dr_draco")->move_living("xxx", TO);
}

reset_tantallon_room()
{
    if (present("drunk", TO))
	return;
    set_alarm(1.0,0.0,"load_drunk");
    set_alarm(10.0,0.0,"load_drunk");
}
		  
/*
 * Function name: create_room
 * Description:   Set up default trade and cofigure it if wanted.
 */
void
create_tantallon_room()
{
    set_short("The Draco inn");
    set_long(
	"You are in the Draco inn, mostly draconians visit this\n" +
	"place. There is a big sign hanging here on which you can\n" +
	"read: \n\n" +
	"   Firstclass  beer      12 cc\n\n" +
	"West you can go out to the road or you could go east to\n" +
	"inner parts of the tent.\n" +
	"");
    
    add_exit(TDIR + "city19", "west", 0);
    add_exit(TDIR + "tent3", "east", 0);

    INSIDE

    reset_room();
}

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
    object drink;
    string name, adj, long;
    int price, alco, weight, volume, soft, i;

    if (!str)
    {
	NF("Buy what?\n");
	return 0;
    }

    switch(str)
    {
    case "beer":
	/* Beer, alco is 4% */
	name = "beer";
	adj = "light";
	long = "It's a small but refreshing beer.\n";
	weight = 100;
	volume = 100;
	soft = 100;
	alco = 4;
	price = 12;
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
    
    NF("You cannot pay the price.\n");
    if (!MONEY_ADD(this_player(), -price))
        return 0;

    write("You pay the price with your hard earned money.\n");
    if (drink->move(this_player()))
    {
	write("You drop the " + name + " on the floor.\n");
	say(QCTNAME(this_player()) + " drops one " + name + " on the floor.\n");
	drink->move(this_object());
    } else {
	write("You get your " + name + ".\n");
	say(QCTNAME(this_player()) + " buys a " + name + ".\n");
    }

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
    drink->set_short();
    drink->set_name(name);
    drink->add_name("draco_beer");
    drink->set_adj(adj);
    drink->set_long(long);
    drink->set_soft_amount(soft);
    drink->set_alco_amount(alco);
    drink->add_prop(OBJ_I_WEIGHT, weight);
    drink->add_prop(OBJ_I_VOLUME, volume);
    drink->add_prop(HEAP_S_UNIQUE_ID, "draco_beer");

    return drink;
}
