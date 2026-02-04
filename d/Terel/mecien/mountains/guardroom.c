#define PATH "/d/Terel/mecien/mountains"
inherit "/std/room";
#include <macros.h>
#include <stdproperties.h>

reset_room(arg){

object gguard, rat;
if(present("gguard")) return;
gguard=clone_object("/d/Terel/mecien/mountains/gguard");
gguard->move(this_object());
if(present("rat")) return;
rat=clone_object("d/Terel/mecien/mountains/rat");
rat->move(this_object());

}

create_room(){

set_short("Guard Hall");
set_long(
"This is a simple stone hall. The walls are covered with crude paintings\n"
+"that depict sexual images. There is a large heap for a bed.\n");
add_prop(ROOM_I_INSIDE, 1);

add_exit("/d/Terel/mecien/mountains/quarters", "up",0);
add_exit("/d/Terel/mecien/mountains/refuse", "down",0);
    
add_item(({"paintings","images"}),
"They are smeared on the walls in blood, they are fairly explicit.\n");
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
