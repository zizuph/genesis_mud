/* Creative rights reserved to Mecien (Jeff Babcock) and team. */
/* This is a magic lightener/darkener, that lightens/darkens the room.
 * It's cloned by the LoD dark "spell", and should never be seen by
 * the players.
 */
inherit "/std/object";

#include <stdproperties.h>

#define TO        this_object()
#define ETO       environment(TO)
#define MAX_DUR   3000
#define ENTER_MSG "A startling darkness fills this place."
#define LEAVE_MSG "The darkness seems to disperse."

int light_val=1;
string enter_msg=ENTER_MSG, leave_msg=LEAVE_MSG;

public void
set_enter_msg(string msg)
{
    enter_msg = msg;
}

public void
set_leave_msg(string msg)
{
    leave_msg = msg;
}

public void
set_light_value(int val)
{
    light_val = val;
}

public int
my_val()
{
    return light_val;
}

public void
create_object()
{
    set_name("darkness");
    set_adj("evil");
    set_no_show();
    add_prop(OBJ_I_LIGHT, "@@my_val");
    add_prop(OBJ_I_NO_GET, 1);
}

public void
set_duration(int dur)
{
    if (dur < 0) return;
    if (dur > MAX_DUR) dur = MAX_DUR;
    set_alarm(itof(1 + dur), -1.0, remove_object);
}

public void
enter_env(object dest, object old)
{
    ::enter_env(dest, old);
    if (!dest || !dest->query_prop(ROOM_I_IS)) return;

    if (strlen(enter_msg))
        tell_room(dest, enter_msg);
}

public void
leave_env(object old, object dest)
{
    ::leave_env(old, dest);
    if (!old || !old->query_prop(ROOM_I_IS)) return;

    if (strlen(leave_msg))
        tell_room(dest, leave_msg);
}
