/* A brandy for the Tower of Wayreth inn, modified from
 * the VK beer.
 * -Kentari 12/6/96
 */

inherit "/std/drink";
#include <stdproperties.h>
#include <macros.h>
#include "/d/Krynn/common/defs.h"

public void
create_drink()
{
    set_soft_amount(125);
    set_alco_amount(12);
    set_name("brandy");
    add_name("alcohol");
    set_adj(({"smooth","warming"}));
    set_pname("brandies");
    add_pname("alcohols");
    set_short("glass of brandy");
    set_pshort("glasses of brandy");
    set_long("A glass of brandy, perfect for those cold nights and " +
        "hours of long study. It is dark and rich in colour, as a " + 
	"good brandy should be.\n");
    set_drink_msg("You feel the warmth of the drink go down your " +
	"throat and throughout your body.\n");
    add_prop(OBJ_I_WEIGHT, 125);
    add_prop(OBJ_I_VOLUME, 125);
}

