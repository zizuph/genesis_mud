/* Chatting monster */

inherit "/std/monster";

create_monster()
{
   set_name("pilgrim");
   add_name("old man");
   add_name("man");
   set_short("pilgrim");
   set_long("An aged pilgrim. He looks as though he has been travelling\n" +
      "for many years. He wears simple clothing and has little\n" +
      "interest in worldly things.\n");
   
   set_random_move(2);
   set_chat_time(5);
   add_chat("I search for holiness");
   add_chat("Great blessing come from the living");
   add_chat("Peace on your journeys");
}

