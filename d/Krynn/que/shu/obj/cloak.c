/* Leather armour for barbarians.
 * ~Aridor 08/97
 */

inherit "/std/armour";
#include "../local.h"
#include <wa_types.h>


void
create_armour()
{
    set_name("cloak");
    set_short("dirty brown cloak");
    set_adj(({"dirty","brown"}));
    set_long("It's a dirty brown cloak of decent quality, made from robust material.\n");
    set_default_armour(4,A_ROBE);
}
