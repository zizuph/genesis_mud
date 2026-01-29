
inherit "/std/drink";
#include <stdproperties.h>

create_drink()
{
    set_soft_amount(500);
    set_alco_amount(50);
    set_name("juice");
    add_name("bad juice");
    add_name("mug");
	add_name("green stuff");

    set_short("mug of bad juice");
    set_pshort("mugs of bad juice");

    set_long("The mug contains a fair amount of green icky stuff.\n");
   
    add_prop(OBJ_I_WEIGHT, 180);
    add_prop(OBJ_I_VOLUME, 150);
}

void
special_effect(int numofdrinks)
{
    write("Your throat feels as though on fire as you gulp down the " +
		"green icky stuff.\n");
}
