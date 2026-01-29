/**********************************************************************
 * - messenger.c                                                    - *
 * - This is the delivery_messenger                                 - *
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

void
create_delivery_messenger()
{
    set_short("tiny elven nymph dragon");
    set_long("This is a " + short() + ". She sits comfortably on "+
      "your shoulder, with her long tail tickling the side of your "+
      "neck just waiting for you to write a message upon a scroll. Simply "+
      "'send <receiver name>'.\n");
}

void
send_mail(string message, string name)
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

    MESSENGER_MANAGER->send(this_object(), this_player(), name, message);
         
    return;
}

int
do_send(string who)
{
    int reply;

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

    sender->catch_tell("A " + short() + " mysteriously appears, lands on your "
    		+ "shoulder tickling your neck with her tail "+
    		"and gives you a scroll from " + QTNAME(sender) + ".\n");

    if (env)
    {
        ppl = FILTER_CAN_SEE_IN_ROOM(
            FILTER_PLAYERS(all_inventory(environment(sender)))) - ({ sender });
        ppl->catch_msg("A " + short() + " mysteriously appears to"+
          "" + QTNAME(sender) + ".\n");
    }

    move(sender, 1);
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
    add_action(do_send, "send");
    add_action(return_messenger, "egreturn");
}
