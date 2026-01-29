/*
 * /d/Rhovanion/common/rhun/camp/guardpost.c
 *
 * Guard post at the entrance to the barbarian camp.
 */

inherit "/d/Rhovanion/common/rhun/camp/room";

#include <filter_funs.h>
#include "/d/Rhovanion/defs.h"

void
create_camp()
{
  set_long("This is a guard post at the entrance to the evil camp. " +
           "@@see_guards" + "\n");
  set_short("Guard post");
  add_exit(CAMP_DIR + "camp1", "north", "@@try_go");
  add_exit(CAMP_DIR + "testdis", "south");

  MaxBar = 4;
}

/*
 * Function name: see_guards
 * Description:   Description of room with/without guards.
 * Arguments:     (none)
 * Returns:       A description of guards/no guards.
 */

string
see_guards()
{
    /* This is not finished */
    return "You see some guards. Maybe... (FIX THIS VBFC!)";
}

