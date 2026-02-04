/* Chatting monster */

inherit "/std/monster";

create_monster()
{
  set_race_name("human");
    add_adj("old");
    set_name("old man");
    add_name("old man");
    add_name("man");
    set_short("old man");
    set_long("He has a long grey beard, wears a simple robe and may be blind.\n");

    set_chat_time(5);
    add_chat("Greetings.");
    add_chat("Welcome to the city of Elnoven.");
    add_chat("This is a place of great antiquity.");
}

