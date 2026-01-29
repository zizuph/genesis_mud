inherit "/std/food";
#include <stdproperties.h>

/*
 * Function name: create_food()
 * Description  : Constructor.  Creates the food.
 */
create_food()
{
    set_name("red beans and rice");
    add_name("plate");
    add_name("plates");
    set_long("Delicious red beans and seasoned rice. The smell and herb "
    +"combination is mouthwatering.\n");
    set_short("plate of red beans and rice");
    set_pshort("plates of red beans and rice");
    set_amount(110);
}

