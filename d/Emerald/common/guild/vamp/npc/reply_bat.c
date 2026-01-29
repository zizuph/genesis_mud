#include "../guild.h"

inherit VAMP_NPC_DIR + "bat_base";

#include "../bat_manager.h"
#include <filter_funs.h>

int messenger_id = -1;

void
create_delivery_bat()
{
    set_long("A black bat which seems to be controlled by someone.\n" +
             "It carries a message for you, which can be replied to--" +
             "simply \"send reply to <sender name>\".\n");
}
         
void
goto_dest(object receiver)
{
    object message_ob;
    object env = environment(receiver);
    object *ppl;

    tell_object(receiver, 
        "A black bat flies up to you, and you retrieve a message from it.\n");

    ppl = FILTER_CAN_SEE_IN_ROOM(FILTER_PLAYERS(all_inventory(
        environment(receiver)))) - ({ receiver });
    ppl->catch_msg("A bat flies to " + QTNAME(receiver) + ", and " +
        receiver->query_pronoun() + " retrieves a message from it.\n");

    move(receiver, 1);
    
    message_ob = clone_object("/d/Genesis/obj/message");
    message_ob->set_message(
        BAT_MANAGER->query_message_data(messenger_id, MESSAGE));
    message_ob->set_sender(
        BAT_MANAGER->query_message_data(messenger_id, SENDER_NAME));
    message_ob->move(receiver, 1);
}

void set_messenger_id(int id) 
{
    string name;

    messenger_id = id;

    name = BAT_MANAGER->query_message_data(messenger_id, SENDER_NAME);

    set_long("A black bat which seems to be controlled by " + name + ".\n" +
        "It carries a message for you, which can be replied to--" +
        "simply \"send reply to " + lower_case(name) + "\".\n");

}

void
send_mail(string message)
{
    if (!strlen(message))
    {
        write("Message aborted.\n");
        return;
    }

    write("You give your message to the bat.\n");
    tell_room(environment(this_player()), ({
        this_player()->query_Met_name() + " gives a message to" +
            " a black bat.\n",
        "The " + this_player()->query_nonmet_name() + " gives a message" +
            " to a black bat.\n",
        "" }), this_player());

    BAT_MANAGER->reply(this_object(), this_player(), message, messenger_id);
}

int
reply(string str)
{
    string name;

    if (this_player() != environment())
    {
        return 0;
    }

    if (!strlen(str) || !wildmatch("reply to *", str))
    {
        return 0;
    }

    str = lower_case(str[9..]);

    name = lower_case(BAT_MANAGER->query_message_data(messenger_id,
        SENDER_NAME));

    if (name != str)
    {
        notify_fail("Send reply to whom?\n");
        return 0;
    }

    write_message(send_mail);

    return 1;
}

void
init_living()
{
    ::init_living();
    add_action(reply, "send");
}

int
query_messenger_id()
{
    return messenger_id;
}
