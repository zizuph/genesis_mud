/* Creative rights reserved to Mecien(Jeff Babcock) and team. */
inherit "/std/room";
#include <macros.h>
#include <stdproperties.h>

#define PATH "/d/Terel/mecien/valley/guild/"

create_room(){

object door;

set_short("Secret Stair");
set_long(
"All about a mist coils upwards, rising from some abyssmal\n"
+"darkness towards a dim light above, dancing upon the eerie\n"
+"steps of this forgotten staircase. The stone is a faint shade\n"
+"of aquamarine. The stairs spiral around the outer walls of this\n"
+"cylindrical pit, standing open to the nothingness that is below.\n"
);

door=clone_object(PATH + "ldoor2");
door->move(this_object());
door->set_key(88800);

add_item(({"angel", "angelic spirit"}), 
"It is a mysterious winged spirit, white and radiant. It holds\n"
+"a silvery white branch in one hand and a spear in the other.\n");
add_item("stairs", "They spiral up and down, made from a stone of\n"
+"deep aquamarine.\n");
add_item("mist", "It is like some mysterious viel that shrouds this place.\n");

add_exit(PATH + "ss2a", "down", -10);
add_exit(PATH + "ss1", "up", 0);

}

init(){
add_action("say", "say");
::init();
}

say(string str){
object angel, key;
if(!str) return 0;
if(str == "let Truth be known"){
    seteuid(getuid());
key=clone_object(PATH + "lkey");
key->move(this_player());
key->activate();
write("A mysterious key appears in your hand.\n");
return 1;
}
}

