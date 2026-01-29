/* room coded by Elizabeth Cook/Mouse, February 1997 */

inherit "std/room";
#include <stdproperties.h> 
#define ROOT "/d/Emerald/mouse/"

void create_room()  {
     set_short("The green guest room");
     set_long("   This second guest room is known as the 'Green Room'. "+
          "Tapestries predominantly woven in shades of green hang "+
          "upon the walls and green draperies adorn the windows. The "+
          "settee and armchairs are upholstered in a green floral pattern. "+
          "The rug upon the floor and the coverlet upon the bed are primarily "+ 
          "green as well. The overwhelming use of green leaves you feeling "+
          "as if you were lost in a forest.\n");
     add_prop(ROOM_I_INSIDE,1);
     add_prop(ROOM_I_LIGHT,2);

     room_add_object(ROOT+"village/items/door2b.c");
   

        
}

