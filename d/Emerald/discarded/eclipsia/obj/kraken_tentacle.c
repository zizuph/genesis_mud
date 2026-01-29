#include <macros.h>
#include <task.h>

inherit "/std/paralyze";

int strength = 10;

void
create_paralyze()
{
    set_fail_message("You are busy enough trying to get loose and generally " +
		     "stay alive!\n");
    set_remove_time(600);
}

