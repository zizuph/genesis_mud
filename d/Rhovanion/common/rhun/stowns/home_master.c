inherit "/d/Rhovanion/lib/room";
#include "/d/Rhovanion/farlong.h"

reset_room()
{
    reset_euid();

    if (!present("_poorwoman", TO))
    {
        object woman;
        woman = clone_object(RHUN + "npc/poorwoman");
        woman->add_name("_poorwoman");
        woman->move(TO, 1);
    }

    if (!present("_poorchild", TO))
    {
        object child;
        child = clone_object(RHUN + "npc/poorchild");
        child->add_name("_poorchild");
        child->move(TO, 1);
    }
}

