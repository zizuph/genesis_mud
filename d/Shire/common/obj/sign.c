inherit "/std/object";

#include <macros.h>
#include <stdproperties.h>

void
create_sign()
{
}

void
create_object()
{
    add_prop(OBJ_M_NO_GET, "You can't as it is securely fastened to the ground.\n");
    create_sign();
}

init()
{
    ::init();
    add_action("read", "read");
}

int
read(string arg)
{
    if(!id(arg))
	return notify_fail("Read what?\n");

    write("You read the "+short()+".\n");
    write(long());
    return 1;
}
