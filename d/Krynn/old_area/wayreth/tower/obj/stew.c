/* A stew for the Tower of Wayreth inn, from
 * the VK soup.
 * -Kentari 12/6/96
 */

inherit "/std/food";
#include <stdproperties.h>
#include <macros.h>
#include "/d/Krynn/common/defs.h"

public void
create_food()
{
    set_name("stew");
    add_name("food");
    set_pname("stews");
    add_pname("foods");
    set_adj(({"steaming","Ice Folk"}));
    add_adj("ice folk");
    set_short("steaming Ice Folk stew");
    set_pshort("steaming Ice Folk stews");
    set_long("This stew is made in the traditional Ice Folk style " +
        "of the Thanoi region and used to keep any traveler warm. " +
        "Careful eating, as it still is steaming.\n");
    set_amount(182);
}

