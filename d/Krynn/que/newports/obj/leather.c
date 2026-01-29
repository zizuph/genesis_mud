/* original from Percy from the crypt in the graveyard. */
/* Area around Newports, Abanasinia
 * Aridor, 03/95
 */

inherit "/std/armour";

#include <wa_types.h>

void
create_armour()
{
    set_name("armour");
    add_name("leather");
    set_adj("tattered");
    add_adj("leather");
    set_short("tattered leather armour");
    set_long("It's a tattered piece of leather, you could barely call it armour.\n");
    set_default_armour(8, A_BODY, ({1,1,-2}));
}
