

#define PATH "/d/Terel/mountains/obj"
inherit "/std/room";
#include <macros.h>
#include <stdproperties.h>

reset_room(arg){

object rat, lord;
if(present("rat")) return;
rat=clone_object("/d/Terel/mountains/obj/rat");
rat->move(this_object());
if(present("lord")) return;
lord=clone_object("/d/Terel/mountains/obj/lord");
lord->move(this_object());

}

create_room(){
object door;

set_short("Master Hall");
set_long(
"This hall has been carved from stone and the walls inscribed with\n"
+"cryptic symbols, set with semi-precious stones. Two marble columns\n"
+"support the ceiling. A large mat of furs lies in the corner.\n");
add_prop(ROOM_I_INSIDE, 1);

door = clone_object(PATH + "/gobdoor2");
door->move(this_object());
    
add_item(({"mat", "furs"}), "A large bedding of matted furs.\n");
add_item("column", "They are thick pillars made to support the cave.\n");
add_item(({"semi-precious","stones"}),
"These stones have been permanently affixed to the walls.\n");
call_out("reset_room", 1);
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
