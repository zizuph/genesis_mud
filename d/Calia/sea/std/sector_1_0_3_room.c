
/*
    Inherited room for the northwest sector of the third level of 
    the Calian water area (sector_0_1_3). 

    Coded by Khail and Maniac March/June 1996 

 15                    8 
|------------------------|
|       W  sv sf s  s  s | 0 
|    CG sv sf s  s  s  s |
| W  sv sf s  s  s  s  s |       s - open sea
| sv sf s  s  s  s  s  s |       W - city wall barrier
| sf s  s  s  s  s  s  s |      sb - sea bed
| s  s  s  s  s  s  sw s |      sv - city vis
M s  s  s  s  s  s  s  s |      sf - city further vis
M s  s  s  s  s  s  s  s | 7    CG - city gate
|------------------------|      M  - Mt Pyros mid east

*/

#pragma save_binary

inherit "/d/Calia/std/water_room";
inherit "/d/Calia/sea/std/sea_creature_descs"; 
#include <stdproperties.h>


void
make_the_room(string extra_long, int x, int y, int z)
{
    string intro, w_desc, w_item, proxim, gates, misc, city;

    proxim = "";
    city = ""; 

    set_short("Swimming deep in the sea");

    add_sea_creature("red herring");
    set_presence_chance("red herring", 3);
    add_sea_creature("trigger fish");
    set_presence_chance("trigger fish", 6);
    add_sea_creature("frog fish");
    set_presence_chance("frog fish", 6);
    add_sea_creature("hatchet fish");
    set_presence_chance("hatchet fish", 6);
    add_sea_creature("whale shark");
    set_presence_chance("whale shark", 3);
    add_sea_creature("yellowtail fish");
    set_presence_chance("yellowtail fish", 6);
    add_sea_creature("sun fish");
    set_presence_chance("sun fish", 4);
    add_sea_creature("sea catfish");
    set_presence_chance("sea catfish", 6);
    add_sea_creature("lantern fish");
    set_presence_chance("lantern fish", 6);

    w_item = ("You are completely surrounded by the dark blue water, " +
     "and you reluctantly consider the irony of something so seemingly " +
     "peaceful being so readily capable of ending your life.\n");

    w_desc = ("The water here is a cool blue, deepening to into a " +
        "seemingly impenetrable wall of blue in the distance. ");

    if (random(2))
        w_desc += ("The light filtering down through the shallower " +
              "levels shimmers and shifts due to waves on the surface. ");

    set_tell_time(45);
    add_tell("A great, dark shape cuts through the water off to one " +
        "side, but it's gone again before you can see any details.\n");
    add_tell("A school of small, brightly coloured fish appear directly " +
        "in front of you, and accelerate around you on their way past. " +
        "Tickles a bit, doesn't it?\n");
    add_tell("The deep water darkens slightly as the sun is blocked by " +
        "a cloud high above.\n");
    add_tell("Something bumps you playfully from behind, at least you hope " +
        "it was playful, because it was gone when you looked around.\n");
    add_tell("Your heart comes to a sudden stop as you look up and see the " +
        "outline of a huge shark cruising through the waters closer to the " +
        "surface. Your heart doesn't start again until it slips out of " +
        "sight.\n");


     /* shipwreck */ 
    if (x == 9 && y == 5) { 
        add_item(({"ship","shipwreck","wreck","ship wreck"}),
             "A few fathoms below, you see the dark shape of " +
             "a shipwreck. It appears to have capsized on it's way " +
             "down, and the keel is the only thing visible.\n");
       proxim += ("In the depths below, you can see a dark " +
            "curved shaped, which appears to be a shipwreck of " +
            "some kind. ");
     } 

     /* volcano */ 
    if (x == 15)  {
        if (y == 10) {
            proxim += "Off to the northwest you can see a " +
                "massive shape of some sort, possibly the " +
                "the middle heights of a volcano. ";
            add_item(({"shape", "volcano"}),
                "You really can't tell from here, the water just " +
                "is too dark for any real identification, but " +
                "your best guess places it as the middle " +
                "heights of a large, conical shaped volcano.\n");
        }
        else if (y == 5) {
            proxim += "Off to the southwest you can see a " +
                "massive shape of some sort, possibly the " +
                "the middle heights of a volcano. ";
            add_item(({"shape", "volcano"}),
                "You really can't tell from here, the water just " +
                "is too dark for any real identification, but " +
                "your best guess places it as the middle " +
                "heights of a large, conical shaped volcano.\n");
        }
        else if ((y > 5) && (y < 10)) {
             set_short("Swimming near to underwater volcano"); 

             if ((y == 7) || (y == 8)) 
                misc = "west"; 
             else if (y == 9) 
                 misc = "northwest"; 
             else if (y == 6) 
                 misc = "southwest"; 

             w_desc = ("The water here is somewhat darker than other " +
                "places, mainly due to the fine, sooty residue that " +
                "seems to be suspended in the water here. "); 
             w_item = (w_desc + " " +  "Oddly " +
                "enough, you note that the water here suddenly " +
                "changes temperature, and is even warmer than on the " +
                "surface.\n");

             proxim += ("To your " + misc + " the middle heights of " +
                "a great underwater volcano rise from the depths. " + 
                "Its sheer size is ominous, when it is active it must " +
                "carry an awesome destructive power. ");
             add_item(({"volcano", "underwater volcano"}),
                "Its shape and rock structure is that of a volcano, " +
                "and the water nearby provides another clue. " +
                "It is absolutely huge, when it is active it " +
                "must carry an awesome destructive power.\n");
         }
    }

    if (((x == 11) && (y == 0)) ||  
        ((x == 12) && (y == 1)) ||  
        ((x == 13) && (y == 2)) || 
        ((x == 14) && (y == 3)) || 
        ((x == 15) && (y == 4))) { 
         set_short("Distant view of underwater city");
         city = ("On the edge of your field of vision to the " +
                 "northwest, you see a great underwater city " +
                 "spreading out at your level. ");
         add_item(({"city", "underwater city"}),
                 "It's hard to make out much detail from here, " +
                 "but you can see sparkling lights and hints of " +
                 "unusual architecture.\n");
         add_item(({"lights", "sparkling lights"}),
                 "Lights sparkle and twinkle in the distance " +
                 "among the buildings of the city.\n");
         add_item(({"architecture", "unusual architecture"}),
                 "The shapes within the city, although not clearly " +
                 "discernible from here, seem to be quite different " +
                 "from what you're used to on land, even in Gelan.\n");
    }

    if (((x == 12) && (y == 0)) || 
        ((x == 13) && (y == 1)) || 
        ((x == 14) && (y == 2)) || 
        ((x == 15) && (y == 3))) {
        set_short("Near to underwater city"); 
        proxim += ("There is a mass of grey bedrock below you " +
                   "running from northeast to southwest. ");  
        add_item(({"bedrock", "mass of bedrock", "grey bedrock"}),
            "The mass of ancient grey stone rises from the deeper " +
            "waters below.\n"); 

        city = ("A great underwater city of light opens out at your " +
           "level to the northwest. You see gleaming dome-shaped " +
           "buildings of all sizes, cylindrical towers " +
           "rising, spherical buildings standing on central spines, " +
           "fin-shaped buildings, and many others. " +
           "You can, however, discern some movement over there. " +
           "Nearest you are the city walls. ");
         add_item(({"city", "underwater city", "great city",
                    "great underwater city"}),
                 "It is an unusual sight from a land-dweller's " +
                 "perspective, but it seems to fit perfectly in a " +
                 "sea environment.\n");
         add_item(({"walls", "city walls"}),
               "They appear to be more for display than anything else. " +
               "Walls make little sense under water. They " +
               "consist of vertical metal bars with colourful " +
               "seaweeds twined around them. It is the gates " +
               "that really catch your eye though.\n");
         add_item(({"gate", "gates", "city gates"}),
            "The gates look very unusual. " +
            "They are made in the shape of a gigantic whale's head, " +
            "with a vertical opening and closing mechanism to " +
            "represent its jaws. Metallic silvery plates form its `skin', " +
            "sharp interlocking vertical white bars are its teeth " +
            "and the great ruby coloured rocks set on either side " +
            "of the head are its eyes.\n");
         add_item(({"lights", "sparkling lights"}),
                 "The shades of light given off at the tops of towers " +
                 "and other points among the buildings " +
                 "are mysterious, being both bright " +
                 "and soothing at the same time.\n");
         add_item(({"buildings"}),
                "Which buildings do you want to look at, " +
                "dome-shaped, spherical, fin-shaped or towers?\n");
         add_item(({"dome-shaped buildings"}),
               "A smooth dome is the most common shape in the " +
               "architecture of the buildings in the city. They " +
               "have pale, elegant colours, in some cases they " +
               "are transparent. All of them shine like pearls.\n");
         add_item(({"fin-shaped buildings"}),
             "These are perhaps the most unusual of them all, " +
             "buildings that look like gigantic whales' fins pointing " +
             "upwards.\n");
         add_item(({"spherical buildings"}),
             "These are shaped as spheres, with thick central spines. " +
             "They are not perfect spheres however, appearing to have " +
             "angular plates, so they appear more like crystals.\n");
         add_item(({"towers", "cylindrical towers"}),
             "The city has some high, smooth cylindrical towers, " +
             "many of them independent from the lower buildings. " +
             "Lights shine from the tops of many of them.\n");

        if ((x == 13) && (y == 1)) 
             city += ("Directly in front of you are the unusual " +
                  "city gates. Metallic and silvery, they are made " +
                  "in the shape of a gigantic whale's head. "); 
    }


    intro = "You are swimming deep in the sea, immersed in a world of " +
        "blues and greens, devoid of sound except the rush of the " +
        "water past your ears. ";

    add_item(({"water", "waves", "sea"}), w_item); 

    set_long(city + proxim + intro + w_desc + extra_long);

    start_creatures(); 
}

