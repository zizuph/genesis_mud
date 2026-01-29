inherit "/std/food";
#include <stdproperties.h>

/*
 * Function name: create_food()
 * Description  : Constructor.  Creates the food.
 */
create_food()
{
    set_name("stew");
    add_name("beef and vegetable stew");
    set_adj("beef and vegetable");
    add_adj("beef");
    add_adj("vegetable");
    set_short("beef and vegetable stew");
    set_pshort("beef and vegetable stews");
    set_long("This is bowl of beef and vegetable stew contains a "
    +"greyish meat that may or may not be beef, a few potatoes "
    +"and a couple of carrots. It is heavily spiced, most "
    +"likely to offset the meat.\n");
    set_amount(212);
}

