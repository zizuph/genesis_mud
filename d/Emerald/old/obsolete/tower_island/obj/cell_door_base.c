inherit "/std/door";

#include "../defs.h"
#include <stdproperties.h>

void
create_door()
{
    set_door_desc("This is a large steel door. It seems quite sturdy
    set_open_mess(({"pulls on the handle of the cell door.\n", "The door" +
                    "quickly swings open on its silent hinges.\n"}));
    set_close_mess("swings the cell door closed.\n");
    set_open_fail("pulls on the handle of the cell door, but it does not" +
                  "budge.\n");
    set_open(0);
    set_locked(1);
    set_no_pick();
}   

