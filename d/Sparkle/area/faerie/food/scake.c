/* Sweet Cake for Green Oaks
 * Finwe, March 2005
 */
 
inherit "/std/food";
 
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"
 
create_food()
{
    setuid();
    seteuid(getuid());

    set_name("cake");
    add_name("sweet cake");
    set_adj("tasty");
    set_adj("sweet");
    set_short("tasty sweek cake");
    set_pshort("tasty sweet cakes");
    set_long("This is an elven delicacy called sweet cake. It is sweet " +
        "looking and flaky.\n");
    set_amount(75); 
    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 50);
}
