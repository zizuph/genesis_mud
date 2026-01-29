/* Terminator started this,
 * Aridor, 11/94
 */

#include "../local.h"

inherit CAVE_BASE

#include <macros.h>
#define CAVE2   (CAVE + "cave2")

void
create_vin_mount_room()
{
    set_short("Cave");
    set_long("Cool damp air hits your face as you move through the narrow hole." +
	     " To your northeast, the cave seems to become even narrower.\n");
    add_exit(CAVE2, "up","@@check@@");
    add_exit(THIEF_CAVERN, "northeast");
    add_item(({"bars","iron bars"}),
	     "@@the_bars@@");
    DARK;
    INSIDE;

    CAVE2->load_me();
}

void
init()
{
    ADA("bend");
    ::init();
}

int
check()
{
    write("You move carefully along the narrow cave, ");
    if (CAVE2->query_bars())
      {
	  write("but there are iron bars blocking your exit!\n");
	  return 1;
      }
    write("and emerge into a fairly large room.\n");
    return 0;
}

int
bend(string str)
{
    return CAVE2->bend(str);
}

string
the_bars()
{
    return "This is an iron grid affixed before the opening. " +
      CAVE2->bend_already() + "\n";
}
