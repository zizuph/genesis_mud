#define PATH "/d/Terel/mecien/valley/city"
inherit "/std/room";
#include <macros.h>
#include <stdproperties.h>

object tp, smoker;

reset_room(arg){

object person1, man;
if(!tp){
tp=clone_object("/d/Terel/mecien/valley/city/tp");
tp->move(this_object());
}
if(smoker) return 0;
smoker=clone_object("d/Terel/mecien/valley/city/smoker");
smoker->move(this_object());

}

create_room(){
object statue;

set_short("Street");
set_long(
"This is the south part of town. The street runs north and south\n"
+"between the many shops. The air here is foggy and is filled with\n"
+"the many smells of the town. A large stone building stands on the west\n"
+"side of the street, in front of which is a statue. There is a small\n"
+"wooden building on the east side of the street, it has a sign on it.\n");

statue = clone_object(PATH + "/statue");
statue->move(this_object());
    
add_exit("/d/Terel/mecien/valley/city/street3", "north", 0);
add_exit("/d/Terel/mecien/valley/city/tobacco", "east", "@@closed");
add_exit("/d/Terel/mecien/valley/city/statuary", "west", "@@closed");
add_exit("/d/Terel/mecien/valley/city/street1", "south", 0);
add_item(({"sign","wooden sign"}),
"A large raven is carved upon it, under which is written:\n" +
"Myclirons Tobacco Store\n");
add_cmd_item("sign", "read", "Myclirons Tobacco Store\n");
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

closed(){

write("It is closed.\n");
return 1;
}

