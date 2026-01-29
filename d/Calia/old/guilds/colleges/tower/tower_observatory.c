/* Observatory on the top floor of the Tower of Elemental Magic 
   Created 16.1.2000, Bishop
*/

inherit "/d/Calia/guilds/colleges/tower/tower_base.c";

#include <stdproperties.h>
#include <macros.h>
#include "defs.h";

create_room()
{
    set_short("Observatory at the top of the Tower");

    set_long("Long description of this room.\n");

    add_exit(TOWER + "tower_stair_6.c", "down", 0, 1);

    make_college_room();
}