inherit "/d/Rhovanion/lib/room";
#include "/d/Rhovanion/farlong.h"

void
add_guard(string type)
{
    object guard;

    reset_euid();

    guard = clone_object(RHUN + "npc/guard");
    guard->add_name(type);
    guard->move(TO, 1);
}

void
reset_room()
{
    if (!present("_guard1", TO))
        add_guard("_guard1");

    if (!present("_guard2", TO))
        add_guard("_guard2");

    if (!present("_guard3", TO))
        add_guard("_guard3");

    if (!present("_guard4", TO))
        add_guard("_guard4");
}
