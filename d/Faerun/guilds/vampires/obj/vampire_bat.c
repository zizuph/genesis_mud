/*
 *  Carrier vampire bat for the Fire Vampires.
 *
 *  Based on Olorin's raven, 5-jan-1994, also
 *  used by Eowil for new MM.
 *
 *  Borrowed by Nerull 2021.
 */

#pragma save_binary

inherit "/std/messenger";

#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include "/d/Faerun/defs.h"

public void create_messenger()
{
    set_name("bat");
    set_pname("bats");
    set_race_name("bat");
    set_adj("brown");
    add_adj("long-eared");
    set_short("brown long-eared bat");
    set_pshort("brown long-eared bats");
    
    set_gender(2);
    
    set_long("Long ears and even longer fangs, this vampire bat serves as a messenger for its master. "
        + "It is small with brown fur and has wide, nearly translucent wings. It will deliver messages "
        + "with 'send <player>'.\n");
        
    set_alignment(-10);

    set_can_deliver_indoors(1);
    set_can_deliver_unmet(1);
    set_number_of_uses(5);   
}


public void
hook_send_message()
{    
    write("You give your message to " + LANG_THESHORT(this_object()) + ". "
        + capitalize(this_object()->query_pronoun()) + " flaps its wings silently and "
        + "flies away.\n");
        
    say(QCTNAME(this_player()) + " gives a message to " + QTNAME(this_object())
        + ". " + capitalize(this_object()->query_pronoun()) + " disappears with a few silent "
        + "flaps of its wings.\n");
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
        + " returns, unable to find " + capitalize(gReceiver) + ". It hangs"
        + "upside down on your chest allowing you to retrieve your message.\n");
        
    tell_room(environment(sender), QCTNAME(this_object()) + " hangs upside down on "
        + QTNAME(sender) + "'s chest, allowing " + sender->query_objective()
        + " to retrieve a message.\n", ({ sender }));           
}


public void
hook_deliver_message_success(object receiver)
{
    receiver->catch_msg(QCTNAME(this_object()) + " screeches menacingly as it lands on your head. "
        + "You are careful to avoid those large fangs as you retrieve a message.\n");
        
    tell_room(environment(receiver), QCTNAME(this_object()) + " screeches menacingly, landing on "
    + QTNAME(receiver) + "'s head, allowing " + receiver->query_objective()+ " to carefully retrieve "
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
    
    tell_room(room, QCTNAME(this_object()) + " flaps its wings silently and flies away.\n");
}
