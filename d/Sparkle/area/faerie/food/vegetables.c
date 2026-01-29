/* Basket of fresh vegetables for Green Oaks
 * Finwe, March 2005
 */
 
inherit "/std/food";
 
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"
 
create_food()
{
    set_name("vegetables");
    add_name("fresh vegetables");
    add_name("basket of fresh vegetables");
    set_pname("baskets of fresh vegetables");
    set_short("basket of fresh vegetables");
    set_pshort("baskets of fresh vegetables");
    set_adj("basket");
    set_adj("fresh");
    set_long("This is a basket of fresh vegetables. It consists of many " +
        "leafy and root vegetables. The vegetables look satisfying and " +
        "very filling.\n");
    set_amount(250);
}
