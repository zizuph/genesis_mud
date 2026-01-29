/*
 * Fixed door so it can be opened/closed
 * Finwe, May 2019
 */

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
    set_pass_command(({"u","up"}));
    set_door_name(({"trap door", "hatch", "door", "trapdoor"}));
    set_door_desc(BSN("The trap door is made from a thick steel plate "
      + "and must be very heavy. There is no lock visible on the "
      + "door."));
    set_closed_desc("In the middle of the roof, there is a "
      + "closed trap door leading up.\n");
    set_open_desc("In the middle of the roof, there is an "
      + "open trap door leading up.\n");
    set_lock_desc("There is no lock visible on the trap door.\n");
    set_fail_open(({"The trap door is already open.\n",
        "You try to open the trap door, but there seems to be "
      + "something heavy standing on it.\n"}));
    set_str(MIN_STRENGTH);
    set_other_room(MORGUL_DIR + "cellar/dung_1ws");

    set_open(0);         /* 1 if open, 0 if closed */
}
