/* Carridin */
/* NPC sharing by Ashlar */

#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/taman_busuk/neraka/local.h"
#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>
#include <money.h>
#include <filter_funs.h>

inherit OUTER_IN;
inherit "/d/Ansalon/lib/pub";

#define SHOPOBJ (NOUTER+"green/ware1")
#define BARKEEP (SHOPOBJ->query_fence())
#define FETCH_BARKEEP (SHOPOBJ->move_fence(TO))

// #define DEBUG(x)    find_player("ashlar")->catch_msg("GBAR: " + x + "\n")

object ob;

int balarm = 0;

void
create_neraka_room()
{
    set_short("Inside a bar in the Green Quarter");
    set_long("The bar is named the Queen's Heads. It is a fairly quiet one, " +
	     "although it does recieve a decent amount of custom. A few tables " +
	     "have been placed around the room, and at the back of the room " +
	     "stands a counter.\n");
    set_quarter(GREEN);
    add_item_inside();
    add_item("counter", "You note that a pricelist has been placed upon " +
	     "the polished counter.\n");
    add_item("pricelist", "There are words on it for you to read, if you " +
	     "can muster up the brainpower to do it.\n");	
    add_cmd_item("pricelist",({"read"}), ({"@@read_pricelist@@"}));
    add_item("tables", "The tables are old and well-used. A few customers " +
	     "sit at the tables, having a drink.\n");
    add_item("customers", "They sit at their tables, doing what one would " +
	     "expect of them at a place such as this.\n");

    add_exit(NOUTER+"green/g5","northeast");

    add_drink_object(({"beer","pale beer","beers","pale beers"}),
		     NOBJ + "drink/swater",
		     10);
    add_drink_object(({"wine","wines","glass of wine","glasses of wine"}),
		     NOBJ + "drink/gwine",
		     78);
    add_drink_object(({"juice","juices","bad juice","bad juices"}),
		     NOBJ + "drink/badjuice",
		     300);

    setuid();
    seteuid(getuid());
    LOAD_ERR(SHOPOBJ);
}

string
read_pricelist()
{
    return "----------------------------------------\n"+
	"Pale beer           ---   10cc          \n"+
	"A glass of wine     ---   78cc          \n"+
	"Bad juice           ---  300cc          \n"+
	"----------------------------------------\n";
}

/*
* Function name: init
* Description:   Initalize the pub actions
*/
void
init()
{
    ::init(); /* Since it's a room this must be done. */

    /* This needs be updated every time someone enters the room */
    set_barkeeper(BARKEEP);
    init_pub();
}

/* NPC SHARING FUNCTIONS */

void
move_barkeep(object dest)
{
    if (!sizeof(FILTER_PLAYERS(all_inventory(TO))) && objectp(BARKEEP) && P(BARKEEP,TO))
        BARKEEP->move_living("through a hidden door",dest);
}

void
may_fetch_barkeep()
{
    object *ob;

    if (!BARKEEP || P(BARKEEP, TO))
        return;

    ob = FILTER_PLAYERS(all_inventory(TO));
    if (sizeof(ob))
    {
        FETCH_BARKEEP;
    }
    else
    {
        remove_alarm(balarm);
        balarm = 0;
    }
}   

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    if (interactive(ob) && !balarm)
        balarm = set_alarm(8.0,5.0,may_fetch_barkeep);
}

