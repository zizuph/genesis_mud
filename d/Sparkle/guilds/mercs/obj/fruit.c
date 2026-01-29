inherit "/std/food";
#include <stdproperties.h>

create_food()
{
    set_name("fruit");
    set_adj("dried");
    set_short("bit of dried fruit");
    set_pshort("bits of dried fruit");
    set_long("The dried fruit does not look appealing, but "+
	"it does the trick.\n");
    set_amount(212);
}

