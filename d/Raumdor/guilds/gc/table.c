/* Round table
 * For Gentleman's Club
 * Damaris 10/2001
 */

inherit "/std/container";
#include <stdproperties.h>


void
create_container()
{
    set_name("table");
    set_adj(({"large", "round"}));
    set_short("large round table");
    set_long("A large round table made from cherry wood.\n");
    add_prop(OBJ_I_NO_GET, 1);
    add_prop(CONT_I_ATTACH, 1);
    add_prop(OBJ_I_VOLUME, 5000);
    add_prop(OBJ_I_WEIGHT, 9000);
    add_prop(CONT_I_MAX_WEIGHT, 100000);
    add_prop(CONT_I_MAX_VOLUME, 1000000);
}
