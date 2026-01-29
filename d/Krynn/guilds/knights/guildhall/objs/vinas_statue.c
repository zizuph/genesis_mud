/* Statue of Vinas Solamnus for Vingaard Keep  */
/* Teth Jan 97 for new VK */

inherit "/std/object";

#include "/d/Krynn/common/defs.h"
#include "../../local.h"

create_object()
{
    set_name("statue");
    add_name(({"vinas","figure","solemn figure","vinas solamnus","solamnus",
        "marble statue"}));
    set_short("statue of a solemn figure");
    set_long("This is a statue of a solemn figure. A closer look of the " +
        "marbled features reveals that it is a statue of Vinas Solamnus, " +
        "founder of the Solamnian Knights. Carved into the marble statue " +
        "are Vinas Solamnus' facial features, including a typical Solamnian " +
        "moustache. His stony armour is etched with the symbol of the " +
        "Knights of Solamnia, a Kingfisher adorned with a Crown, " +
        "a Rose in its beak, and a Sword in its talons.\n");

    add_prop(OBJ_I_VALUE, 0);
    add_prop(OBJ_I_WEIGHT, 10000);
    add_prop(OBJ_I_VOLUME, 3000);
    add_prop(OBJ_M_NO_GET, "You will get a hernia if you try that again!\n");
    add_prop(OBJ_M_NO_STEAL);
}
