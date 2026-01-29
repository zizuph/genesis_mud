/* Ashlar, 27 Jul 97 */


#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include <stdproperties.h>

inherit "/std/object";
inherit "/lib/keep";

void
create_object()
{
    set_name("pass");
    add_name(VALID_PASS_ID);
    set_adj("pass");
    set_short("black pass");
    set_long("The pass is a small square of paper, upon which the " +
        "following is written:\n\n"+
        "  The bearer of this pass is allowed passage to the Inner City.\n\n" +
        "It is signed by a high officer of the Black Dragonarmy.\n");
    add_prop(OBJ_I_WEIGHT, 50);
    add_prop(OBJ_I_VOLUME, 25);
}
