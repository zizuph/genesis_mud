/* room coded by Elizabeth Cook/Mouse, February 1997 */

inherit "std/room";
#include <stdproperties.h> 
#define ROOT "/d/Emerald/mouse/"  

void create_room()  {
     set_short("The blue guest room");
     set_long("   This first guest room is known as the 'Blue Room'. "+
          "Tapestries predominantly woven in shades of blue hang "+
          "upon the walls and blue draperies adorn the windows. The "+
          "settee and armchairs are upholstered in a blue floral pattern. "+
          "The rug upon the floor and the coverlet upon the bed are primarily "+ 
          "blue as well. The overwhelming use of blue leaves you feeling "+
          "as if you could drown in this room.\n");
     add_prop(ROOM_I_INSIDE,1);
     add_prop(ROOM_I_LIGHT,2);

     room_add_object(ROOT+"village/items/door1b.c");
   

        
}

