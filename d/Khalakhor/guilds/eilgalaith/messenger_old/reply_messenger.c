/**********************************************************************
 * - reply_messenger.c                                              - *
 * - A Tiny Elven Nymph Dragon                                      - *
 * - There are three messengers, messenger.c, reply_messenger.c,    - *
 * - resend_messenger.c                                             - *
 * - Recoded by Damaris 2/2002                                      - *
 **********************************************************************/
#include "../guild.h"

inherit MESSENGER_BASE;

#include "messenger_manager.h"
#include <const.h>
#include <files.h>
#include <filter_funs.h>
#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>

int messenger_id = -1;

void
create_delivery_messenger()
{
    set_short("tiny elven nymph dragon");
    set_long("This is a " + short() + ". She sits comfortably on "+
      "your shoulder, with her long tail tickling the side of your "+
      "neck just waiting for you to write a message.\n"+
      "Simply 'send <receiver name>'.\n");
}
     
void
goto_dest(object receiver)
{
    object message_ob;
    object env = environment(receiver);
    object *ppl;

    tell_object(receiver, 
        "A " + short() + " mysteriously appears, lands on your "
    		+ "shoulder tickling your neck with her tail "+
    		"and you retrieve a scroll from her.\n");

    ppl = FILTER_CAN_SEE_IN_ROOM(FILTER_PLAYERS(all_inventory(
        environment(receiver)))) - ({ receiver });
    ppl->catch_msg("A " + short() + " mysteriously appears "+
      "to " + QTNAME(receiver) + ", and " +
        receiver->query_pronoun() + " retrieves a scroll from her.\n");

    move(receiver, 1);
    
    setuid();
    seteuid(getuid());
    message_ob = clone_object("/d/Khalakhor/guilds/eilgalaith/messenger/message");
    message_ob->set_message(
        MESSENGER_MANAGER->query_message_data(messenger_id, MESSAGE));
    message_ob->set_sender(
        MESSENGER_MANAGER->query_message_data(messenger_id, SENDER_NAME));
    message_ob->move(receiver, 1);
}

void set_messenger_id(int id) 
{
    string name;

    messenger_id = id;

    setuid();
    seteuid(getuid());

    name = MESSENGER_MANAGER->query_message_data(messenger_id, SENDER_NAME);

    set_long("A " + short() + " which is eager to "+
      "assist " + name + ".\n" +
        "She carries a scroll for you, which can be replied to by "+
        "simply 'send reply to " + lower_case(name) + "'.\n");

}

void
send_mail(string message)
{
    if (!strlen(message))
    {
        write("Message aborted.\n");
        return;
    }

    write("You give your scroll to the " + short() + ".\n");
    tell_room(environment(this_player()), ({
        this_player()->query_Met_name() + " gives a scroll to" +
            " a " + short() + ".\n",
        "The " + this_player()->query_nonmet_name() + " gives a scroll" +
            " to a " + short() + ".\n",
        "" }), this_player());

    MESSENGER_MANAGER->reply(this_object(), this_player(), message, messenger_id);
         
    return;
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

    name = lower_case(MESSENGER_MANAGER->query_message_data(messenger_id,
        SENDER_NAME));

    if (name != str)
    {
        notify_fail("Send reply to whom?\n");
        return 0;
    }

    write_message(send_mail);

    return 1;
}
int
return_messenger(string str)
{
   if(!strlen(str))
      {
      write("Return what?\n");
      return 0;
      }
   if((str == "dragon")|| (str == "nymph dragon") || (str == "messenger"))
      {
   write("You whisper softly to the " + short() + " and tell her "+
   "she may return.\nThe " + short() + " tickles you with her tail then "+
   "mysteriously disappears.\n");
      
          /* This what others in room see. */
   say(QCTNAME(TP)+" whispers softly to a " + short() + " and she "+
     "mysteriously disappears.\n");
    destruct();
      }
    return 1;
}
void
init_living()
{
    ::init_living();
    add_action(reply, "send");
    add_action(return_messenger, "egreturn");
}

int
query_messenger_id()
{
    return messenger_id;
}
