#define PATH "/d/Terel/mecien/mountains"
inherit "/std/room";
#include <macros.h>
#include <stdproperties.h>

reset_room(arg){

object rat;
if(present("rat")) return;
rat=clone_object("/d/Terel/mecien/mountains/rat");
rat->move(this_object());

}

create_room(){
object door;

set_short("Stone Hall");
set_long(
"This is a large hall of stone, and is supported by eight pillars of\n"
+"black obsidian. In the center of the pillars is a pit for a fire.\n");
add_prop(ROOM_I_INSIDE, 1);

door = clone_object(PATH + "/gobdoor1");
door->move(this_object());
door->set_key(621621);
    
add_exit("/d/Terel/mecien/mountains/cavern","north",0);
add_exit("/d/Terel/mecien/mountains/quarters","west","@@guarded");
add_item(({"pit","fire"}),
"It is still warm and contains charred bones.\n");
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
