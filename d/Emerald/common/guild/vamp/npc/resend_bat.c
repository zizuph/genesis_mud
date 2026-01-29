#include "../guild.h"

inherit VAMP_NPC_DIR + "bat_base";

#include "../bat_manager.h"
#include <filter_funs.h>

int messenger_id = -1;

void create_delivery_bat()
{
    set_long("A black bat which seems to be under your control.\n" +
        "It is currently carrying a message for @@receiver_name@@.  " +
        "You can attempt to \"resend\" the message if you desire.\n");
}

string
receiver_name()
{
    return capitalize(BAT_MANAGER->query_message_data(messenger_id, 
        RECEIVER_NAME));
}

int
resend(string str)
{
    if (strlen(str))
    {
        return 0;
    }

    write("You give your message to the bat.\n");
    tell_room(environment(this_player()), ({
        this_player()->query_Met_name() + " gives a message to" +
            " a black bat.\n",
        "The " + this_player()->query_nonmet_name() + " gives a message" +
            " to a black bat.\n",
        "" }), this_player());

    BAT_MANAGER->resend(this_object(), this_player(), messenger_id);

    return 1;
}
        
void
init_living()
{
    ::init_living();
    add_action(resend, "resend");
}

void set_messenger_id(int id) { messenger_id = id; }

void
goto_dest(object sender)
{
    object env = environment(sender);
    object *ppl;

    sender->catch_tell("Your black bat returns to you, unable to find " +
        receiver_name() + ".\n");

    if (env)
    {
        ppl = FILTER_CAN_SEE_IN_ROOM(
            FILTER_PLAYERS(all_inventory(environment(sender)))) - ({ sender });
        ppl->catch_msg("A black bat flies up to " + QTNAME(sender) + ".\n");
    }

    move(sender, 1);
}

int
query_messenger_id()
{
    return messenger_id;
}
