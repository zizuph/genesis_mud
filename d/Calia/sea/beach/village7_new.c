
 /*
        coder(s):    Jaacar & Maniac 23/8/96
        change:      Uhclem added exit to southwest and relevant changes
                     to long description.  14/9/2002

 */

#pragma save_binary

inherit "/d/Calia/std/room_tell_room";

#include <stdproperties.h>
#include <macros.h>
#include "defs.h"

void
create_room()
{
    set_short("Promenade of seaside village");
    set_long("You walk along the sea front of a small fishing village. " +
        "This is the promenade, a raised area of beach where the sand is " +
        "overlaid sparsely with light blue paving stones. The village " +
        "itself adjoins it. Rustic wooden huts are arranged neatly " +
        "on either side of the village street. Next to you is a " +
        "large blue-painted hut which looks like the local fish market. " +
        "Lying at points along the promenade are a small number " +
        "fishing boats in various stages of manufacture. Out to sea " +
        "you notice many complete versions floating around. " +
        "It seems the fisher folk are at work. South of here " +
        "the coastline gets rather craggy and rocky, but a narrow " +
        "cleft in the rocks allows passage to the southeast.\n");

    add_item(({"village", "small village", "fishing village"}),
        "The village adjoins the pleasant promenade. " +
        "It's a tiny, rustic place, little more than a neatly " +
        "arranged collection of huts. But, as they say, it's not " +
        "size that counts.\n");

    add_item(({"rocks", "coastline", "cleft", "narrow cleft",
          "path", "narrow path", "rocky path", "narrow rocky path"}),
          "South of here are large grey craggy rocks, a daunting " +
          "barrier to travellers, but a cleft in the rocks, possibly " +
          "the result of some recent erosion, reveals a narrow " +
          "rocky path to the southwest.\n"); 

    add_item(({"street", "village street"}),
        "The village street runs perpendicular to the promenade, " +
        "right through the centre of the village. On each side are " +
        "the commercial or important huts of the locality, such as " +
        "the tavern, the fish market, the general store and the " +
        "residence of the local guru.\n");

    add_item(({"huts"}),
        "The rustic huts are wooden and painted in " +
        "various colours. The largest ones, which lie just off the " +
        "village street, seem to be the busiest, while further away " +
        "are the more cosy residential ones. One just next to you " +
        "catches your eye, it seems to be the local fish market.\n");

    add_item(({"fish market", "hut", "blue-painted hut", 
               "blue hut", "large hut"}),
         "The local fish market is a large blue-painted wooden hut. " +
         "A jolly sign over the door marks it as `Mar-Iella's Fish " +
         "Market - We Pay the Best Prices!' " +
         "It has two entrances, one connecting to the village street " +
         "and one to the promenade. You can see people inside " +
         "haggling over prices.\n");

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

    add_prop(ROOM_I_LIGHT,1);
    add_prop(ROOM_I_INSIDE,0);
    add_prop(ROOM_I_IS,1);
    add_prop(ROOM_I_TYPE, ROOM_BEACH);

    set_tell_time(80);

    add_tell("A large wave crashes on the shore to your west.\n");
    add_tell("Gulls cry and swoop above you.\n");
    add_tell("You hear the screech of someone sharpening carving " +
             "knives in the fish market.\n");
    add_tell("A cool breeze blows through.\n");

    add_exit(BEACH+"village4","north");
    add_exit(SECTOR_PATH(0, 11, 0)+"wr_0_11_0","west");
    add_exit(BEACH+"village8", "east");
    add_exit(BEACH+"cleft", "southeast");
}

/* Scale the rocks */ 
int
do_scale(string str)
{
    object tp = this_player(); 

    if (str == "rocks")
    {
        write("You scale the rocks.\n");
        tell_room(environment(tp), QCTNAME(tp)+" scales "+
            "the rocks.\n",tp);
        tp->move_living("M",BEACH+"rocks",1);
        tell_room(environment(tp), QCTNAME(tp)+" arrives.\n",tp);
        return 1;
    }
    notify_fail("Scale what?\n"); 
    return 0;
}

void
init()
{
    ::init();
    add_action(do_scale,"scale");
    add_action(do_scale,"climb");
}

