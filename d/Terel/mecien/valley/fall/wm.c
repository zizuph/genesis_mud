inherit "/std/monster";

create_monster(){
set_race_name("human");
set_name("man");
set_adj("wise");
add_adj("old");

set_stats(({ 21, 12, 15, 52, 76, 66 }));
set_alignment(555);

set_long(
"A kind looking old man. He has a short gray beard, simple blue\n"
+"eyes and a charming smile.\n"
);

set_chat_time(2);
add_chat("Do not cross this bridge!");
add_chat("The east forest is haunted, many have died there...");
add_chat("The dead walk upon the earth in the Winter Wood!");
add_chat("Great evil magic abides in the cold forest...");
add_chat("You must trust me and not go there!");
add_chat("Seek the Mystic Order for guidance");
add_chat("Power is a dangerous thing, beware");

set_act_time(3);
add_act("smile charmingly");
add_act("ponder");

}

