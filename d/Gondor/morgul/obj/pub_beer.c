/* 
*  Beer for the Dead Tark Pub
*  Raymundo, Summer 2021
*/

inherit "/std/drink";

#include "/sys/stdproperties.h"

create_drink() 
{
    set_name("beer");
    add_name("morgul beer");
    add_pname("morgul beers");
    set_pname("beers");
    set_adj("Morgul");
    set_short("Morgul Beer");
    set_pshort("mugs of Morgul Beer");
    set_long("This is a mug of Morgul Beer. The beer is a murky, "
        + "brown color, but at least it smells like beer.\n");
    add_item("mug", "The mug is a simple earthenware mug. "
        + "It's grey in color and looks very cheap.\n");
    add_cmd_item( ({"beer", "beers","mug","mugs"}), "smell",
        "It smells like beer.\n");
    add_prop(OBJ_I_VALUE, 12);
    set_soft_amount(270);
    set_alco_amount(5);
    add_prop(OBJ_I_WEIGHT,270);
    add_prop(OBJ_I_VOLUME,270);
}
