inherit "/d/Emerald/std/door";

#include "../defs.h"

#define BANK_CLOSED 0

void
create_emerald_door()
{
    object l;
    set_name("door");
    set_adj(({ "massive", "iron" }));

    l = add_default_lock();
    l->set_long("A complex lock of gnomish design.  It isn't clear how to " +
                "engage it.\n");
    l->set_key("NONE");

#if BANK_CLOSED
    set_open(0);
    l->lock();
#else
    set_open(1);
    l->unlock();
#endif BANK_CLOSED

    set_long("A huge, iron door secures the entrance to the small building.\n");
}

public int
prevent_open_door()
{
    write("The door won't budge.\n");
    return 1;
}

public int
prevent_close_door()
{
    write("The door won't budge.\n");
    return 1;
}
