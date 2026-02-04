/* Creative rights reserved to Mecien (Jeff Babcock) and team. */
/* This is a magic lighter, that lights up the room. It's cloned by the
 * light spell, and should never be seen by players.
 */
inherit "/std/object";

#include <stdproperties.h>

#define MIN_DUR 10
#define MAX_DUR 3000

public void
create_object()
{
    set_name("light");
    set_adj("sacred");
    set_no_show();
    add_prop(OBJ_I_LIGHT, 5);
    add_prop(OBJ_M_NO_GET, 1);
    add_prop(OBJ_M_NO_GIVE, 1);
}

public void
set_duration(int dur)
{
    if (dur < MIN_DUR) dur = MIN_DUR;
    if (dur > MAX_DUR) dur = MAX_DUR;
    set_alarm(itof(dur), -1.0, remove_object);
}

public void
enter_env(object dest, object old)
{
    ::enter_env(dest, old);
    
    if (dest && dest->query_prop(ROOM_I_IS))
        tell_room(dest, "A radiant light fills this place.\n");
}

public void
leave_env(object old, object dest)
{
    ::leave_env(old, dest);
    
    if (old && old->query_prop(ROOM_I_IS))
        tell_room(old, "The light seems to fade away.\n");
}

