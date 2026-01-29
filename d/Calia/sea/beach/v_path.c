
 /*
        coder(s):    Jaacar & Maniac 26/8/96
  */

#pragma save_binary

inherit "/d/Calia/std/room_tell_room";

#include <stdproperties.h>
#include <macros.h>
#include "defs.h"

void
create_room()
{
    set_short("A little path by the sea");
    set_long("You walk along a little seaside path that skirts some " +
             "sand dunes, connecting a beach to the north " + 
             "with a little seaside village to the south. " + 
             "You can see a pleasant promenade with blue " +
             "paving stones that adjoins the foremost village " +
             "huts. The blue-green sea to your west looks warm and " +
             "inviting. Waves crash rhythmically on the shore.\n");

    add_item(({"village", "small village", "seaside village", 
               "fishing village", "huts", "village huts" }),
        "The village adjoins the pleasant promenade. " +
        "From what you can see of it, it looks like a tiny, rustic " +
        "place, little more than a neatly " +
        "arranged collection of huts. But, as they say, it's not " +
        "size that counts.\n");

    add_item((({"beach", "shore"})),
           ("It is a beautiful white sandy beach "+
            "on the shore of the sea, just north of here.\n"));

    add_item((({"dunes", "sand dunes"})),
           "The dunes to the east are too steep to climb. "+
           "They are fairly barren except for occasional "+
           "sea grasses.\n");

    add_item(({"path", "little path", "seaside path"}), 
        "It's a simple path, just a sand track, connecting " +
        "an area of natural beach to the north with a small fishing " +
        "village to the south.\n");  

    add_item(({"promenade", "paving stones", "stones"}),
       "Set in the sand to your south are a number of smooth light " +
       "blue paving stones. The paved area is raised so as not to " +
       "get caught by the tide, making it a promenade. It is some " +
       "twenty feet wide and adjoins the village.\n");

    add_item(({"waves", "sea", "blue-green sea"}), "The blue-green sea "+
        "stretches all the way to the horizon. The water looks "+
        "very clear, as large waves regularly pound the shore. " +
        "A number of small fishing boats float peacefully on the " +
        "water.\n");

    add_item(({"boats", "rowing boats", "small boats", "fishing boats"}),
           "They are many small fishing boats out there of various " +
           "colours. They look about ten feet long and are floating " +
           "peacefully on the friendly waters.\n");

    add_prop(ROOM_I_LIGHT,1);
    add_prop(ROOM_I_INSIDE,0);
    add_prop(ROOM_I_IS,1);
    add_prop(ROOM_I_TYPE, ROOM_BEACH);

    set_tell_time(80);

    add_tell("The sun is obscured briefly by a puffy white cloud.\n"); 
    add_tell("A large wave crashes on the shore.\n");
    add_tell("Sea foam washes against the edge of the path.\n");
    add_tell("Gulls cry and swoop above you.\n");

    add_exit(BEACH+"beach4","north");
    add_exit(SECTOR_PATH(0, 8, 0)+"wr_0_8_0","west");
    add_exit(BEACH+"village1","south");
}

