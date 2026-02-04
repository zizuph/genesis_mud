/* Creative rights reserved to Mecien(Jeff Babcock) and team. */
inherit "/std/object";
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>


init(){
add_action("ms", "ms");
::init();
}

create_object(){
set_name("talisman");
set_adj("silver");

}


ms(string msg){

int i;
object *room_list;

if(this_player()->query_skill(SS_LANGUAGE) < 20){
write("To be able to speak the Ancient Mystic Tongue you\n"
+ "must improve thy language skills.\n");
return 1;
}

if(!msg){
write("Say what in the mystic language?\n");
return 1;
}

room_list = all_inventory(environment(this_player()));
  for (i=0; i < sizeof(room_list); i++)
  if (living(room_list[i]))
  {
    if(room_list[i]->query_guild_member("The Ancient Mystic Order"))
      {
         room_list[i]->catch_msg(QCTNAME(this_player()) +
            " says in mystic speech: " + msg + "\n");
       }
   else
     room_list[i]->catch_msg(QCTNAME(this_player()) +
       " speaks in a mystical language.\n");
   }

  return 1;
}

