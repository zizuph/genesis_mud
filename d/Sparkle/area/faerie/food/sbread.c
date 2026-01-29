/* Sweet Bread for Green Oaks
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

    set_name("bread");
    add_name("sweet bread", "slice of sweet bread");
    set_adj("sweet");
    set_short("slice of sweet bread");
    set_pshort("slices of sweet bread");
    set_long("This is a slice of sweet bread. It is fresh and light, " +
        "and very filling.\n");
    set_amount(50); 
    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 60);
}
