/* Inventory alcove for the "store" operated by the bandits of the Blackwall
   mountains.
   - Modified from the inventory room for the shop in Telberin by Shiva.
   Code (c) 1999 to Damian Horton, BKA Casimir.
 */
 
#include "defs.h"

inherit "/d/Emerald/thief_lair/base_cave";
inherit "/lib/store_support";

#include <stdproperties.h>

void
create_banditcave_room()
{
    set_short("An alcove off of a large cavern.\n");
    set_em_long("An alcove off of a larger cavern, somewhere under "+
		"the Blackwall mountains.\n");

    set_max_values(10, 10); // No more than ten items in the inventory at once.
 
    add_exit(THIEF_LAIR_DIR + "cave9", "southwest");
}
 
void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    store_update(ob);
}






