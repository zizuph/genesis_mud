inherit "/std/door";
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include "/d/Gondor/defs.h"

void
create_door()
{
    ::create_door();
    set_door_id("Emyn-Arnen_Herbalist_Trapdoor");
    set_pass_command(({"u","up"}));
    set_door_name(({"trap door", "hatch", "board", "plank", 
        "wooden board", "wooden plank", "door", "trapdoor"}));
    set_door_desc(VBFC_ME("long_desc"));

    set_other_room(ITH_DIR + "emyn-arnen/house4");

    set_open(0);         /* 1 if open, 0 if closed */

    set_str(40);
}

string
long_desc()
{
    if(query_open())
        return BSN("There is a hole in the ceiling. Using the ladder you can " +
            "climb up to the ground floor of the building.");
    else
        return BSN("Looking at the ceiling, you notice that there seems to " +
            "be a hole covered by a large wooden plank. It looks like a trap " +
            "door leading up to the ground floor of the building. If you are " +
            "strong enough you might open the trap door and climb up using " +
            "the ladder here.");
}

