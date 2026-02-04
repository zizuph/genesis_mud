inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>

int tp;
#define PATH "/d/Terel/mecien/valley/city/"

reset_room(arg){

if(!tp){
tp = clone_object(PATH + "tp");
tp->move(this_object());
}
}

create_room(){

set_short("Street");
set_long(
"The stones of the road are loose, the pieces broken. Tall buildings\n"
+"hang over the street, providing a haunted feeling. A light mist hangs\n"
+"in the sky, troubling the eyes. An eerie feeling glides through\n"
+"its way through the streets here, making it a less desirable place\n"
+"to travel. Two aged stone house rise on the south side of the\n"
+"street, on the north a large red stone building.\n"
);

add_cmd_item("alley", "enter", "@@alley");
add_item(({"house", "houses"}), "They are old residences of the inhabitants "
  +"of the city,\nthey look off-limits. A small dark alley seperates them.\n");
add_item("alley", "It runs south between the houses.\n");
add_item(({"red stone building", "stone building"}),
  "It seems to be some kind of workshop.\n");
add_exit(PATH + "street7", "east", 0);
add_exit(PATH + "street9", "northwest", 0);
add_exit(PATH + "rb", "north", "@@closed");

reset_room();
}

alley(){
write("You slip into the alley, finding darkness and intrigue.\n");
say(QCTNAME(this_player()) + " slips into the shadows.\n");
this_player()->move(PATH + "al1");
return 1;
}

closed(){
write("It is closed.\n");
return 1;
}

