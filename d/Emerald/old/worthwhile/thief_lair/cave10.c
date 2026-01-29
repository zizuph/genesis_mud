/* Where the bandits store their supplies. This room cannot be accessed
   unless there are no bandits in cave9. As eliminating the bandits there
   should be rather difficult, the contents of this chamber are substantial.
   Code (c) 1999 to Damian Horton, BKA Casimir.
 */
 
#include "defs.h"

inherit "/d/Emerald/thief_lair/base_cave";

#include <stdproperties.h>

void
create_banditcave_room()
{
    set_short("An alcove off of a large cavern.\n");
    set_em_long("An alcove off of a larger cavern, somewhere under "+
		"the Blackwall mountains.\n");

    add_exit(THIEF_LAIR_DIR + "cave9", "east");
}






