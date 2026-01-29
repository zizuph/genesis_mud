inherit "/d/Gondor/common/room";

#include "/d/Gondor/defs.h"

#define ROOM1		"/d/Gondor/olorin/workroom"
#define ROOM2		"/d/Gondor/fingolfin/workroom"

void
create_room()
{
    set_short("An interesting room");
    set_long("@@long_desc");

    add_exit(ROOM1, "south", "@@leave_room", 0);
    add_exit(ROOM2, "north", "@@leave_room", 0);
}

string
long_desc()
{
    string  from_dir;
    switch(TP->query_prop("_entered_from"))
    {
        case "north":
            from_dir = "from the north";
            break;
       case "south":
            from_dir = "from the south";
            break;
       default:
            from_dir = "nowhere";
            break;
    }
    return "You entered this room "+from_dir+"!\n";
}

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if (!objectp(from) || !objectp(ob) || !living(ob))
        return;

    if (from == find_object(ROOM1))
        ob->add_prop("_entered_from", "north");
    else if (from == find_object(ROOM2))
        ob->add_prop("_entered_from","south");
}

int
leave_room()
{
    TP->remove_prop("_entered_from");
    return 0;
}
