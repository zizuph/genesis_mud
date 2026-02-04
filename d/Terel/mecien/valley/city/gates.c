#define PATH "/d/Terel/mecien/valley/city"
inherit "/std/room";
#include <macros.h>
#include <stdproperties.h>

reset_room(arg){
   
   object beggar;
   if(present("beggar")) return;
   beggar=clone_object("/d/Terel/mecien/valley/city/beggar");
   beggar->move(this_object());
   
}

create_room(){
   object door;
   
   set_short("City Gates");
   set_long(
      "An ancient city, whose blackened battered spires rise up into the\n"
      +"dismal sky like doomed sentinals of a long lost dream. The walls\n" 
      +"crumble away in their eternal doom, serving now only as a symbol\n"
      +"of what former glory they once held. There is still majesty in its\n"
      +"decay, a nobility of ages, of wisdom born from primal darkness\n"
      +"A shadow hangs over this place, the clouds themselves reach down\n"
      +"into the midst of the city, dwelling their like a presence of some\n"
      +"divine being. Patches of moss grow on the walls and ivy creeps up\n"
      +"onto the gate and spreads out onto the walls.\n");   
   
   door = clone_object(PATH + "/gate1");
   door->move(this_object());
   door->set_key(191);
   
   add_exit("/d/Terel/mecien/valley/path8","south",0);
   add_exit("/d/Terel/mecien/valley/city/wall1","west",0);
   add_item(({"moss","patches"}),
      "It is a strange vibrant green moss with black flowers.\n");
   reset_room();
}

int guarded(){
   object rat;
   rat=present("rat");
   if(rat && rat->query_name()!="corpse"){
      write("The nasty rat guards the way.\n");
      say("The rat keeps "+QCNAME(this_player())+" from going any further.\n");
      return 1;
   }
   return 0;
}
