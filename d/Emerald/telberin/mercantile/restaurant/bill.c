inherit "/std/object";

#include "defs.h"
#include <money.h>
#include <stdproperties.h>
#include <language.h>
#include <macros.h>

void
create_object()
{
    set_name("bill");
    set_adj("dinner");

    set_long("It is an empty dinner bill from the " +
        TELBERIN_RESTAURANT_NAME + ".\n");
}

public string
money_text(int amnt)
{
    int i, *coins = MONEY_SPLIT(amnt);
    string str = "";

    for (i = sizeof(coins) -1; i >= 0; i--)
    {
        if (coins[i])
	{
            str += sprintf("%2d%s ", coins[i], FCHAR(MONEY_TYPES[i]));
	}
    }

    return str;
}

public void
set_order(object *order)
{
    int i;
    string str = "";
    int cost, total = 0;

    for (i = 0; i < sizeof(order); i++)
    {
	cost = order[i]->query_prop(HEAP_I_UNIT_VALUE);
	total += cost;
	str += sprintf("%-30s %16s\n", capitalize(LANG_ASHORT(order[i])),
	    money_text(cost));

    }

    set_long("It is a dinner bill from the " + TELBERIN_RESTAURANT_NAME +
        ".\n\n" + str + "\n" + "Total: " + money_text(total) + "\n");
}
    
