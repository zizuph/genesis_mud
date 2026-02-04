inherit "std/monster";
#include "/d/Terel/common/terel_defs.h"
#include <stdproperties.h>
#include <macros.h>

create_monster(){
set_race_name("human");
set_name("thidlo");
add_name("man");
add_name("hunchbacked man");
add_name("hunchback");
set_short("small hunchbacked man");
set_long("A hideous hunchbacked man. He has long gray hair and a beard\n"
  + "that matches. His teeth have fallen out, his body coated all over\n"
   + "with small blisters, and he smells of refuse. He walks very\n"
  + "strangely and of course, he is hunchbacked.\n");

set_random_move(5);

set_chat_time(3);
add_chat("What a wonderful day it is....");
add_chat("the Avenchirs are not home... come back later...");
add_chat("Why are you here?");

set_act_time(3);
add_act("stare");
add_act("giggle");
add_act("strut");


}

