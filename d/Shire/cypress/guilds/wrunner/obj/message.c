/*

 * Message for Wild Elf messengers. Modified from Ranger's message file
 * by Gwyneth
 * -- Finwe, March 2005
 */
inherit "/std/object";

#include "/d/Shire/cypress/sys/defs.h"
#include "/d/Shire/cypress/guilds/wrunner/wrunner_defs.h"
#include <cmdparse.h>
#include <files.h>
#include <stdproperties.h>

/* Global variables */
static string gMessage, gSender;

public string
long_desc()
{
    string desc;

    desc = "The message is from " + gSender + ". You may 'read', " +
            "'tear' or 'destroy' this message.\n";

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
    mixed *message;
    string desc;


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
        desc = ("\nThis message is from " + gSender + ":\n" +
"==============================================================================\n\n" +
            gMessage + "\n" +
"==============================================================================\n" +
            "You may 'tear' or 'destroy' this message.\n");

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
        write("You tear up the " + short() + " and discard it.\n");
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
