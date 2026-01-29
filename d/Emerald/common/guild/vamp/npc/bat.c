#include "../guild.h"

inherit VAMP_NPC_DIR + "bat_base";

#include "../bat_manager.h"
#include <filter_funs.h>

void create_delivery_bat()
{
    set_long("A black bat which seems to be under your control.\n" +
         "You could use it to send a message to far away lands--" +
         "simply \"send <receiver name>\".\n");
}

void
send_mail(string message, string name)
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

    BAT_MANAGER->send(this_object(), this_player(), name, message);
}

int
do_send(string who)
{
    if (!strlen(who))
    {
        return 0;
    }

    if (this_player() != environment())
    {
        return 0;
    }

    write_message(send_mail, who);

    return 1;
}

void
goto_dest(object sender)
{
    object env = environment(sender);
    object *ppl;

    sender->catch_tell("A black bat flies up to you.\n");

    if (env)
    {
        ppl = FILTER_CAN_SEE_IN_ROOM(
            FILTER_PLAYERS(all_inventory(environment(sender)))) - ({ sender });
        ppl->catch_msg("A black bat flies up to " + QTNAME(sender) + ".\n");
    }

    move(sender, 1);
}

void
init_living()
{
    ::init_living();
    add_action(do_send, "send");
}
