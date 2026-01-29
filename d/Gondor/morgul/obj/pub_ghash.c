/* 
*  Ghash Water for the Dead Tark Pub
*  Raymundo, Summer 2021
*/

inherit "/std/drink";

#include "/sys/stdproperties.h"

create_drink() 
{
    set_name("water");
    add_name( ({"ghash water", "ghash"}) );
    add_pname( ({"ghash waters", "ghashes"}) );
    set_pname("waters");
    set_adj("ghash");
    set_short("Ghash Water");
    set_pshort("glasses of Ghash Water");
    set_long("This is a glass of brandy that was distilled somewhere "
        + "in Minas Morgul. It's a deep, dark amber color.\n");
    add_item( ({"glass",}), "This glass is quite simple. There is "
        + "nothing remarkable about it in any way, except that "
        + "there  is alcohol in it.\n");

    add_prop(OBJ_I_VALUE, 288);
    set_soft_amount(50);
    set_alco_amount(50);
    add_prop(OBJ_I_WEIGHT,200);
    add_prop(OBJ_I_VOLUME,200);
}
