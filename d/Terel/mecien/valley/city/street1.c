#define PATH "/d/Terel/mecien/valley/city"
inherit "/std/room";
#include <macros.h>
#include <stdproperties.h>

reset_room(arg){

object guard, oman;
if(present("guard")) return;
guard=clone_object("/d/Terel/mecien/valley/city/guard");
guard->move(this_object());
if(present("oman")) return;
oman=clone_object("d/Terel/mecien/valley/city/oman");
oman->move(this_object());

}

create_room(){
object door;

set_short("Street");
set_long(
"This is the south part of a street leading north.  Buildings rise\n"
+"up on either side of the street. The east building, made of red\n"
+"stone seems to be some kind of shop, the  west building, made of\n"
+"a cobbled stone, may also be some kind of shop. The city walls\n"
+"rise to the south. There is a small well here.\n");

door = clone_object(PATH + "/gate2");
door->move(this_object());
    
add_exit("/d/Terel/mecien/valley/city/street2", "north", 0);
add_exit("/d/Terel/mecien/valley/city/pottery", "east", 0);
add_exit("/d/Terel/mecien/valley/city/clothing", "west", 0);

add_item(({"well","small well"}),
"It has been dried up for many years.\n");
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
