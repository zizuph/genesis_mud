/*
 * /d/Gondor/guilds/rangers/obj/message.c
 *
 * The message sent by Rangers.
 *
 * Gwyneth, July 1, 2001
 */
inherit "/std/object";

#include <cmdparse.h>
#include <files.h>
#include <stdproperties.h>

#include "../rangers.h"

/* Global variables */
static string gMessage, gSender;

public string
long_desc()
{
    int sender_level, receiver_level;
    string desc; 

    sender_level = MANAGER->query_ranger_level(gSender);
    receiver_level = MANAGER->query_ranger_level(
        this_player()->query_real_name());

    if (receiver_level > APPROVED_APP_LEVEL && sender_level > 0)
        desc = "You recognize the writing of your fellow Ranger, " +
            gSender + ". You may 'read', 'tear' or 'destroy' this message.\n";
    else if (receiver_level > 0 && !sender_level)
        desc = "The message is from " + gSender + ". You may 'read', " +
            "'tear' or 'destroy' this message.\n";
    else
        desc = "You may read this message.\n";

    return desc;
}

public void
create_object()
{
    set_name("message");
    set_short("message");
    set_long(&long_desc());
    add_prop(OBJ_I_WEIGHT, 1);
    add_prop(OBJ_I_VOLUME, 2);
}

public void
set_message(string message)
{
    if (extract(message, -1) != "\n")
        message += "\n";

    gMessage = message;
}

public void
set_sender(string sender)
{
    gSender = capitalize(sender);
}

public int
read_message(string str)
{
    int sender_level, receiver_level;
    mixed *message;
    string desc;

    sender_level = MANAGER->query_ranger_level(gSender);
    receiver_level = MANAGER->query_ranger_level(
        this_player()->query_real_name());

    if (!strlen(str))
        return 0;

    message = FIND_STR_IN_OBJECT(str, this_player());

    if (!sizeof(message))
    {
        message = FIND_STR_IN_OBJECT(str, environment(this_player()));
        if (!sizeof(message))
        {
            notify_fail(capitalize(query_verb()) + " what?\n");
            return 0;
        }

        write("The message is too far away to read.\n");
        return 1;
    }

    if (message[0] == this_object())
    {
        if (receiver_level > APPROVED_APP_LEVEL && sender_level > 0)
            desc = ("You recognize the writing of your fellow Ranger, " +
                gSender + ". You read the message:\n" + gMessage +
                "\n\nYou may 'tear' or 'destroy' this message.\n");
        else if (receiver_level > 0 && !sender_level)
            desc = ("The message is from " + gSender + ". You read " +
                "the message:\n" + gMessage + "\n\nYou may 'tear' or " +
                "'destroy' this message.\n");
        else
            desc = ("You read the message:\n" + gMessage);

        write(desc);
        return 1;
    }
    else
    {
        notify_fail(capitalize(query_verb()) + " what?\n");
        return 0;
    }
}

private int
tear_message(string str)
{
    mixed *message = FIND_STR_IN_OBJECT(str, this_player());

    if (!sizeof(message))
    {
        notify_fail(capitalize(query_verb()) + " what?\n");
        return 0;
    }
    if (message[0] == this_object())
    {
        write("You discreetly tear up the " + short() + " and discard it.\n");
        set_alarm(0.1, 0.0, &remove_object());
        return 1;
    }
    else
    {
        notify_fail(capitalize(query_verb()) + " what?\n");
        return 0;
    }
}

void
destruct_me(object room)
{
    tell_room(room, "The message blows away with the wind.\n");
    remove_object();
}

void
enter_env(object dest, object old)
{
    ::enter_env(dest, old);

    if (!IS_ROOM_OBJECT(dest))
        return;

    add_prop(OBJ_M_NO_GET, "The message is blown out of your grasp " +
        "by the wind.\n");
    set_alarm(rnd(), 0.0, &destruct_me(dest));
    return;
}

public void
init()
{
    ::init();

    add_action(read_message, "read");
    add_action(read_message, "study");
    add_action(tear_message, "tear");
    add_action(tear_message, "destroy");
}
