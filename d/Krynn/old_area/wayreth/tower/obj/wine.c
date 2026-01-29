/* A wine for the Tower of Wayreth inn, modified from
 * the VK wine.
 * -Kentari 12/6/96
 */

inherit "/std/drink";
#include <stdproperties.h>
#include <macros.h>
#include "/d/Krynn/common/defs.h"

public void
create_drink()
{
    set_soft_amount(185);
    set_alco_amount(25);
    set_name("wine");
    add_name("alcohol");
    set_adj(({"imported","Silvanesti"}));
    add_adj("Silvanesti");
    set_pname("wines");
    add_pname("alcohols");
    set_short("imported Silvanesti wine");
    set_pshort("imported Silvanesti wines");
    set_long("This wine is imported from Silvanesti, the wary land " +
	"of elves. Savored for its amazing quality and taste, this " +
	"wine is very prestigious and hard to acquire.\n");
    set_drink_msg("The Sylvanesti wine tastes like the nectar of the " +
        "gods, and leaves a sweet taste in your mouth.\n");
    add_prop(OBJ_I_WEIGHT, 185);
    add_prop(OBJ_I_VOLUME, 185);
}

