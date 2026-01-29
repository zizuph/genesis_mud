/* Desk in ship
 * Created by Damaris 02/01
 */

inherit "/std/container";
#include <stdproperties.h>

void
create_container()
{
    set_name("desk");
    set_adj(({"large","wooden","cluttered"}));
    set_short("large wooden desk");
    set_long("It is a large wooden desk that is quite cluttered.\n");
 
    add_prop(OBJ_I_NO_GET, 1);
    add_prop(CONT_I_ATTACH, 1);
    add_prop(OBJ_I_VOLUME, 5000);
    add_prop(OBJ_I_WEIGHT, 9000);
    add_prop(CONT_I_MAX_WEIGHT, 100000);
    add_prop(CONT_I_MAX_VOLUME, 1000000);
}
