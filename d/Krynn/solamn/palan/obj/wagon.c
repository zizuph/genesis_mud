/* created by Aridor 03/97 */

#include "../local.h"

inherit "/std/object";

void
create_object()
{
    set_short("horse-pulled wagon");
    set_name("wagon");
    add_name("carriage");
    set_adj("horse-pulled");
    set_long("This is a wagon, pulled by two horses. You can enter " +
	     "it.\n");
}

init()
{
    ADA("enter");
    ADD("enter","board");
    ::init();
}

int
enter(string str)
{
    return 0;
}
