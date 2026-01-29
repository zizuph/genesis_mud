// Avenirian brand of 'pigeon'
// if players give the 'child' things, it runs away with them.
// Modification Log:
// 26 Feb, 1999 Lilith:  commented-out the sublocs.
// 17 January, Cirion:   Made the child take longer if it
//    has to travel to another domain to deliver the message.
// 01 Dec 1997, Lilith: Children can deliver messages to people not 
//    in player memory. Rationale? These are children. Thay can ask
//    questions to find who they are looking for.
// N.B. The child will not deliver objects. If an object is given
//    to the child, it will run away, and the sender will
//    lose both the object and the child.
// Lilith May 2022: put a limit on how many other messengers can be
//    in a place with it before they run away. 

#pragma strict_types

inherit "/std/monster";
inherit "/lib/messenger";

#include "/d/Avenir/common/bazaar/bazaar.h"
#include <flags.h>

#define FAST		random(20) + 20
#define SLOW		random(20) + 40
// Number of times the child will deliver messages
// before it becomes too tired.
#define TIMES		(5 + random(5))

/*
 * Global variables:
 */
static int     times = TIMES; 

private string *randomname =
	({"child","waif", "messenger", "urchin", "orphan"});
private string *randomadj =
	({"plaintive", "sad", "skinny", "smiling", "tiny", "frail"});

/*
 * Function name: create_monster
 * Description:   Create the monster. (standard)
 */
void
create_monster()
{
    ::create_monster();

    // Sets the defaults for any messenger. It calls create_messenger.
    // Must call this before set_short and set_long
    init_messenger();
}

/*
 * Function:    create_messenger
 * Description: Set all the options in this function. It overrides the
 *              defaults set in init_messenger since it is the last
 *              function called by init_messenger.
 */
public void
create_messenger()
{
    set_name(randomname[random(sizeof(randomname))]);
    set_adj(randomadj[random(sizeof(randomadj))]);
    set_gender(random(2));
    add_name(({"child", "waif", "messenger", "urchin", "orphan"}));
    add_name("_bazaar_messenger");
    set_pname(({"waifs", "messengers", "urchins", "children"}));
    set_race_name("human");
    set_short(query_adj() + " " + lower_case(query_name()));
    set_pshort(query_adj()+ " " +query_pname());
    set_long("This "+ short() +" is the orphan of Sybarite "+
        "slaves.\n"+ capitalize(this_object()->query_pronoun()) +
        " earns "+ this_object()->query_possessive() +" food and "+
        "a corner to sleep in by running messages for "+ 
        this_object()->query_possessive() +" master or mistress.\n"+
        "Write your letter using: 'send <name>' or 'send reply' "+
        "and then the child will deliver it for you.\n"+
        "When you want the child to go away, just <dismiss child>.\n");
    
    NEVERKNOWN;
    remove_prop(OBJ_I_NO_GET);
    remove_prop(OBJ_I_NO_DROP);
    add_prop(LIVE_I_NON_REMEMBER,1);
    remove_prop(NPC_M_NO_ACCEPT_GIVE);
    add_prop(OBJ_I_WEIGHT,  1000);
    add_prop(CONT_I_WEIGHT, 1500);
    add_prop(OBJ_I_VOLUME,  2000);
    add_prop(CONT_I_VOLUME, 2000);
    add_prop(OBJ_M_NO_ATTACK, "On second thought, maybe just <dismiss "+
        "child> instead?\n");   
    set_can_deliver_indoors(1);
    set_can_deliver_unmet(1);
    set_message_object_file("/d/Avenir/common/bazaar/Obj/misc/letter");
    set_number_of_uses(TIMES);            
}

/* 
 * Function name: enter_inv
 * Description:   Called when objects enter this container or when an
 *                object has just changed its weight/volume/light status.
 * Arguments:     ob: The object that just entered this inventory
 *                from: The object from which it came.
 */
void
enter_inv(object obj, object from)
{
    ::enter_inv(obj,from);
    if (!from) 
        return; // Was probably cloned into me. 

    set_alarm(2.0, 0.0, return_messenger_home); 
    // This will make the child run away if given anything except a
    // message to deliver.
}

#if 0
// Just use the standard now that there is one.
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
        SLOW;
    }
    
    if (environment(sender) == environment(receiver))
    {
        return random(5);
    }
    
    if (explode(MASTER_OB(environment(sender)), "/")[2] ==
        explode(MASTER_OB(environment(receiver)), "/")[2])
    {
        FAST;
    }
    
    return SLOW;
}
#endif

/* HOOKS TO CUSTOMIZE MESSAGES */

