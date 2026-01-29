inherit "/std/monster";
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>

#define PATH "/d/Terel/mecien/"


query_mm_in(){
return "arrives upon a sledge drawn by flying reindeer!";
}

query_mm_out(){
  return "departs upon his famous sledge drawn by flying reindeer!";
}

create_monster(){

set_living_name("santa");
set_race_name("human");
set_name("santa");

set_long(
"A huge jolly fat man, dressed in red and white.\n"
);

set_stats(({ 456, 342, 999, 200, 345, 100 }));
enable_commands();

set_act_time(3);
add_act("emote goes Ho! Ho! Ho!");


add_act("emote searches his bag.");

}

run(string str){

if(!str) return 0;
if(find_living(str)){
this_object()->move_living(environment(str));
return 1;
}
write("You cannot locate this person.\n");
}

