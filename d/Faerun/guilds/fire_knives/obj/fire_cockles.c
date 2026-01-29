inherit "/std/food";
#include <stdproperties.h>

/*
 * Function name: create_food()
 * Description  : Constructor.  Creates the food.
 */
create_food()
{
    set_name("stew");
    add_name("cockle and mussel stew");
    set_adj("cockle and mussel");
    add_adj("cockle");
    add_adj("mussel");
    set_short("cockle and mussel stew");
    set_pshort("cockle and mussel stews");
    set_long("Salt water clams and fresh water mussels melded together "
    +"in a white wine reduction with fresh herbs.\n");
    set_amount(212);
}

