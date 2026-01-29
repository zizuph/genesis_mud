
/* 
   Inherited room for surface level of west coast Calian water area. 
   sector_1_1_0_room. 

   See sector_0_1_0_room for details of the shore that lies east
   of this sector, which much of the description here is based on.


   Coded by Maniac 2/1/96.

   19/2/96    descriptions added               Maniac

 15                    8
|------------------------|    
| s  s  s  s  s  s  s  s | 8
| s  s  s  s  s  s  s  s |    s - sea surface
| s  s  s  s  s  s  s  s |
| s  s  s  s  s  s  s  s |
| s  s  s  s  s  s  s  s |
|    s  s  s  s  s  s  s |
|       s  s  s  s  s  s |
|          s  s  s  s  s | 15
|------------------------|

*/

#pragma save_binary

inherit "/d/Calia/std/water_room";
#include <stdproperties.h>

void
make_the_room(string extra_long, int x, int y, int z)
{
    string intro, depth, proxim, shore_far,
           rb, coast_brief, sea_brief, sht, cb;
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


    cx = x;
    if (y == 13)
       cx = cx - 1;
    else if (y == 14)
       cx = cx - 2;
    else if (y == 15)
       cx = cx - 3;

    switch (cx) {
       case 5 :
                shore_far = "quite a long way away";
                break;
       case 6 :
                shore_far = "a long way away";
                break;
       case 7 :
                shore_far = "a long way away";
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
        case 8 :
              cb = "little path";  
              coast_brief = (" " + capitalize(shore_far) + ", to your " +
                   "east, you see a stretch of shore on the " +
                   "western coast of Calia. Nearest you is a path " +
                   "connecting a white beach that lies just to its north " +
                   "with a fishing village that lies to its south. " +
                   "To the south of the village you see that the coastline " +
                   "becomes rocky and turns southwest, while to the north of " +
                   "the white beach is a rocky outcrop and then the animated " +
                   "harbour of Gelan.");
               break;
        case 9 :
        case 10 :
        case 11 : 
              cb = "fishing village"; 
              coast_brief = (" " + capitalize(shore_far) + ", to your " +
                   "east, you see a stretch of shore on the " +
                   "western coast of Calia. Nearest you is a small " +
                   "fishing village that lies on the edge of a southerly " +
                   "rim of rocky coastline. Looking further northwards " +
                   "you see a path connecting the village to a white " +
                   "beach, and further north still lies the mighty " +
                   "harbour of Gelan.");
              break;
        case 12 :
        case 13 :
        case 14 :
        default: 
               cb = "rocky coastline"; 
               coast_brief = (" " + capitalize(shore_far) + ", to your " +
                  "east, you see a stretch of shore on the western " +
                  "coast of Calia. Nearest you is the north-most part of a " +
                  "long rim of rocky coastline that runs its rugged course " +
                  "for a long way in a southwesterly direction. " +
                  "On its northern edge lies a small fishing village, " + 
                  "while further north is a white beach and then the great " +
                  "harbour of Gelan."); 
                  break;
    }

    intro = ("You are swimming in the blue-green sea, on a fine " +
            "sunny day. The water is " + depth + " at this point." +
            sea_brief + coast_brief);

    sht = ("Sea, shore is " + shore_far + " (" + cb + ")");
    set_short(sht);
    set_long(intro + extra_long);

    add_prop(ROOM_I_TYPE, ROOM_IN_WATER);
}

