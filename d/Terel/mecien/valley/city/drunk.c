inherit "/std/monster";
#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>

create_monster(){

set_race_name("human");
set_name("benedo");
set_adj("old");
add_adj("drunken");

set_alignment(23);
set_stats(random(15) + 11);


set_chat_time(15);
add_chat("I hear the mystics make wine.. I'd like that...");
add_chat("That old prophet.. I bet he gets all the wine");
add_chat("Gimme another drink!");
add_chat("I always got along good with me children");
add_chat("Me wife says I drink too much...");
add_chat("Women! They don't know nothin");
add_chat("I'll be takin another shot over here!");
add_chat("A round of beer for me friend");

set_act_time(3);
add_act("@@drink");
add_act("@@stagger");
add_act("burp");
add_act("laugh");
add_act("puke");

}

drink(){

tell_room(environment(this_object()),
   QCTNAME(this_object()) + " takes another shot of whiskey.\n");
return 1;
}

stagger(){

tell_room(environment(this_object()),
  QCTNAME(this_object()) + " staggers back and forth.\n");
return 1;
}


