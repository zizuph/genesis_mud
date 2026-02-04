/*
a pair of mining boots dust 921105
 */
#include "/d/Terel/include/Terel.h"
inherit STDARMOUR;
#include <wa_types.h>

create_terel_armour()
{
    set_name(({"boots", "pair of boots"}));
    set_pname("pairs of boots");
    set_short("pair of mining boots");
    set_pshort("pairs of mining boots");
    set_long(break_string("There's nothing special about this pair of " +
	"worn boots. They are very dirty, maybe they have been used for " +
	"mining.\n",70));
    set_adj("mining");
    add_prop("_mining_boots",1);
    set_armour_size(ANY_SIZE);
    set_default_armour(5, A_FEET, 0, 0);
}
