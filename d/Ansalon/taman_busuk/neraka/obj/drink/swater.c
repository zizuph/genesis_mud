#include "/d/Ansalon/common/defs.h"
#include <ss_types.h>

inherit "/std/drink";
#include <stdproperties.h>

create_drink()
{
    set_soft_amount(200);
    set_alco_amount(0);
    set_name("beer");
    add_name("pale beer");
    add_name("water");
    set_adj("pale");
   
    set_short("pale beer");
    set_pshort("pale beers");
    set_long("@@see_water@@\n");
    add_prop(OBJ_I_WEIGHT, 230);
    add_prop(OBJ_I_VOLUME, 230);
}

string
see_water()
{
	if (TP->query_stat(SS_WIS) > 55)
		return "After examining the pale beer closer, you discover " +
			"that it is in fact merely spiced water. A clever ploy " +
			"to fool the customers.";
	else
		return "It's a glass of pale beer.";
}
