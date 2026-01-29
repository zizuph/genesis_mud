

#define PATH "/d/Terel/mountains/obj"
inherit "/std/room";
#include <macros.h>
#include <stdproperties.h>

reset_room(arg){

object boar;
if(present("boar")) return;
boar=clone_object("/d/Terel/mountains/obj/boar");
boar->move(this_object());

}

create_room(){
object door;

set_short("Entry Hall");
set_long(
"This is a large hall in the great house. The furnishings are rather\n"
+"crude. There is a small room to the east and a larger one north. A small\n"
+"lamp lights the room. The house is warm, but smokey.\n");
add_prop(ROOM_I_INSIDE, 1);

door = clone_object(PATH + "/idoor");
door->move(this_object());
door->set_key(123454321);
    
add_exit("/d/Terel/mountains/house2","north","@@guarded");
add_exit("/d/Terel/mountains/closet","east","@@guarded");
add_item(({"lamp","light"}),
"It is lit with a smelly animal fat.\n");
reset_room();
}

int guarded(){
 object boar;
 boar=present("boar");
 if(boar && boar->query_name()!="corpse"){
  write("The boar will not let you pass!\n");
  say("The boar blocks "+QCNAME(this_player())+" from going any further.\n");
  return 1;
 }
 return 0;
}
