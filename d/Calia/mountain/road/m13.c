/* 
   Moorland in the mid-west of Calia.

   Coded by Maniac.

   History: 
           1.5.95          Created                      Maniac
*/

#pragma save_binary

inherit "/d/Calia/std/std_west_moor";
#include "/d/Calia/mountain/defs.h"

void
create_room()
{
    make_the_room("\n", 2); 
    set_long("You have reached a peaceful place out on the open moorland. " +
       "You see a great monument standing here, and " +
       "can feel an aura of pure magic around it. It seems to " +
       "be made up of weapons arranged in a perfect tower-like " +
       "shape, shining and amazingly preserved, despite " +
       "the elements. Indistinct memories of great deeds in times " +
       "gone by seem to be all around this place, perhaps emanating " +
       "from the monument itself, and finding their way into your mind. " +
       "The air feels warmer here than in the surrounding moors.\n");

    add_exit(ROAD+"road15", "east");
    add_exit(ROAD+"road16", "north");
    add_exit(ROAD+"m07", "northwest");
    add_exit(ROAD+"m08", "northeast");
    add_exit(ROAD+"m12", "west"); 
    add_exit(ROAD+"m17", "southwest");
    add_exit(ROAD+"m18", "south");
    add_exit(ROAD+"m19", "southeast");

    clone_object(MOUNTAIN_OBJ + "monument")->move(this_object());
}
