
/* Inherited room for surface level of west coast Calian water area. 
   sector_0_1_0_room. 

   Coded by Maniac 2/1/96.

   Descriptions added, 12/2/96, Maniac

  7                    0 
|------------------------|              r - rock barrier
| s  s  s  s  s  s  w  w p     8        b - beach
| s  s  s  s  s  s  w  w v h            v - fishing village  
| s  s  s  s  s  s  w  w v h            h - village hut
| s  s  s  s  s  s  w  w b              p - path
| s  s  s  s  s  s  w  w r              s - sea surface
| s  s  s  s  s  s  w  r |              w - wade
| s  s  s  s  s  s  r  r |
| s  s  s  s  s  r  r    |    15
-----------------r-------|

*/

#pragma save_binary

inherit "/d/Calia/std/water_room";
#include <stdproperties.h>

void
make_the_room(string extra_long, int x, int y, int z)
{
    string intro, action, depth, w_desc, proxim, shore_far,
           rb, coast_brief, cb, sht;
    int cx; 

    add_item(({"sky", "sun", "cloud", "clouds"}),
             ("The sky is a rich blue, with only the occasional fluffy " +
             "white cloud. No danger of a storm today.\n"));

    add_item(({"fish", "small fish"}),
             ("Small fish of all colours abound here and seem to attract "+
              "large numbers of sea birds.\n"));

    add_item(({"birds", "sea birds", "gulls", "pelican",
                 "pelicans", "seagulls", "cormorants"}),
                ("Sea birds cry and swoop overhead, occasionally "+
                "diving into the waves after a fish. You can identify "+
                "seagulls, cormorants and pelicans.\n"));

    w_desc = ("The water is a clear blue-green and feels just the " +
              "right temperature.\n");

   set_tell_time(75);
   add_tell("The water laps gently around you.\n");
   add_tell("The longing cries of sea gulls pierce the air above.\n");
   add_tell("The sun is obscured briefly behind a white puffy cloud.\n");
   add_tell("A gentle warm breeze blows through.\n");
   add_tell("Suddenly a pelican dives in, catching a fish.\n");

   switch (x) {
       case 0 :
                 add_tell("The wet sand gushes between your toes.\n");
                 add_tell("Small fish nibble at your feet and legs.\n");
                 add_item(({"bottom", "sea bed" }),
                            ("The sea bed, which you are walking on, " +
                             "is white and sandy.\n"));
                 depth = "up to your knees";
                 add_item(({"sea", "water", "waves"}),
                            ("The sea here is shallow, only up " +
                             "to your knees. " + w_desc));
                 break;
       case 1 :
                 add_tell("A large wave nearly knocks you over!\n");
                 add_item(({ "bottom", "sea bed" }),
                            ("The sea bed, which you are walking on, " +
                             "is white and sandy.\n"));
                 depth = "up to your chest";
                 add_item(({"sea", "water", "waves"}),
                           ("The sea here is shallow, only up " +
                            "to your chest. " + w_desc));
                 break;
       case 2 :
                 add_tell("You descend with the swell of the sea.\n");
                 add_tell("You rise with the swell of the sea.\n");
                 add_item(({ "bottom", "sea bed" }),
                           ("The white sandy sea bed is clearly " +
                            "visible, well below your feet.\n"));
                 depth = "deep enough to swim downwards";
                 add_item(({"sea", "water", "waves"}),
                          ("The sea here is somewhat deeper than you " +
                           "are tall, although you will not be able " +
                           "to swim down very far. " + w_desc));
                  break;
       case 3 :
       case 4 :
                 add_tell("A large wave rolls imperiously through.\n");
                 add_tell("You descend with the swell of the sea.\n");
                 add_tell("You rise with the swell of the sea.\n");
                 add_item(({ "bottom", "sea bed" }),
                           ("The white sandy sea bed is " +
                            "just visible. It is a fair way down " +
                            "though.\n"));
                 depth = "pretty deep";
                 add_item(({"sea", "water", "waves"}),
                           ("The sea here is fairly deep, you should " +
                            "be able to swim down a fair way, if you " +
                            "so wish. " + w_desc));
                 break;
       case 5 :
       case 6 :
       default :
                 add_tell("A large wave rolls imperiously through.\n");
                 add_tell("You descend with the swell of the sea.\n");
                 add_tell("You rise with the swell of the sea.\n");
                 add_item(({ "bottom", "sea bed" }),
                              ("The sea bed is " +
                               "lost below you in a haze of " +
                               "deep blue-green.\n"));
                 depth = "very deep";
                 add_item( ({"sea", "water", "waves"}),
                           ("The sea here very deep, you should " +
                            "be able to swim down a fair way, if you " +
                            "so wish. " + w_desc));
                 break;
    }

    cx = x; 

    /* follow coastline */
    if (y == 13) 
       cx = cx - 1;
    else if (y == 14)
       cx = cx - 2; 
    else if (y == 15)
       cx = cx - 3;

    switch (cx) {
        case 0 :
                 shore_far = "within easy reach";
                 break;
        case 1 :
                 shore_far = "quite close";
                 break;
        case 2 :
                 shore_far = "not very far";
                 break;
        case 3 :
                 shore_far = "a fair distance away";
                 break;
        case 4 :
                 shore_far = "some distance away";
                 break;
        case 5 :
                 shore_far = "quite a long way away";
                 break;
        case 6 :
                shore_far = "a long way away";
                break;
        default :
                 shore_far = "a long way away";
                 break;
    }

    switch (x) {
        case 0 :
                 action = "wading";
                 break;
        case 1 :
                 action = "wading";
                 break;
        case 2 :
        case 3 :
        case 4 :
        case 5 :
        case 6 :
        default :
                 action = "swimming";
                 break;
    }


    add_item(({"beach", "white sandy beach",
               "white beach", "sandy beach",}),
               ("A white sandy beach stretches along the shore to the " +
                "north, a bright highlight of the rocky coastline.\n"));

    add_item(({"path", "little path"}), 
               ("The path is very simple, a seaside variation of a dirt " +
                "track, i.e. a sand track.\n")); 

    add_item( ({ "ship", "ships"}),
               ("A considerable way to your north there are ships " +
                "at various points of their journeys, approaching " +
                "and departing from the harbour of Gelan presumably.\n"));

    add_item(({"village", "small fishing village", "fishing village", 
               "small village"}), 
             ("It is a small fishing village. You spot some fishing boats " +
              "hauled up on the sand in front of a row of simple huts.\n"));

    add_item(({"boat", "boats", "fishing boats", "fishing boat"}), 
              ("They are small fishing boats, " +
               "about ten feet long. Not exactly the type of thing one " +
               "would go shark fishing with, but good enough for a skilled " +
               "fisherman to land a decent catch in.\n"));

    add_item(({"hut", "huts"}), "They are of the rude wooden variety.\n");

    switch (y) {
        case 8 : 
                  cb = "little path"; 
                  coast_brief = (" " + capitalize(shore_far) + ", " +
                          "to your east, you see that the nearest " +
                          "point on the shore is a little path " +
                          "that skirts the edge of some sand dunes. " +
                          "The path connects the stretch of white sandy " +
                          "beach with a small fishing village."); 
                  add_item(({"dunes", "sand dunes"}), 
                        ("The path skirts the edge of an area of sand " +
                         "dunes. The countryside can pretty varied in " +
                         "Calia, it seems.\n")); 
                  add_item(({ "shore", "coast", "coastline" }),
                        ("The nearest point on the shore " +
                         "is a little path that skirts the edge of some " + 
                         "sand dunes. It connects the stretch of white " +
                         "sandy beach with a small fishing village.\n"));
                  break;
        case 9 : 
        case 10 :
        case 11 :
                  cb = "fishing village"; 
                  coast_brief = (" " + capitalize(shore_far) + ", " +
                            "to your east, you see that the nearest " +
                            "point on the shore is small and rustic " +
                            "fishing village, a rare point of civilisation " +
                            "on the coastline. Further south the coastline " +
                            "becomes very rocky.");
                  add_item(({"shore", "coast", "coastline" }),
                          ("The nearest point on the shore to your east " +
                            "is a small and rustic fishing village. Further " +
                            "south the coastline becomes very rocky.\n"));
                  break ;
        case 12 : 
        case 13 : 
        case 14 : 
        default :
                  cb = "rocky coastline"; 
                  coast_brief = (" " + capitalize(shore_far) + ", " +
                            "to your east, you see that the coastline " +
                            "is skirted by large, craggy rocks, " +
                            "a harsh warning for any shipping in the " +
                            "vicinity. The rock-strewn coastline " +
                            "extends southwest, while to its north is " +
                            "a fishing village, then a beach.");
                  add_item(({"shore", "coast", "coastline"}),
                           ("The coast immediately to your east is very " +
                            "rocky, which is the norm of the western " +
                            "coastline of Calia. Northwards you see a " +
                            "fishing village.\n"));
        break;
    }

    if (y > 8) 
         add_item(({"rocks", "large craggy rocks", "large rocks",
                  "craggy rocks" }),
            ("They are large craggy rocks that extend outwards in " +
             "irregular patterns along much of the coast. " +
             "Foam from the waves caresses their harsh " +
             "outlines.\n"));

    /* follow coastline for rock splash room tells */
    if (((y == 12) && (x == 0)) || 
        ((y == 13) && (x == 1)) ||
        ((y == 14) && (x == 2)) || 
        ((y == 15) && (x == 3)))  {
         add_tell("Splash! A large wave hits the rocks.\n");
         add_tell("Foam fizzes around the rocks.\n");
         add_tell("A small mischievous crab scuttles between a crack in " +
                  "the rocks.\n");
    }

    intro = ("You are " + action + " in the blue-green sea, on a fine " +
            "sunny day. The water is " + depth + " at this point." + 
            coast_brief);

    sht = ("Sea, shore is " + shore_far + " (" + cb + ")");
    set_short(sht); 
    set_long(intro + extra_long);

    add_prop(ROOM_I_TYPE, ROOM_IN_WATER); 
}

