/*
 * Example Message Object
 * 
 * /std/message allows one to customize the messages that
 * are delivered by messengers. This is an example of how
 * one can go about customizing the description of the
 * message.
 * 
 * The message object can be set in a messenger by calling
 * the function set_message_object_file(filename).
 *
 * Created by Petros, January 2009
 */

#include <macros.h>

inherit "/std/message";

public string
my_short()
{
	return ("message from " + query_sender());
}

/*
 * Function:    create_message
 * Description: Default create method for a message object. All we
 *              do here is customize the short description.
 */
public void
create_message()
{
    set_short(my_short);
}

/*
 * Function:    message_description
 * Description: This function is what the message looks like when it is
 *              "read" or "examine"d. Mask this function to customize
 *              the presentation to the player.
 * Returns:     string to be displayed
 */
public string
message_description()
{
    return "The message from " + query_sender() + " reads:\n" +
        query_message() + "\n";
}

/*
 * Function:    hook_message_destroyed
 * Description: Hook method that gets called when a message is destroyed.
 *              Mask this function to customize the message that players
 *              will see.
 * Arguments:   room   - room that the message is in
 *              player - if not null, then this is the player that dropped
 *                       the message, causing it to be destroyed.
 */
public varargs void
hook_message_destroyed(object room, object player)
{
    tell_room(room, "The " + short() + " crumbles to dust, then blows away.\n");
}
