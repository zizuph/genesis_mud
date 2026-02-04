inherit "/std/monster";
#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>
#include <wa_types.h>

query_mm_out(){ return "flies off in a frantic despair."; }
query_m_in(){
   if(present("mecien")){
     return "lands upon the shoulder of Mecien"; }
else
   return "descends like a gloomy omen.";
}
query_m_out(){ return "flies off into some forming shadows"; }
query_mm_in(){
    return "glides downward from seemingly nowhere.\n";
}



init_living(){
add_action("do_stat", "stat");
::init_living();
}

create_monster(){
set_name("thirka");
set_race_name("raven");
set_living_name("thirka");
set_adj("shadowy");
set_long(
"A large raven, sinister and very wise looking.\n"
);
set_gender(2);
set_follow("mecien");

set_stats(({ 21, 38, 23, 144, 123, 87 }));
set_exp(0);
enable_commands();

set_act_time(1);
add_act("@@noise");

}

noise(){

tell_room(environment(this_object()), "The raven squawks loudly.\n");
return 1;

}
 
do_stat(string str){
if(!str) return 0;
if(str == "mecien"){
write("Some ancient power seems to protect him.\n");
return 1;
}

}

