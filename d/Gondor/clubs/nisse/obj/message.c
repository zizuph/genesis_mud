/*
 *  /d/Gondor/clubs/nisse/obj/message.c
 *
 *  The message that is delivered by the hawk of Nisse Ohtar.
 *  It's not used since the hawks cannot carry the messages.
 *
 *  Big part of this code has been taken from the Eil-Galaith scroll.
 *  Deagol, March 2003
 */

#pragma save_binary
#pragma strict_types

inherit "/std/object";

#include <stdproperties.h>
#include <macros.h>

string gMessage, gSender;

public string read_message();

public void
create_object()
{
    set_name("message");
    set_long("An empty message.\n");
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
    set_short("message from " + capitalize(str));
    set_pshort("messages from " + capitalize(gSender));
}

public string
query_sender()
{
    return gSender;
}

public string
read_message()
{
    return sprintf("%'-'76s\n The message reads this:\n%'-'76s\n" +
        "%s\n%'-'76s\n", "", "", break_string(gMessage, 76, 2), "");
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

    tell_room(room, "The message blows away with the wind.\n");
    remove_object();
}

public void
leave_env(object env, object to)
{
    ::leave_env(env, to);

    if (env)
    {
        set_alarm(0.5, 0.0, destruct_me);
    }
}
