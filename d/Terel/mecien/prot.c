inherit "/std/monster";
#include <macros.h>

init_living(){
add_action("do_stat", "stat");
::init_living();
}

create_monster(){
set_race_name("raven");
set_living_name("thirka");
set_adj("shadowy");
set_long(
"A large raven, sinister and very wise looking.\n"
);
enable_commands();
}

do_stat(string str){
if(!str) return 0;
if(str == "mecien"){
write("Some ancient power seems to protect him.\n");
return 1;
}

}

