/* Creative rights reserved to Mecien (Jeff Babcock) and team. */
inherit "/std/object";

#include <macros.h>
#include <stdproperties.h>

#define MIN_DUR 1
#define MAX_DUR 10000

public void
create_object()
{
    set_name("ghost_object");
    set_no_show();
    add_prop(OBJ_M_NO_DROP, 1);
}

public void
set_duration(int dur)
{
    if (dur < MIN_DUR) dur = MIN_DUR;
    if (dur > MAX_DUR) dur = MAX_DUR;
    set_alarm(itof(dur), -1.0, remove_object);
}

public void
enter_env(object to, object from)
{
    ::enter_env(to, from);
    
    if (!to || !living(to)) return;
    
    tell_room(environment(to), "A spectral image arises.\n", to);
    to->set_ghost(1);
}

public void
leave_env(object from, object to)
{
   ::leave_env(from, to);
   
   if (!from || !living(from)) return;
   
   tell_room(environment(from), QCTNAME(from) +
             " glows with a pale light and begins to take shape.\n", from);
   from->catch_msg("You return to the land of the living.\n");
   from->set_ghost(0);
}

