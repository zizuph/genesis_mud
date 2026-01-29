/* Sauteed Potatoes
 * Finwe, September 2001
 */

#include </stdproperties.h>
inherit "/std/food";

void
create_food()
{
    add_name("boar");
    set_name("roasted boar");
    set_short("roasted wild boar");
    set_pshort("roasted wild boars");
    set_adj(({"wild"}));
    set_long("This is a thick slab of wild boar meat. It was slow cooked " +
        "over a barbecue and looks juicy.\n");
    set_amount(250);
    add_prop(OBJ_I_VALUE,150); 
}
