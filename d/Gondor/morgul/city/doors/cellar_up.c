inherit "/std/door";

#include "/d/Gondor/defs.h"

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

#define MIN_STRENGTH 40

void
create_door()
{
    ::create_door();
    set_door_id("Morgul_Cellar_Trapdoor");
    set_pass_command(({"d","down"}));
    set_door_name(({"wooden plank", "trap door", "hatch", "board",
        "plank", "door", "trapdoor"}));
    set_door_desc(VBFC_ME("long_desc"));
    set_closed_desc("");
    set_open_desc("There is an open trap door leading down.\n");
    set_str(MIN_STRENGTH);

    set_other_room(MORGUL_DIR + "cellar/dung_1e5");

    set_open(0);         /* 1 if open, 0 if closed */
    enable_reset();
}

string
long_desc()
{
    if (query_open())
        return BSN(
            "A simple wooden board on iron hinges that is leaning "
          + "against a wall next to a hole in the floor.");
    else
        return BSN(
            "A simple wooden board on iron hinges that probably "
          + "covers a hole in the floor. The board looks rather heavy.");
}


