inherit "/std/food";
#include <stdproperties.h>

/*
 * Function name: create_food()
 * Description  : Constructor.  Creates the food.
 */
create_food()
{
    set_name("plowman's lunch");
    add_name("lunch");
    add_name("lunches");
    set_long("A simple meal of hearty mustard seed and dark"
    +" ale cheese with fennel seed pumpernickel rye bread.\n");
    set_short("plowman's lunch");
    set_pshort("plowman's lunches");
    set_amount(110);
}

