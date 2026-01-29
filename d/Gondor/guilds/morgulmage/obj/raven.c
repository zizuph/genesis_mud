/*
 *  Carrier raven for the Morgul Mages.
 *
 *  Olorin, 5-jan-1994
 *  Converted to the generic messenger by Eowul, Februari 2009
 */

#pragma save_binary

inherit "/std/messenger";

#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include "/d/Gondor/defs.h"

public void create_messenger()
{
    set_name("raven");
    set_pname("ravens");
    set_race_name("raven");
    set_adj("black");
    set_short("black raven");
    set_pshort("black ravens");
    set_long("This is a black raven, which you can use to send messages "
        + "to other players with 'send <player>'.\n");
    set_alignment(-100);

    set_can_deliver_indoors(0);
    set_can_deliver_unmet(0);
    set_number_of_uses(3);   
}

public void
hook_send_message()
{    
    write("You give your message to " + LANG_THESHORT(this_object()) + ". "
        + capitalize(this_object()->query_pronoun()) + " flaps its wings and "
        + "flies up to the sky.\n");
    say(QCTNAME(this_player()) + " gives a message to " + QTNAME(this_object())
        + ". " + capitalize(this_object()->query_pronoun()) + " flaps its wings and "
        + "flies up to the sky.\n");
}

public void
hook_resend_message()
{    
    hook_send_message();
}

public void
hook_deliver_message_failure(object sender)
{
    sender->catch_tell("Your " + this_object()->short() 
        + " returns, unable to find " + capitalize(gReceiver) + ". It lands "
        + "on your shoulder and you retrieve your message.\n");
        
    tell_room(environment(sender), QCTNAME(this_object()) + " lands on "
        + QTNAME(sender) + "'s should and gives " + sender->query_objective()
        + " a message.\n", ({ sender }));           
}

public void
hook_deliver_message_success(object receiver)
{
    receiver->catch_msg(QCTNAME(this_object()) + " descends from the sky, "
        + "lands on your shoulder and gives you a message.\n");
        
    tell_room(environment(receiver), QCTNAME(this_object()) + " lands on "
        + QTNAME(receiver) + "'s should and gives " + receiver->query_objective()
        + " a message.\n", ({ receiver }));  
}

public void
hook_messenger_returns_home()
{
    object room;
    if (living(room = environment()))
    {
        room = environment(room);
    }
    
    tell_room(room, QCTNAME(this_object()) + " flaps it's wings and "
        + "flies up into the sky.\n");
}
