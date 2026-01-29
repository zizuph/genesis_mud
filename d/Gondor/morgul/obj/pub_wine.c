/* 
*  Wine for the Dead Tark Pub
*  Raymundo, Summer 2021
*/

inherit "/std/drink";

#include "/sys/stdproperties.h"

create_drink() 
{
    set_name("wine");
    add_name("harad wine");
    add_pname("harad wines");
    set_pname("wines");
    set_adj("Harad");
    set_short("Harad Wine");
    set_pshort("glasses of Harad wine");
    set_long("This is a glass of Harad Wine. It's dark purple "
        + "and looks quite strong.\n");
    add_item("glass", "The glass is simple and clear. You can't "
        + "see any dirt on it, so it was probably washed "
        + "recently.\n");

    add_prop(OBJ_I_VALUE, 24);
    set_soft_amount(100);
    set_alco_amount(10);
    add_prop(OBJ_I_WEIGHT,270);
    add_prop(OBJ_I_VOLUME,270);
}
