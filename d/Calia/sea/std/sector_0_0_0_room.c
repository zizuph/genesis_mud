
/* 
   Inherited room for surface level of west coast Calian water area. 

   Coded by Maniac 2/1/96.
   Modified 1-12/2/96, Maniac
   Added herbs 10-08-97, Jaacar

  7                    0 
|-------------t----------|
| s  s  s  s  s  t  t    | 0     r - rock barrier
| s  s  s  s  s  s  t    |       k - kroug cave
| s  s  s  s  s  m  r  r |       b - beach
| s  s  s  s  s  s  r  r k       w - wade 
| s  s  s  s  s  s  w  w b      
| s  s  s  s  s  s  w  w b       t - shipway barrier
| s  s  s  s  s  s  w  w b       
| s  s  s  s  s  s  w  w b 7     s - sea surface
|------------------------|       m - mermaid rock

*/

#pragma save_binary

inherit "/d/Calia/std/water_room";
#include <stdproperties.h>
#include "defs.h"
#include KR_HERBSEARCH

void
reset_herb_room()
{
    set_searched(0);
}

void
reset_room()
{
    reset_herb_room();
}

void
make_the_room(string extra_long, int x, int y, int z)
{
    string intro, action, depth, w_desc, proxim, shore_far, 
           rb, coast_brief, cb, sht;
    int item_rocks, cx;  


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
   add_tell("The sound of the lapping water is all around you.\n");
   add_tell("A gull dives into the water and surfaces with a small " +
            "fish in its beak.\n");
   add_tell("A puffy white cloud briefly blocks the sun.\n");  
   add_tell("Soft sea breezes ruffle your hair.\n");  
   add_tell("A pelican soars gracefully on the warm currents of air.\n");
   add_tell("The sound of an enchanting voice singing a beautiful melody " +
            "carries across the waves, but you cannot tell where " +
           "it came from.\n");

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
                 set_search_places(({"sand","water"}));
                 add_prop(OBJ_I_SEARCH_TIME,1);
                 add_prop(OBJ_S_SEARCH_FUN,"herb_search");
                 add_herb_file(HERBS+"sargassum");
                    add_herb_file(HERBS+"fucus");
                 add_herb_file(HERBS+"surf_grass");
                 add_herb_file(HERBS+"eel_grass");
                 add_herb_file(HERBS+"cord_grass");
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
                 set_search_places(({"sand","water"}));
                 add_prop(OBJ_I_SEARCH_TIME,1);
                 add_prop(OBJ_S_SEARCH_FUN,"herb_search");
                 add_herb_file(HERBS+"sargassum");
                 add_herb_file(HERBS+"surf_grass");
                 add_herb_file(HERBS+"cord_grass");
                 add_herb_file(HERBS+"eel_grass");
                 add_herb_file(HERBS+"coral_alga");
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
                 set_search_places(({"sand","water"}));
                 add_prop(OBJ_I_SEARCH_TIME,2);
                 add_prop(OBJ_S_SEARCH_FUN,"herb_search");
                 add_herb_file(HERBS+"sargassum");
                 add_herb_file(HERBS+"fucus");
                 add_herb_file(HERBS+"salt_wort");
                 add_herb_file(HERBS+"sea_bubble");
                 add_herb_file(HERBS+"sea_lettuce");
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
    if ((y == 2) || (y == 3))
       cx = cx - 2;

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
               ("A white sandy beach stretches along the shore, " +
                "a bright highlight of the rocky coastline.\n")); 

    add_item(({ "harbour", "harbour of Gelan", 
                 "harbour of gelan" }), 
                 ("The harbour looks busy " +
                  "with the ships that dock " +
                  "on the coast.\n")); 

    add_item(({ "outcrop", "rocky outcrop" }), 
                ("Large, grey craggy rocks form an outcrop that separates " +
                 "the harbour from the beach. Much of the coastline " +
                 "of Calia is, in fact, rocky.\n"));

    add_item( ({ "ship", "ships"}), 
               ("There are ships to your north at various " + 
                "points of their journeys, approaching " +
                "and departing from the harbour of Gelan.\n")); 

    switch (y) {
        case 0 : 
        case 1 :  
                 cb = "harbour"; 
                 coast_brief = (" " + capitalize(shore_far) + ", " +
                                "to your east, you see that the nearest " +
                                "point on the shore is the southern part " +
                                "of the harbour of Gelan. To its south is " +
                                "a rocky outcrop that separates it from " +
                                "a stretch of white sandy beach."); 
                  add_item(({ "shore", "coast" }), 
                        ("The nearest point on the shore " +
                         "is the harbour of Gelan, further south is " +
                         "a rocky outcrop, then a stretch of beach.\n"));
                  add_tell("A cargo ship sails slowly out of the " +
                                 "harbour.\n");  
                  add_tell("A swift vessel sails into the harbour.\n"); 
                  add_tell("A swift vessel sails out of the " +
                                 "harbour.\n");  
                  add_tell("A cargo ship sails slowly into the harbour.\n"); 
                  break;
        case 2 :  
        case 3 :  
                  cb = "rocky outcrop"; 
                  coast_brief = (" " + capitalize(shore_far) + ", " + 
                            "to your east, you see that the nearest " +
                            "point on the shore is a rocky outcrop, " +
                            "which sits in between the harbour of " +
                            "Gelan (to its north) and a white sandy beach " +
                            "(to its south)."); 
                  add_item(({"shore", "coast" }), 
                           ("The nearest point on the shore to your east " +
                            "is a rocky outcrop. To its south is a beach " +
                            "and to its north the harbour of Gelan.\n")); 
                  break ;
        case 4 :  
        case 5 : 
        case 6 : 
        default : 
                  cb = "white sandy beach"; 
                  coast_brief = (" " + capitalize(shore_far) + ", " + 
                              "to your east, you see that the nearest " +
                              "point on the shore is a white sandy beach. " +
                              "To its north is a rocky outcrop, then " +
                              "the harbour of Gelan."); 
                  add_item(({"shore", "coast"}), 
                           ("A stretch of white sandy beach runs along " +
                            "the coast to your east. Just north of it " +
                            "is a rocky outcrop, then the southernmost " +
                            "part of the harbour of Gelan.\n"));
        break;
    }

    rb = " Waves splash against the large craggy rocks to your "; 
    proxim = "";

    if (x == 2) {
       if ((y > 1) & (y < 4)) {
           item_rocks = 1;
           proxim = (rb + "east.");  
       }
       else if (y == 1) {
           item_rocks = 1;
           proxim = (rb + "southeast."); 
       }
       else if (y == 4) {
           item_rocks = 1;
           proxim = (rb + "northeast.");
       }
    }
  
    if ((x < 2) && (y == 4)) { 
        item_rocks = 1; 
        proxim = (rb + "north.");
    }

    proxim += (" There are many sea birds in the proximity.");
    if (item_rocks) 
       add_item(({"rocks", "large craggy rocks", "large rocks", 
                  "craggy rocks" }), 
            ("They are large craggy rocks that extend outwards in " +
             "irregular patterns along much of the coast. " +
             "Foam from the waves caresses their harsh " +
             "outlines.\n")); 

    intro = ("You are " + action + " in the blue-green sea, on a fine " +
             "sunny day. The water is " + depth + " at this point." + 
              coast_brief); 
    sht = ("Sea, shore is " + shore_far + " (" + cb + ")");  
    set_short(sht);
    set_long(intro + proxim + extra_long);
    add_prop(ROOM_I_TYPE, ROOM_IN_WATER); 
}

