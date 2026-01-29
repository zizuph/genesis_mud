/* A hot coin.
 * Sometimes the GnomishCoinCounter spits them out in the 
 * heat of the action.
 */
 
inherit "/std/coins";

#include "/d/Krynn/common/defs.h"
#include <money.h>
#include <wa_types.h>
#include <macros.h>
#include <global/money.c>

int flag = 0;

void
create_coins()
{
    set_name("coin");
    set_pname("coins");
    set_heap_size(1);
    set_coin_type(MONEY_TYPES[0]);

    add_prop(HEAP_S_UNIQUE_ID, "hot" + query_prop(HEAP_S_UNIQUE_ID));
    set_alarm(0.5, -1.0, "coin_is_hot");
}

/* This coin is hot
 */

void
coin_is_hot()
{
    set_alarm(5000.0, -1.0, "coin_cold");
    add_prop(OBJ_M_NO_GET, "@@get_the_coin");
    add_prop("_coin_is_hot", 1);
    flag = 1;
}

/* replace the coin for a 'real' one
 */

void
coin_cold()
{
     object coin;
     
     seteuid(getuid());
     move_coins(query_coin_type(), num_heap(), 0, E(TO));
     remove_object();
}

mixed
get_the_coin(string str)
{
    object armour;
    
    if(!flag)
    	return 1;
    if((armour = TP->query_armour(TS_LHAND)) ||
	(armour = TP->query_armour(TS_RHAND)))
    {
	flag = 0;
	set_alarm(1.0, -1.0, "remove_object");
	write("You notice that this " + query_coin_type() + " coin is a lot "
	    + "hotter than it should be. But since you are "
	    + "wearing a " + armour->short() + " that's no problem to you.\n");
	return 0;
    }
    return "As you try to pick up the " + short()[2..] + " you burn "
 	+ "yourself. It's hot!\n";
}
