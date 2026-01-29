/* Counter in gemshop
 * Created by Damaris 02/01
 */

inherit "/std/container";
#include <stdproperties.h>
#include "../defs.h"


void create_container() {
    set_name("counter");
    set_adj(({"small","wooden","cluttered"}));
    set_short("small wooden counter");
    set_long("It is a small wooden counter with a few tools scattered upon it.\n");
 
    add_prop(OBJ_I_NO_GET, 1);
    add_prop(CONT_I_ATTACH, 1);
    add_prop(OBJ_I_VOLUME, 5000);
    add_prop(OBJ_I_WEIGHT, 9000);
    add_prop(CONT_I_MAX_WEIGHT, 100000);
    add_prop(CONT_I_MAX_VOLUME, 1000000);
}
