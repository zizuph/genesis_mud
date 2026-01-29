
 /*
        coder(s):   Maniac & Jaacar Sept 1996

 */

#pragma save_binary

inherit "/std/room";

#include <stdproperties.h>
#include <macros.h>
#include "defs.h"

void
create_room()
{
    set_short("The village street");
    set_long("This multi-coloured crazy-paved main street is flanked by " +
         "the more important huts of the locality. A large " +
         "silver-painted hut signed as the `Leaping Dolphin' tavern " +
         "lies just to your north, while to your south is the " +
         "ever-animated fish market, a large blue hut where " +
         "some important trade takes place. Humbler residential " + 
         "huts fill the space behind them, and the occasional " + 
         "palm tree can be seen. " +  
         "From the west you can hear the waves crashing against the " + 
         "shore and catch the freshness of the sea breeze.\n"); 

    add_item(({"tree", "trees", "palm tree", "palm trees"}), 
       "How nice! They seem to grow quite well here. A place like this " +
       "wouldn't really be complete without them.\n");  

    add_item(({"huts"}),
        "The rustic huts are wooden and painted in " +
        "various colours. The largest ones, which lie just off the " +
        "village street, seem to be the busiest, while further away " +
        "are the more cosy residential ones.\n");

    add_item(({"street", "village street", "walkway"}),
        "The village street runs perpendicular to the promenade, " +
        "right through the centre of the village. The surface is " +
        "crazy-paved, with stones of many colours and sizes fitted " +
        "together at chaotic angles. " +
        "On each side are the commercial or important huts of the " +
        "locality, such as the tavern, the fish market, the hardware " +
        "store and the residence of the local guru.\n");

    add_item(({"large hut", "hut"}), "Which hut?\n"); 

    add_item(({"tavern", "silver-painted hut", "silver hut"}),
         "The local tavern is a large silver-painted wooden hut. " +
         "A jolly sign over the door marks it as `The " +
         "Leaping Dolphin'. " +
         "It has two entrances, one open to the promenade and the other " +
         "linking it with the village street. You can see people inside " +
         "and hear the clinking of classes.\n");

    add_item(({"market", "fish market", "blue-painted hut", "blue hut" }),
         "The local fish market is a large blue-painted wooden hut. " +
         "A jolly sign over the door marks it as `Mar-Iella's Fish " +
         "Market - We Pay the Best Prices!' " +
         "It has two entrances, one connecting to the village street " +
         "and one to the promenade. You can see people inside " +
         "haggling over prices.\n");

    add_item(({"village", "small village", "fishing village"}),
        "It's a tiny, rustic place, little more than a neatly " +
        "arranged collection of huts. But, as they say, it's not " +
        "size that counts.\n");

    add_item(({"waves", "sea", "blue-green sea", "boats", "rowing boats", 
               "fishing boats", "small boats", "beach", "sand", 
               "white sand", "promenade"}), 
           "Go west to get a better look.\n"); 

    add_prop(ROOM_I_LIGHT,1);
    add_prop(ROOM_I_INSIDE,0);
    add_prop(ROOM_I_IS,1);

    add_exit(BEACH+"village2","north",0,0);
    add_exit(BEACH+"village4","west",0,0);
    add_exit(BEACH+"village6","east",0,0);
    add_exit(BEACH+"village8","south",0,0);
}

