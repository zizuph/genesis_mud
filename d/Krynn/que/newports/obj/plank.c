/* Area around Newports, Abanasinia
 * Aridor, 03/95
 */

inherit "/std/weapon";

#include <wa_types.h>
#include <ss_types.h>

void
create_weapon()
{
    set_name("plank");
    set_adj("wooden");
    add_name("club");
    add_name("board");
    set_short("wooden plank");
    set_long("This is an ordinary wooden plank. It's about 2 feet long and round. " +
	     "It'd make a nice weapon to bash heads, actually.\n");
    set_default_weapon(5,8,W_CLUB,W_BLUDGEON,W_BOTH);
}
