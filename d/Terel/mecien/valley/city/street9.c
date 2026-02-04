inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>

#define PATH "/d/Terel/mecien/valley/city/"

create_room(){

set_short("Street");
set_long(
"The stones of the road are loose, the pieces broken. Tall buildings\n"
+"hang over the street, providing a haunted feeling. A light mist hangs\n"
+"in the sky, troubling the eyes. An eerie feeling glides through\n"
+"its way through the streets here, making it a less desirable place\n"
+"to travel. Two aged stone house rise on the north side of the\n"
+"street, on the south side is a black stone building.\n"
);

add_item(({"house", "houses"}), "They are old residences of the inhabitants "
+ "of the city, they look off-limits.\n");
add_item(({"black stone building", "stone building"}),
   "There is no telling what it is.\n");
add_exit(PATH + "street8", "southeast", 0);
add_exit(PATH + "street10", "northeast", 0);
add_exit(PATH + "ds", "south", "@@closed");
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

