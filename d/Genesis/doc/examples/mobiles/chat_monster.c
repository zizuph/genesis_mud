/*
 * /doc/examples/mobiles/chat_monster.c
 *
 * A simple example of a monster that has repeating chat messages.
 */

inherit "/std/monster";

void
create_monster()
{
    set_name("chatter");
    set_adj("chatting");
    set_long("An example of a chatting monster.\n");
    set_race_name("human");

    /* This chatter will say something every now and then... :) */

    /* Set the interval between chats.  Note that it is only useful
     * to call this once:  calling this function multiple times with
     * with different arguments will not result in varying delays in
     * between chats!
     */
    set_chat_time(5); /* Interval between chat */

    /* Add each chat message.  The order that the chats occur will be
     * random, but no chat will repeat until each has been said.  Only
     * when all have been said will the chats be randomized again and
     * start to repeat.
     */
    add_chat("Hi, how are you?");
    add_chat("I'm talking to you ;-)");
    add_chat("Don't you think this is fun?");
}


