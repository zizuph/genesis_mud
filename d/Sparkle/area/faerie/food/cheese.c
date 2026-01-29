/* Brick of Cheese for Green Oaks
 * Finwe, March 2005
 */
 
inherit "/std/food";
 
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"

 
create_food()
{
    set_name("brick of cheese");
    add_name("cheese");
    add_name("brick");
    set_pname("bricks of cheese");
    set_short("brick of cheese");
    set_pshort("bricks of cheese");
    set_adj("small");
    set_long("The brick of cheese is white and solid looking. It was " +
        "made from fresh milk and looks delicious.\n");
    set_amount(150);
}
