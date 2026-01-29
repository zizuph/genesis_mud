/*
*
*/


inherit "/std/food";
#include <stdproperties.h>

/*
 * Function name: create_food()
 * Description  : Constructor.  Creates the food.
 */
create_food()
{
    set_name("bread and cheese");
	add_name("bread");
	add_name("portion");
	add_name("portions");
    set_long("A simple meal of bread and cheese. It isn't much, but as "
	+"they say: a man cannot live on bread alone.\n");
    set_short("portion of bread and cheese");
    set_pshort("portions of bread and cheese");
    set_amount(110);
}

