
 /*
        Seaside village room 

        coder(s):    Jaacar & Maniac 23/8/96 
 */


#pragma save_binary

inherit "/d/Calia//std/room_tell_room";

#include <stdproperties.h>
#include <macros.h>
#include "defs.h"

void
create_room()
{

    set_short("Promenade of seaside village");
    set_long("You walk along the sea front of a small fishing village. " +
        "This is the promenade, a raised area of beach where the sand is " +
        "overlaid sparsely with light blue paving stones. You are at " +
        "the T-junction of the promenade and the village street, a " +
        "multi-coloured crazy-paved walkway with a variety of huts " +
        "arranged neatly on each side. Out to sea you notice many " +
        "small fishing boats dotted across your view.\n"); 

    add_item(({"village", "small village", "fishing village"}),
        "The village adjoins the pleasant promenade. " +
        "It's a tiny, rustic place, little more than a neatly " +
        "arranged collection of huts. But, as they say, it's not " +
        "size that counts.\n");

    add_item(({"street", "village street", "walkway"}),
        "The village street runs perpendicular to the promenade, " +
        "right through the centre of the village. The surface is " +
        "crazy-paved, with stones of many colours and sizes fitted " +
        "together at chaotic angles. " +
        "On each side are the commercial or important huts of the " +
        "locality, such as the tavern, the fish market, the hardware " +
        "store and the residence of the local guru.\n");

    add_item(({"huts"}),
        "The rustic huts are wooden and painted in " +
        "various colours. The largest ones, which lie just off the " +
        "village street, seem to be the busiest, while further away " +
        "are the more cosy residential ones.\n"); 

    add_item(({"beach", "sand", "white sand"}),
       "The sand of the beach beneath and between the paving stones " +
       "is very white, like sugar, and would be a little difficult " +
       "to walk in.\n");

    add_item(({"promenade", "paving stones", "stones"}),
       "Set in the sand are a number of smooth light blue paving " +
       "stones. This paved area is raised so as not to get caught by " +
       "the tide, making it a promenade. It is some twenty feet " +
       "deep and adjoins the village.\n");

    add_item(({"waves", "sea", "blue-green sea"}), "The blue-green sea "+
        "stretches all the way to the horizon. The water looks "+
        "very clear, as large waves regularly pound the shore. " +
        "A number of small fishing boats float peacefully on the " +
        "water.\n");

    add_item(({"boats", "rowing boats", "small boats", "fishing boats"}),
           "There are a few half-finished rowing boats " +
           "lying on the edge of the promenade. They look " +
           "about ten feet long and seem to be intended for fishing. " +
           "Out at sea there are many similar-sized boats of all " +
           "colours floating around.\n");

    set_tell_time(80);

    add_tell("A large wave crashes on the shore to your west.\n");
    add_tell("Gulls cry and swoop above you.\n");
    add_tell("Sounds of activity emanate from various points " +
             "in the village.\n");
    add_tell("A cool breeze blows through.\n");

   add_exit(BEACH+"village1","north");
   add_exit(SECTOR_PATH(0, 10, 0)+"wr_0_10_0","west");
   add_exit(BEACH+"village5","east");
   add_exit(BEACH+"village7","south");

   add_prop(ROOM_I_IS, 1);
   add_prop(ROOM_I_LIGHT, 1);
   add_prop(ROOM_I_INSIDE, 0);
   add_prop(ROOM_I_TYPE, ROOM_BEACH);
}

