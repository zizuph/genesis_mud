inherit "/std/door";

#include "../defs.h"
#include <stdproperties.h>

void
create_door()
{
    set_door_desc("This is a large steel door. It seems quite sturdy.\n");
    set_open_mess(({"pulls on the handle of the cell door.\n", "The door " +
                    "quickly swings open on its silent hinges.\n"}));
    set_close_mess("swings the cell door closed.\n");
    set_fail_open(({"tries to open the already open door.", "pulls on the " +
                  "handle of the cell door, but it does not budge.\n"}));
    set_open(0);
    set_locked(1);
    set_no_pick();
}   

void
load_other_door()
{
    string *door_ids;
    object *doors;
    int pos;

    seteuid(getuid());

    if (!strlen(other_room) || other_door)
    {
        return;
    }

    if (!find_object(other_room))
    {
        other_room->teleledningsanka();
        if (!find_object(other_room))
        {
            remove_door_info(environment(this_object()));
            remove_object();
            return;
        }
    }

    door_ids = (string *)other_room->query_prop(ROOM_AS_DOORID);
    doors = (object *)other_room->query_prop(ROOM_AO_DOOROB);
    pos = member_array(file_name(environment()), door_ids);
    if (pos < 0)
    {
        write("Other side of door is not in room after it has been loaded: " +
                other_room + ".\n");
        remove_door_info(environment(this_object()));
        remove_object();
        return;
    }

    other_door = doors[pos];
}
