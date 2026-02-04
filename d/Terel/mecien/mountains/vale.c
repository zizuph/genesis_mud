#define PATH "/d/Terel/mecien/mountains"
inherit "/std/room";
#include <macros.h>
#include <stdproperties.h>

reset_room(arg){

object hermit;
if(present("hermit")) return;
hermit=clone_object("/d/Terel/mecien/mountains/hermit");
hermit->move(this_object());

}

create_room(){

set_short("Vale");
set_long(
"This is a small vale that stands between opposing mountains. North there\n"
+"are the icy peaked mountains, to the south dark and sinister mountains.\n"
+"The remains of a small fire are here.\n"
);

add_exit("/d/Terel/mecien/mountains/ridge", "north",0);
add_exit("/d/Terel/mecien/mountains/dark1", "south",0);
    
add_item(({"fire","remains"}),
"There are only a few burnt sticks there.\n");
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
