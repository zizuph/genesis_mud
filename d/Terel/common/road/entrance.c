#define PATH "/d/Terel/common/road"
inherit "/std/room";
#include <macros.h>
#include <stdproperties.h>

create_room(){
   object door;
   
   set_short("Gates");
   set_long(
      "Looming high into the air is a great stone arch, it stands as\n"
      +"part of a wall of stone here. In front of the arch grow seven\n"
      +"holly trees, their vibrant green canopies drape the walls and\n"
      +"shroud the arch in their mystery.\n");
   
   door = clone_object(PATH + "/sgate1");
   door->move(this_object());
   
   add_item(({"stone arch","arch"}),
      "A massive stone arch, twenty feet high, made from the many\n" +
      "kinds of rock. Under the arch is a silver gate which opens\n" +
      "to a road. A star of silver is set into the arch.\n");
   add_item(({"star","silver star"}),
      "A four-pointed star of silver, it serves to ward against\n" +
      "the powers of darkness. It is a sign of wisdom.\n");
   add_item(({"trees","holly"}),
      "Large evergreen trees, the leaves almost a blue-green color.\n");
add_prop(ROOM_S_MAP_FILE, "town_last.txt");

add_exit("/d/Terel/n_port/np_road1", "east", 0);
   
}
