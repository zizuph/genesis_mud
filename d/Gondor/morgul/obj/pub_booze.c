/* 
*  Booze for the Dead Tark Pub
*  Raymundo, Summer 2021
*/

inherit "/std/drink";

#include "/sys/stdproperties.h"

create_drink() 
{
    set_name("booze");
    add_name("mirkwood booze");
    add_pname("mirkwood boozes");
    set_pname("boozes");
    set_adj("mirkwood");
    set_short("Mirkwood Booze");
    set_pshort("shots of Mirkwood Booze");
    set_long("This is a small glass--not much bigger than a "
        + "thimble--of strong alcohol. It smells as if it were "
        + "distilled from berries.\n");
    add_item( ({"glass", "shot", "shot glass"}), "This glass is very "
        + "small, holding only an ounce or so of liquid. But the "
        + "liquid smells very strong.\n");
    add_cmd_item( ({"booze", "shot", "glass", "mirkwood booze"}), "smell",
        "It smells very strong. Your nose burns a little! You think you can "
        + "smell blackberries, but it's hard to be sure with such a strong "
        + "alcohol smell.\n");
    add_prop(OBJ_I_VALUE, 72);
    set_soft_amount(80);
    set_alco_amount(25);
    add_prop(OBJ_I_WEIGHT,100);
    add_prop(OBJ_I_VOLUME,10);
}
