/* A Potato delicacy for the Tower of Wayreth inn, modified from
 * the VK fruit.
 * -Kentari 12/6/96
 */

inherit "/std/food";
#include <stdproperties.h>
#include <macros.h>
#include "/d/Krynn/common/defs.h"

public void
create_food()
{
    set_name("potato");
    add_name(({"surprise","food"}));
    set_pname("potatoes");
    add_pname(({"surprises","foods"}));
    set_adj("Kendermore");
    add_adj("surprise");
    set_short("Kendermore potato surprise");
    set_pshort("Kendermore potatoes");
    set_long("A deviously plain potato, it actually is filled with all " +
        "the wonderful potato fixings that you could ask for. " +
	"Coming from the land of Kendermore, nothing is quite as " + 
	"innocent as it appears to be, and this potato is no exception.\n");
    add_prop(OBJ_I_WEIGHT, 225);
    add_prop(OBJ_I_VOLUME, 225);
    add_prop(OBJ_I_VALUE, 0);
    set_amount(170);
}
