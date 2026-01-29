
/* 
   Inherited room for surface level of west coast Calian water area. 
   sector_1_0_0_room.

   See sector_0_0_0_room for details of the shore that lies east
   of this sector, which much of the description here is based on.

   Coded by Maniac 2/1/96.

   15-16/2/96   descriptions added            Maniac

  15                   8 
|------------------------|
|          s  s  s  s  s |  0 
|       s  s  s  s  s  s |  
|    s  s  s  s  s  s  s |   
| s  s  s  s  s  s  s  s |     
| s  s  s  s  s  s  s  s |     
| s  s  s  s  s  s  s  s |    
| s  s  s  s  s  s  s  s |     
| s  s  s  s  s  s  s  s |  7   s - sea surface
|------------------------|

*/

#pragma save_binary

inherit "/d/Calia/std/water_room";
#include <stdproperties.h>

void
make_the_room(string extra_long, int x, int y, int z)
{
    string intro, depth, proxim, shore_far, 
           coast_brief, sea_brief, cb, sht;
    int cx;

    add_item(({"sky", "sun", "cloud", "clouds"}), 
             ("The sky is a rich blue, with only the occasional fluffy " +
             "white cloud. No danger of a storm today.\n"));

    add_item(({"fish", "small fish"}), 
             ("There are a few small fish of various colours around here.\n"));

    add_item(({"birds", "sea birds", "gulls", "pelican", 
                 "pelicans", "seagulls", "cormorants"}),
                ("There aren't so many sea birds around here, " +
                "most of them seem to stick closer to shore.\n"));

    add_item(({ "bottom", "sea bed" }), 
             ("The sea bed is lost below you in a haze of " +
              "deep blue-green.\n"));

    depth = "very deep"; 
    add_item(({"sea", "water", "waves"}), 
           ("The sea here very deep, you should " +
            "be able to swim down a fair way, if you " +
            "so wish. The water is a clear blue-green and feels just " +
            "the right temperature. Sometimes a little algae or " +
            "seaweed floats by.\n"));  

    set_tell_time(75);
    add_tell("The sound of the lapping water is all around you.\n");
    add_tell("Some algae floats by.\n");
    add_tell("Suddenly a flying fish leaps out of the water does a twist, " +
             "then disappears with a `plop!'\n"); 
    add_tell("You hear the cry of a sea gull from the east.\n");
    add_tell("A huge wave rolls through!\n");
    add_tell("Something brushes your legs. Hmmm..\n");
    add_tell("You descend with the swell of the sea.\n"); 
    add_tell("You rise with the swell of the sea.\n"); 

    add_prop(ROOM_I_TYPE, ROOM_IN_WATER); 

    cx = x;
 
    if ((y == 2) || (y == 3))   
        cx = cx - 2;

    switch (cx) {
       case 6 :  shore_far = "a long way away";
                 break;
       case 7 :  shore_far = "a long way away";
                 break;
       case 8 : shore_far = "a great distance away";
                break;
       case 9 : shore_far = "a great distance away";
                break;
       case 10 : shore_far = "a few hundred yards away";
                break;
       case 11 : 
       case 12 : 
       case 13 : shore_far = "far away in the distance";
                 break;
       case 14 : 
       case 15 : shore_far = "far away on the horizon";
                break;
    }
     
    add_item(({"seaweed", "algae"}), ("Every so often a little algae or " +
                     "seaweed floats by. Nothing special about it.\n")); 

    add_item(({"beach", "white sandy beach", "white beach", "sandy beach"}), 
             ("In the distance you see a white sandy beach on the shore.\n"));

    add_item(({ "harbour", "harbour of Gelan", 
                 "harbour of gelan" }), 
                 ("In the distance, the harbour looks busy " +
                  "with the ships that dock on the coast.\n")); 

    add_item(({ "outcrop", "rocky outcrop" }),
                ("You can make out the craggy rocks that form an " +
                 "outcrop separating " +
                 "the harbour from the beach. Much of the coastline " +
                 "of Calia is, in fact, rocky.\n"));

    add_item( ({ "ship", "ships"}),
               ("In the distance to the northwest, north and northeast, " +
                "there are ships at various points of their journeys, " +
                "approaching and departing from the harbour of Gelan.\n"));

    add_item(({"path", "little path"}),
              ("In the distance you see a seaside path that connects " +
               "a beach with a fishing village.\n"));

    add_item(({"village", "small fishing village", "fishing village",
               "small village"}),
             ("It is a small fishing village in the distance. You can just " +
              "spot some fishing boats hauled up on the sand in front of " +
              "some simple huts.\n"));

    add_item(({"boat", "boats", "fishing boats", "fishing boat"}),
              ("It's too far away to make out the details.\n")); 

    add_item(({"hut", "huts"}), ("It's too far away to make out the " +
                                 "details.\n"));
     
    add_item(({"rock", "rocks"}), ("It's too far away to make out " +
                                   "special details of the rocks.\n"));

    sea_brief = (" Looking west, the great rippling sea extends all the " +
                 "way to the horizon."); 

    switch (y) {
        case 0 : 
        case 1 : 
              cb = "harbour"; 
              coast_brief = (" " + capitalize(shore_far) + ", to your " + 
                   "east, you see a stretch of shore on the " +
                   "western coast of Calia. Nearest you is the large and " +   
                   "animated harbour of Gelan, bounded to the south " +
                   "by an outcrop of rocks. Further south is a white " +
                   "sandy beach, linked by a path to a fishing village, " +
                   "then a rocky stretch of coastline that curves around " +
                   "to the southwest.");
               break;
        case 2 :  
        case 3 : 
             cb = "rocky outcrop"; 
              coast_brief = (" " + capitalize(shore_far) + ", to your " +
                   "east, you see a stretch of shore on the " +
                   "western coast of Calia. Nearest you is an outcrop of " +
                   "craggy rocks, north of which is the large and busy " +
                   "harbour of Gelan, and south of which is a white sandy " +
                   "beach, linked by a path to a fishing village. After " +
                   "this is a rocky stretch of coastline that curves around " +
                   "to the southwest.");
              break;
        case 4 : 
        case 5 : 
        case 6 : 
        default: 
               cb = "white sandy beach"; 
               coast_brief = (" " + capitalize(shore_far) + ", to your " +
                  "east, you see a stretch of shore on the western " +   
                  "coast of Calia. Nearest you is a white sandy beach, " +
                  "which is connected southwards to a fishing village " +
                  "via a path, and bounded to the north by a rocky outcrop " +
                  "that divides it from the busy harbour of Gelan. " +
                  "South of the fishing village is a rocky line of coast " +
                  "that turns southwestwards."); 
                  break;

    }
 
    add_item(({"shore", "coast", "coastline"}), (coast_brief + "\n"));

    intro = ("You are swimming in the blue-green sea, on a fine " +
            "sunny day. The water is " + depth + " at this point." +
            sea_brief + coast_brief);

    sht = ("Sea, shore is " + shore_far + " (" + cb + ")");
    set_short(sht); 
    set_long(intro + extra_long);

    add_prop(ROOM_I_TYPE, ROOM_IN_WATER);

}