/*
 * Function:    hook_send_message
 * Description: Hook that gets called to display the message of the
 *              messenger getting the message and leaving to deliver it
 * Arguments:   none
 * Returns:     nothing
 */
public void
hook_send_message()
{
    write("You give the letter to the "+ short() + ".\n");
    say(QCTNAME(this_player()) + " gives a letter to the "+
        short() +" acting as "+ this_player()->query_possessive() + 
        " messenger.\n");

    tell_room(environment(this_player()),
        "The "+ short() +" folds the paper up, puts it in an "+
        "envelope, and seals it.\n"+ 
        capitalize(this_object()->query_pronoun()) +" then dashes "+
        "off as fast as "+ this_object()->query_pronoun() +" can.\n");    
}

/*
 * Function:    hook_resend_message
 * Description: Hook that gets called to display the message of the
 *              messenger being asked to re-deliver after a failed attempt.
 * Arguments:   none
 * Returns:     nothing
 */
public void
hook_resend_message()
{
    write("You convince the "+ short()+ " to make yet another try.\n");
}

/*
 * Function:    hook_deliver_message_failure
 * Description: Hook that gets called to display the message of the
 *              the messenger being unable to deliver the message and
 *              returning to the sender.
 * Arguments:   sender - the person who sent the message
 * Returns:     nothing
 */
public void     
hook_deliver_message_failure(object sender)
{
    string not_found;
    
    not_found = "Sorry, but I couldn't find "
        + capitalize(gReceiver) + " anywhere!\n";
    
    tell_object(sender, "A "+ short() +" arrives.\nThe "+ short() + 
        " grabs onto your leg and won't let go.\n"+ 
        capitalize(this_object()->query_pronoun()) +" hands you a "+
        "letter and says: " + not_found);
    tell_room(environment(sender), "A "+ short() + " arrives.\n"+
        capitalize(this_object()->query_pronoun()) +" runs up to "+ 
        QTNAME(sender) + " and clings to "+ sender->query_possessive()+ 
        " leg. After catching "+ this_object()->query_possessive() +
        " breath, the child gives "+ 
        sender->query_objective() + " a letter.\n", sender);    
}

/*
 * Function:    hook_deliver_message_success
 * Description: Hook that gets called to display the message of the
 *              messenger successfully delivering the message to the
 *              recipient.
 * Arguments:   receiver - the person receiving the message
 * Returns:     nothing
 */
public void     
hook_deliver_message_success(object receiver)
{
    string not_found;
    
    not_found = "I have a letter for you from "+ 
                capitalize(gSender) + "!\n";
    
    tell_object(receiver, "A "+ short() +" arrives.\nThe "+ short() + 
        " grabs onto your leg and won't let go.\n"+ 
        capitalize(this_object()->query_pronoun()) +" hands you a "+
        "letter and says: " + not_found);
    tell_room(environment(receiver), "A "+ short() + " arrives.\n"+
        capitalize(this_object()->query_pronoun()) +" runs up to "+ 
        QTNAME(receiver) + " and clings to "+ receiver->query_possessive()+ 
        " leg. After catching "+ this_object()->query_possessive() +
        " breath, the child gives "+ 
        receiver->query_objective() + " a letter.\n", receiver);    
}

/*
 * Function:    hook_cannot_deliver_player_unavailable
 * Description: Hook that gets called to display that the messenger cannot
 *              deliver to someone who is either LD or not in the game.
 * Arguments:   who - the person the sender is trying to send to
 * Returns:     nothing
 */
public void
hook_cannot_deliver_player_unavailable(string who)
{
    notify_fail("That person has gone to sleep!\n");    
}

/*
 * Function:    hook_messenger_returns_home
 * Description: Hook that gets called to display the message of the
 *              messenger returning home after either being used up or
 *              being asked to return home.
 * Arguments:   none
 * Returns:     nothing
 */
public void
hook_messenger_returns_home()
{
    object room;
    if (living(room = environment()))
    {
        room = environment(room);
    }

    tell_room(room,
        QCTNAME(this_object()) + " seizes the opportunity and makes "
      + "a run for home.\n");
}

/* We had a room with 600 messengers in it, per Cotillion.
 * Limiting the number that can be together to 13.
 * -- Lilith
 */
public void
enter_env(object to, object from)
{
    int i;
    object *obs;

    ::enter_env(to, from);


    /* Only ever one at a time in a person/room inventory */
    foreach(object ob : all_inventory(to))
    {
	if (ob == this_object())
	    continue;

	if (!ob->id("_bazaar_messenger"))
	    continue;

        i++;
        if (i > 13)
        {   
            hook_messenger_returns_home();            
	    ob->remove_object();
        }
    }
}

