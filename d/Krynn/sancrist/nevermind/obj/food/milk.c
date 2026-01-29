/* A cup of milk for the Tower of Wayreth inn
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
    set_alco_amount(0);
    set_name("milk");
    add_name("drink");
    set_adj(({"white","fresh"}));
    set_pname("milks");
    add_pname("drinks");
    set_short("cup of milk");
    set_pshort("cups of milk");
    set_long("A fresh cup of white milk, this 'regular' beverage is " +
        "actually difficult to find among these lands, as many prefer " + 
	"the stronger brews of alcohol.\n");
    set_drink_msg("Ahh... the milk is quite refreshing and a nice " +
	"change of pace from all that alcohol and water.\n");
    add_prop(OBJ_I_WEIGHT, 125);
    add_prop(OBJ_I_VOLUME, 125);
}

