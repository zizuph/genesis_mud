/* A mangager for dragon messengers.
 */

#pragma no_clone
#pragma strict_types
#pragma no_shadow

#include "messenger_manager.h"
#include <stdproperties.h>

#define REPLY_ENABLED 1
#define RESEND_ENABLED 1

static mapping delivery_map = ([]);

varargs object get_messenger(object dest);
object get_reply_messenger(object dest, int id);
object get_resend_messenger(object dest, int id);

static void
undeliverable(int id)
{
    mixed *data = delivery_map[id];
    object sender, messenger;

    if (!(sender = find_player(data[SENDER_REAL_NAME])))
    {
        delivery_map = m_delete(delivery_map, id);
        return;
    }

    setuid();
    seteuid(getuid());
    messenger = get_resend_messenger(sender, id);

#ifndef RESEND_ENABLED
    messenger->remove_messenger();
    delivery_map = m_delete(delivery_map, id);
#endif
}

static void
deliver(int id)
{
    object messenger, receiver;
    mixed *data = delivery_map[id];
    int reply = data[REPLY];

    if (!(receiver = find_player(data[RECEIVER_NAME])) ||
        (receiver->query_wiz_level() && receiver->query_prop(OBJ_I_INVIS)) ||
        !interactive(receiver))
    {    
        undeliverable(id);
        return;
    }

    data[REPLY] = 1;

    setuid();
    seteuid(getuid());

    messenger = get_reply_messenger(receiver, id);

#ifdef REPLY_ENABLED
    if (reply)
#endif
    {
        delivery_map = m_delete(delivery_map, id);
        messenger->remove_messenger();
    }
}

/*
 * Function name: pre_deliver
 * Description:   Do some checks before we deliver the scroll
 * Arguments:     int id - the message id as given by start_delivery()
 */
static void
pre_deliver(int id)
{
    mixed *data = delivery_map[id];
    object receiver;

    if (!data)
        return;

    /* Delay a bit longer if the receiver has moved */
    if ((receiver = find_player(data[RECEIVER_NAME])) &&
        (environment(receiver) != data[RECEIVER_ENV]))
    {
        set_alarm(itof(10 + random(15)), 0.0, &deliver(id));
    }
    else
    {
        deliver(id);
    }
}

/*
 * Function name: start_delivery
 * Description:   Set the initial delay for delivery and store some
 *                information we'll need later.
 * Arguments:     object messenger - the messenger object
 *                object sender    - the sender of the scroll
 *                object receiver  - the receiver of the scroll
 *                string name      - the name of the receiver, given by
 *                                   the player
 *                string message   - the scroll text
 *                int id           - the id for the message (for reply or
 *                                   resent messages) or -1 for new messages
 * Returns:       int - an id for the message
 */
varargs int
start_delivery(object messenger, object sender, 
               string name, string message, int id = -1)
{
    object r_env, s_env, receiver;
    int t = 20 + random(20);
    mixed arr;

    if (id >= 0)
    {
        if (!(arr = delivery_map[id]))
	{
            return -1;
	}
    }
    else
    {
        id = (m_sizeof(delivery_map) ? 
  	    applyv(&max(), m_indices(delivery_map)) + 1 : 0);
        arr = allocate(ARR_SIZE);
    }

    receiver = find_player(name);

    r_env = (receiver ? environment(receiver) : 0);
    s_env = (sender   ? environment(sender)   : 0);

    /* It takes a bit longer if the two are in different domains */
    if (s_env->query_domain() != s_env->query_domain())
    {
        t += 10 + random(20);
    }

    arr[MESSAGE] = message;
    arr[SENDER_REAL_NAME] = sender->query_real_name();
    arr[SENDER_NAME]      = sender->query_name();
    arr[RECEIVER_NAME]    = lower_case(name);
    arr[RECEIVER_ENV]     = r_env;

    delivery_map[id] = arr;

    set_alarm(itof(t), 0.0, &pre_deliver(id));
    messenger->remove_messenger();

    return id;
}

int
send(object messenger, object sender, string name, string message)
{
    return start_delivery(messenger, sender, name, message);
}

int
reply(object messenger, object sender, string message, int id)
{
    string name;
    mixed arr = delivery_map[id];

    if (!arr)
    {    
        return -1;
    }

    name = arr[SENDER_REAL_NAME];

    return start_delivery(messenger, sender, name, message, id);
}

int
resend(object messenger, object sender, int id)
{
    string name, message;
    mixed arr = delivery_map[id];

    if (!arr)
    {    
        return -1;
    }

    name = arr[RECEIVER_NAME];
    message = arr[MESSAGE];

    return start_delivery(messenger, sender, name, message, id);
}

mixed
query_message_data(int id, int which)
{
    mixed *data = delivery_map[id];

    if (!data)
    {
        return -1;
    }

    return data[which];
}

object
get_reply_messenger(object dest, int id)
{
    object ob;

    setuid();
    seteuid(getuid());

    ob = clone_object(REPLY_MESSENGER);

    ob->set_messenger_id(id);

    if (dest)
    {    
        ob->goto_dest(dest);
    }

    return ob;
}

object
get_resend_messenger(object dest, int id)
{
    object ob;

    setuid();
    seteuid(getuid());

    ob = clone_object(RESEND_MESSENGER);

    ob->set_messenger_id(id);

    if (dest)
    {    
        ob->goto_dest(dest);
    }

    return ob;
}

varargs object
get_messenger(object dest)
{
    object ob;

    setuid();
    seteuid(getuid());

    ob = clone_object(MESSENGER);

    if (dest)
    {
        ob->goto_dest(dest);
    }

    return ob;
}

void
remove_message(int id)
{
    delivery_map = m_delete(delivery_map, id);
}

void
remove_object()
{
    if (m_sizeof(delivery_map))
    {
        throw("Cannot destruct with active deliveries.");
    }

    destruct();
}
