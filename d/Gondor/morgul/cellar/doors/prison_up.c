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
    set_door_id("Morgul_Prison_Trapdoor");
    set_pass_command(({"d","down"}));
    set_door_name(({"trap door", "hatch", "door", "trapdoor"}));
    set_door_desc(BSN("The trap door is made from a thick steel plate "
      + "and must be very heavy. There is no lock visible on the "
      + "door."));
    set_closed_desc("In the middle of the floor, there is a "
      + "closed trap door leading down.\n");
    set_open_desc("In the middle of the floor, there is an "
      + "open trap door leading down.\n");
    set_str(MIN_STRENGTH);

    set_other_room(MORGUL_DIR + "cellar/pris_2w1");

    set_open(0);         /* 1 if open, 0 if closed */
}

