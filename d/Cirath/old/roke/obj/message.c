/*
 * message.c
 *
 * Used in npc/pigeon.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Cirath by Glindor, Jan 2000.
 */

#pragma save_binary
#pragma strict_types

inherit "/std/object";

#include <stdproperties.h>
#include <macros.h>

string gMessage, gSender;

void
create_object()
{
    set_name("message");
    set_pname("messages");
    set_short("message");
    set_pshort("messages");
    set_long("@@read_message");
    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 100);
    add_prop(OBJ_I_NO_DROP, "@@do_destruct");
    gMessage = "Nothing.\n";
    gSender = "Someone";
}

string
read_message()
{
    return ("The message reads:\n" + gMessage);
}

int
do_read(string str)
{
    if (str == "message" || str == short())
    {
        write(read_message());
        return 1;
    }
    return 0;
}

void
init()
{
    ::init();
    add_action(do_read, "read");
}

void
destruct_me()
{
    object room;
    if (living(room = environment()))
        room = environment(room);
    tell_room(room, "The message blows away with the wind.\n");
    remove_object();
}

int
do_destruct()
{
    set_alarm(2.0, 0.0, destruct_me);
    return 0;
}

void
set_message(string str)
{
    gMessage = str;
}

void
set_sender(string str)
{
    gSender = capitalize(str);
    set_short("message from " + gSender);
    set_pshort("messages from " + gSender);
}

string
query_sender()
{
    return gSender;
}
