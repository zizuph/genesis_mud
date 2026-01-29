/* Carridin */
/* NPC sharing by Ashlar */
/*
 * Louie April 2006 - Set greed to 100.
 */

#include "/d/Ansalon/taman_busuk/neraka/local.h"
#include "/d/Ansalon/common/defs.h"
#include <filter_funs.h>

inherit OUTER_IN;
inherit "/lib/shop";
inherit "/d/Ansalon/common/cheater";

#define BAROBJ (NOUTER+"green/bar1")
#define FENCE (fence)
#define FETCH_FENCE (BAROBJ->move_barkeep(TO))
#define FENCE_HERE  (P(FENCE,TO))

// #define DEBUG(x)    find_player("ashlar")->catch_msg("GWARE: " + x + "\n")

object fence;
int balarm = 0;

void
reset_neraka_room()
{
	if (!objectp(fence))
		fence = clone_npc(NNPC + "fenster");
}

void
create_neraka_room()
{	
	set_short("Inside a large warehouse");
	set_long("You find yourself in a large warehouse. Crates of various " +
		"sizes have been stacked all around. @@hob_here@@\n");
	set_quarter(GREEN);

	add_item("crates", "Crates have been stacked all over the warehouse. " +
		"You notice that many of them carry various labels.\n");
	add_item(({"label", "labels"}), "Looking at one of the many different " +
		"labels, you see:\n@@random_label@@\n");
      
	add_exit(NOUTER+"green/g19","southeast","@@msg@@",0,0);

	config_default_trade();
    set_money_greed_buy(100);
    set_money_greed_sell(100);

    set_store_room(NOUTER + "green/storage1");
  
	reset_room();
}

int
do_buy(string a)
{
    if(!FENCE_HERE)
        return 0;
        
        if (check_cheater(TP, FENCE))
        return 1;
    return ::do_buy(a);
}

int
do_sell(string a)
{
    if(!FENCE_HERE)
        return 0;
        
        if (check_cheater(TP, FENCE))
        return 1;
    return ::do_sell(a);
}

int
do_value(string a)
{
    if(!FENCE_HERE)
        return 0;
    return ::do_value(a);
}

int
do_show(string a)
{
    if(!FENCE_HERE)
        return 0;
    return ::do_show(a);
}

int
do_list(string a)
{
    if(!FENCE_HERE)
        return 0;
    return ::do_list(a);
}

int
do_store(string a)
{
    if(!FENCE_HERE && !TP->query_wiz_level())
        return 0;
    return ::do_store(a);
}

void
init()
{
    ::init();
    add_action(do_buy,   "buy");
    add_action(do_sell,  "sell");
    add_action(do_value, "value");
    add_action(do_show,  "show");
    add_action(do_list,  "list");
    add_action(do_store, "store");
}

int
msg()
{
    write("You step out of the warehouse and out on the road.\n");
    return 0;
}

string
hob_here()
{
	if(!present("neraka_fenster"))
	{
		return "There isn't much to be said for this place, except that it's " +
			"as dull as it's dusty.";
	}
	else
	{
		return "The shifty-looking hobgoblin lurking around is obviously up to no good.";
	}
}

string
random_label()
{
	switch (random(7))
	{
		case 0:
		return "\"Lutes Loot, Neraka\"";
		case 1:
		return "\"Lutes Loot, Neraka\"";
		case 2:
		return "\"Fragile\"";
		case 3:
		return "\"Flotsam, misc goods\"";
		case 4:
		return "\"Urgent, Port Balifor\"";
		case 5:
		return "\"Express delivery, Solamnia; Blue Dragonarmy\"";
		case 6:
		return "\"Virgins, one case of.\nSacrifice, for the use of.\"";
	}
}

/* NPC SHARING FUNCTIONS */

object
query_fence()
{
    return fence;
}

void
move_fence(object dest)
{
    if (!sizeof(FILTER_PLAYERS(all_inventory(TO))) && objectp(fence) && FENCE_HERE)
    {
        fence->move_living("through a hidden door",dest);
    }
}

void
may_fetch_fence()
{
    object *ob;

    if (!fence || P(fence, TO))
        return;

    ob = FILTER_PLAYERS(all_inventory(TO));
    if (sizeof(ob))
        FETCH_FENCE;
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
        balarm = set_alarm(8.0,5.0,may_fetch_fence);
}

