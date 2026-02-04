/* Chatting monster */

inherit "/std/monster";

create_monster()
{
    set_name("hermit");
    add_name("old man");
    add_name("man");
    set_short("hermit");
    set_long("He is very old, wears tattered clothes and is fasting.\n");

    set_chat_time(5);
    add_chat("Hail.");
    add_chat("Beware the dark mountains, great evil abides there.");
    add_chat("Seek the valley in the north.");
    add_cchat("The curse of the Ancients be upon you!");
}

