/* room coded by Elizabeth Cook/Mouse, February 1997 */

inherit "std/room";
#include <stdproperties.h> 
#define ROOT "/d/Emerald/mouse/"

void create_room()  {
     set_short("In the upstairs hall");
     set_long("   The stairs lead to a long hallway on the second floor "+
          "of the inn. Minimal lodging for overnight guests is provided "+
          "here, in two rooms overlooking the road. A table with a "+
          "lantern atop it stands between the doors of the rooms. There "+
          "is a window at the end of the hallway that provides additional "+
          "light during the daytime. Other than the small table, the "+
          "passageway is completely devoid of decor. Although bare, the "+
          "hallway is maintained in a state of painstaking cleanliness, "+
          "the oaken floor polished to a golden glow.\n");
     add_prop(ROOM_I_INSIDE,1);
     add_prop(ROOM_I_LIGHT,2);

     room_add_object(ROOT+"village/items/door1.c");
     room_add_object(ROOT+"village/items/door2.c");

     add_exit(ROOT+"village/rooms/bwinn","down");

        
}

