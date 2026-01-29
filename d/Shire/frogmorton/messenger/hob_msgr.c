/*
 * Frogmorton Hobbit Messenger
 *
 * Based on ~shire/misty/obj/post_rat.c
 * See that file for the history of this file.
 * -- Finwe 2002
 * 
 * Converted December 2008 to use standard messenger object
 */

inherit "/std/messenger";

#include "/d/Shire/sys/defs.h"
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include "../defs.h"
  
public void 
create_messenger()
{
    set_name("hobbit");
    add_name("bounder");
    add_name("hobbit messenger");
    add_name("messenger");
    set_pname("hobbit messengers");
    set_gender(random(2));
    set_adj(({"adventuresome"}));
    set_short("adventuresome hobbit messenger");
    set_pshort("adventuresome hobbit messengers");
    set_long("This is an apprentice Bounder from Frogmorton. "+
        CAP(HE_SHE(TP))+ " is learning how to be a member of the Watch, " +
        "the Shirriffs of the Shire. As one of their jobs, they " +
        "must learn their way around by delivering notes. To send " +
        "a message, simply 'send [player]'.\n");
 
    add_prop(OBJ_I_WEIGHT,  1000);
    add_prop(CONT_I_WEIGHT, 1500);
    add_prop(OBJ_I_VOLUME,  2000);
    add_prop(CONT_I_VOLUME, 2000);
    add_prop(OBJ_I_NO_GET, 0);
    add_prop(NPC_I_NO_LOOKS, 1);
    add_prop(OBJ_I_NO_DROP, 0);
    add_prop(LIVE_I_NON_REMEMBER, 1);
    add_prop(NPC_M_NO_ACCEPT_GIVE, " doesn't want anything from " +
        "you, "+HE_SHE(TP)+" just wants to end this adventure " +
        "and go home.\n");

    set_act_time(30+random(60));
    add_act("emote tugs on your sleeve and says: I want to go home!");
    add_act("say I have seen so much on my travels today!");
    add_act("say Where are we headed to now?");
    add_act("say This is so much fun.");
    add_act("say I really should be headed home soon.");
    
    // Set Messaging Options
    set_can_deliver_indoors(1);
    set_can_deliver_unmet(1);
    set_number_of_uses(0);    
}

/*
 * Function:    query_delivery_time
 * Description: This function defines the basic times that it usually
 *              takes to deliver a message.
 * Arguments:   sender - person sending the message
 *              receiver - person receiving the message
 * Returns:     The number of seconds until the receiver receives the
 *              message
 */
public int
query_delivery_time(object sender, object receiver)
{
    if (!objectp(sender) || !objectp(receiver))
    {
        return 60 + random(60);
    }
    
    if (environment(sender) == environment(receiver))
    {
        return random(5);
    }
    
    if (explode(MASTER_OB(environment(sender)), "/")[2] ==
        explode(MASTER_OB(environment(receiver)), "/")[2])
    {
        return 60 + random(30);
    }
    
    return 60 + random(60);
}

/*
 * Function:    hook_cannot_deliver_unmet
 * Description: Hook that gets called to display that the messenger cannot
 *              deliver to someone who has not been introduced to the
 *              sender.
 * Arguments:   who - the person the sender is trying to send to
 * Returns:     nothing
 */
public void
hook_cannot_deliver_unmet(string who)
{
    notify_fail("You do not remember being introduced to anyone named " +
        capitalize(who) + ".\n");    
}
 
public void
hook_messenger_returns_home()
{
    object room;
    
    if (living(room = environment()))
        room = environment(room);

    tell_room(room, QCTNAME(this_object()) + " says: 'Thanks for the adventure, "
        + "it was fun!', and runs off.\n");
}
