//  2021-12-02 Meton Added a bit of value, so they don't clutter.
#include "../default.h"
inherit (STD + "armour");

#include <wa_types.h>

void
create_armour()
{
    ::create_armour();

    set_name("medallion");
    set_adj("thanar");
    set_short("medallion of Thanar");
    set_long("A superbly crafted medallion made of pure gold. The symbol "+
      "engraved upon it is that of a dark sun, spreading darkness over all "+
      "of creation.\n");
    set_ac(1);
    set_at(A_NECK);
    add_prop(OBJ_I_VALUE,100);
    add_prop(OBJ_I_VOLUME,500);
    add_prop(OBJ_I_WEIGHT,500);
}

mixed
wear(object what)
{
    if(TP->query_alignment() < 0)
    {
	write("You wear the medallion, as you are truly worthy to serve the "+
	  "glory of Thanar!\n");
	return 0;
    }
    TP->add_hp(-random(50)-10);
    return "A voice rings inside your mind: Craven Defiler! You are not "+
    "worthy to wear this symbol!\n";
}
