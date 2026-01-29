/*
*
*/


inherit "/std/drink";
#include "/sys/stdproperties.h"

/*
 * Function name: create_drink()
 * Description  : Constructor.  Creates the drink.
 */
create_drink()
{
    set_soft_amount(100);
    set_alco_amount(25);
    set_name("ale");
    set_adj("iron flagon");
    set_short("iron flagon ale");
    set_pshort("iron flagon ales");
    set_long("This is a basic form of ale served at the Iron Flagon Inn "
	+"in the city of Neverwinter. It's taste is quite bland, but it is "
    +"the most popular drink served at the inn.\n");
    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 100);
}
