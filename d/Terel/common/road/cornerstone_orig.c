#define PATH "/d/Terel/common/road"
inherit "/std/room";
#include <macros.h>
#include <stdproperties.h>

create_room(){
object stone;

set_short("Cornerstone");
set_long(
"Great stone pillars stand here, monuments of ancient days. They\n"
+"are placed all about here, creating an ominous feeling. Various other\n"
+"stones and markers have been set into the ground, almost as if this\n"
+"were a tomb.\n"
+"A road leads west towards the mountains, east across the moors, north\n"
+"into the hills. South of here is a great silvery pine forest.\n");

add_exit(PATH + "/road5","east",0);
add_exit(PATH + "/road6","west",0);
add_exit(PATH + "/forest_edge","south",0);
add_exit(PATH + "/road9","north",0);
add_item(({"stone pillars","pillars"}),
"These grand pillars seem to have some kind of astrological meaning\n" +
"when studied. They have been inscribed with runes and icons. They are\n" +
"so worn and covered with moss and lichen to make then unreadable.\n");
add_item(({"stones","markers"}),
"They seem to have ceremonial signifigance and have also been worn\n" +
"down so any writings they had are gone.\n");
add_item(({"lichen","moss"}),
"This place seems to be a haven for strange moss and lichen.\n"
+"There are many different kinds, covering the stones, pillars,\n"
+"markers and ground. Their colors range from purple to orange.\n");


/*
 * WE'll have to fix this later!
 *
 * -- Sorgum
 */

/*stone = clone_object(PATH + "/cornerstone_obj"); */

stone = clone_object(PATH + "/broken_cobj"); 
stone->move(this_object());

}
