/*
 * A standard scroll of the type delivered by dragons, pigeons, couriers, etc.
 *
 * Simply clone this object, and use the set_sender() and set_message()
 * methods.
 */
#pragma save_binary
#pragma strict_types

inherit "/std/object";

#include <stdproperties.h>
#include <macros.h>
#include "/d/Khalakhor/sys/basic.h"

string gMessage, gSender;

public string read_message();

public void
create_object()
{
    set_name("scroll");
    set_adj("paper");
    set_long("An empty scroll.\n");
    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 100);
    gMessage = "Nothing.\n";
    gSender = "Someone";
}

public void
set_message(string str)
{
    gMessage = str;
    set_long(read_message());
}

public void
set_sender(string str) 
{
    gSender = str;
    set_short("scroll from " + capitalize(str));
    set_pshort("scrolls from " + capitalize(gSender));
}

public string
query_sender()
{
    return gSender;
}

public string
read_message()
{
    return sprintf("%'-'79s\n The scroll contains this message "+
      "from "+gSender+":\n%'-'79s\n" +
	"%s\n%'-'79s\n", "", "", gMessage, "");
}

public mixed
command_read(int m)
{
    if (m)
    {
        this_player()->more(read_message());
    }
    else
    {
        write(read_message());
    }

    return 1;
}

public void
destruct_me()
{
    object room;
 
    if (living(room = environment()))
    {
        room = environment(room);
    }
 
    tell_room(room, "The scroll mysteriously bursts into "+
      "flames and disappears.\n");
    remove_object();
}

public void
enter_env(object to, object from)
{
    ::enter_env(to, from);

    /* If the scroll is moved out of the living into a non-living environment,
     * this could be a room or a container, then we destroy the scroll. First
     * we change some of its properties so people don't see the name of the
     * author, or can pick it up. */
    if (!living(to))
    {
        set_adj("inscribed");
        set_short("inscribed scroll");
        set_pshort("inscribed scrolls");
        add_prop(OBJ_I_NO_GET, 1);

        set_alarm(1.0, 0.0, destruct_me);
    }
}
