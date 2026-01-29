
 /*

     Village street, coded by Maniac & Jaacar, Oct 96. 

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
         "the more important huts of the locality. A rather " +
         "rickety looking hut signed as the \"Shark's Tooth Shack\" " +
         "lies just to your north, while to your south is the " +
         "local herbalist, a place that is popular among Elemental " +
         "worshippers. To the east lies the home of the local guru. " + 
         "Humbler residential huts fill the space behind them, and " +
         "the occasional palm tree can be seen. At a point in the centre " +
         "of the street is a small white stone. " + 
         "From the west you can hear the waves crashing against the " +
         "shore and catch the freshness of the sea breeze.\n");

    add_item(({"stone", "white stone", "small stone", "small white stone"}),  
             "The small white stone is set into the paving. It is about " +
             "two feet high and has some writing inscribed on it.\n"); 

    add_item("writing", "You can read it.\n"); 

    add_cmd_item(({"writing", "inscription"}), "read", 
                 "It reads:\n" +  
        "    `To commemorate those slain in this the village of Greensea\n " +
        "          by the krougs of Steerax. May their souls rest \n" +
        "                    forever in the deeps.'  " +
        "\n"); 

    add_item(({"tree", "trees", "palm tree", "palm trees"}),
       "How nice! They seem to grow quite well here. A place like this " +
       "wouldn't really be complete without them.\n");

    add_item(({"huts"}),
        "The rustic huts are wooden and painted in " +
        "various colours. The largest ones, which lie just off the " +
        "village street, seem to be the busiest, while further away " +
        "are the more cosy residential ones.\n");

    add_item(({"shack", "rickety hut", "hardware store", "hardware shop"}), 
        "It's quite an old, rickety and dusty hut. It doesn't " + 
        "exactly put the `hard' into `hardware store', but " + 
        "it has recently come into fresh ownership that may change " +
        "that.\n"); 

    add_item("herbalist", "The hut of the local herbalist " + 
        "is smaller than the other commercial huts. " + 
        "It is painted natural green and looks rather cosy. " +
        "Over the door is written a motto: `Nature's Way is Best.'\n"); 

    add_item(({"guru home", "residence", "home", "guru hut", 
               "guru residence" }), 
       "The local guru lives in a hut made of polished pine. " + 
       "Long strings of beads hang from the top of the entrance " +
       "obscuring the interior. You think you can detect " +
       "a faint smell of burning incense coming from inside.\n"); 

    add_item(({"street", "village street", "walkway"}),
        "The village street runs perpendicular to the promenade, " +
        "right through the centre of the village. The surface is " +
        "crazy-paved, with stones of many colours and sizes fitted " +
        "together at chaotic angles. " +
        "On each side are the commercial or important huts of the " +
        "locality, such as the tavern, the fish market, the hardware " +
        "store and the residence of the local guru.\n");

    add_item(({"large hut", "hut"}), "Which hut?\n");

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

    add_exit(BEACH+"village3","north",0,0);
    add_exit(BEACH+"village5","west",0,0);
    add_exit(BEACH+"wiseman_hut","east","@@block");
    add_exit(BEACH+"village9","south", 0, 0);
}


int
block()
{
    this_player()->catch_msg("The door to the hut is closed and "+
        "you can't seem to open it. Perhaps you should try again "+
        "later.\n");
    return 1;
}
