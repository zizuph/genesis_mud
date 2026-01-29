
/* 
   Inherited room for the northwest sector of level 2 of the Calia 
   water area, (sector_1_0_2).  

   Coded by Maniac May 1996

 15                   8      
|------------------------|
|          sv sf s  s  s | 0 
|       sv sf s  s  s  s |       s - open sea
|    sv sf s  s  s  s  s |       M - Mt Pyros top east
| sv sf s  s  s  s  s  s |       sv - city vis*
| sf s  s  s  s  s  s  s |       sf - city further vis*
| s  s  s  s  s  s  s  s |      
| s  s  s  s  s  s  s  s |       
M s  s  s  s  s  s  s  s | 7     *  from above and to side 
|------------------------|     

*/

#pragma save_binary

inherit "/d/Calia/std/water_room";
inherit "/d/Calia/sea/std/sea_creature_descs"; 

void
make_the_room(string extra_long, int x, int y, int z)
{
    string city, intro, depth, w_desc, proxim; 
    int rocks_present;

    set_short("Swimming a fair way down"); 

    city = ""; 
    intro = ("The slightly cool salt water holds you as you paddle around " +
             "some way below the surface. Visibility is good since " +
             "the outstretched fingers of sunlight are still only " +
             "partially doused.");

    w_desc = ("The water is a clear blue-green and feels a little " +
              "on the cool side but quite comfortable. The shades of " +
              "colour around you are darker than above. ");

    proxim = "";

    add_sea_creature("red herring"); 
    set_presence_chance("red herring", 7); 
    add_sea_creature("trigger fish"); 
    set_presence_chance("trigger fish", 12); 
    add_sea_creature("frog fish");
    set_presence_chance("frog fish", 10); 
    add_sea_creature("flying fish");
    set_presence_chance("flying fish", 4); 
    add_sea_creature("hatchet fish");
    set_presence_chance("hatchet fish", 4); 
    add_sea_creature("whale shark"); 
    set_presence_chance("whale shark", 4); 
    add_sea_creature("needle fish");  
    set_presence_chance("needle fish", 10); 
    add_sea_creature("yellowtail fish");  
    set_presence_chance("yellowtail fish", 10); 

    switch (random(4)) {
        case 0 : intro = ("The rippling textures of water play " +
                        "across your view. " + intro);   
             break;
        case 1 : intro = 
                     ("Shades of blue and green undulate " +
                      "around you. " + intro); 
               break;
        case 2 : intro = 
                     ("There is an occasional blur as shoals of " +
                      "fish stream here and there across the deepening " +
                      "watery backdrop. " + intro); 
                 break;
        default : intro = 
                      ("The currents intertwine " + 
                       "and weave around your floating body, as " +  
                       "bubbles rise from your nose and mouth. " + intro); 
               break;
    }


    depth = (" Below you the marine colours darken slowly into " +
             "unseen depths."); 

    /* City far */ 
    if (((x == 11) && (y == 0)) ||  
        ((x == 12) && (y == 1)) ||  
        ((x == 13) && (y == 2)) || 
        ((x == 14) && (y == 3)) || 
        ((x == 15) && (y == 4))) { 
         set_short("Distant view above underwater city"); 
         city = ("Many fathoms below you, on the edge of your field " +
                 "of vision to the northwest, you see a great " +
                 "underwater city spreading out. "); 
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
         set_short("View of underwater city below and to northwest"); 
         city = ("Below you to the northwest a great underwater city " +
           "of light opens out. You see gleaming dome-shaped " +
           "buildings of all sizes, cylindrical towers " +
           "rising, spherical buildings standing on central spines, " +
           "fin-shaped buildings, and many others. " +
           "More immediately below you are the city walls. "); 
         add_item(({"city", "underwater city", "great city", 
                    "great underwater city"}), 
                 "It is an unusual sight from a land-dweller's " +
                 "perspective, but it seems to fit perfectly in a " +
                 "sea environment.\n"); 
         add_item(({"walls", "city walls"}), 
               "They appear to me more for display than anything else. " +
               "Walls make little sense under water. If you swim down " +
               "you can take a closer look.\n"); 
         add_item(({"gate", "gates", "city gates"}), 
            "The gates look very unusual. " +
            "They are made in the shape of a gigantic whale's head. " +
            "If you swim down you can get a closer look.\n"); 
         add_item(({"lights", "sparkling lights"}), 
                 "The shades of light given off at the tops of towers " +
                 "and other points among the buildings " +
                 "are mysterious, being both bright " +
                 "and soothing at the same time.\n"); 
         add_item(({"buildings"}), 
                "Which buildings do you want to look at, " +
                "dome-shaped, spherical, tail-shaped or towers?\n"); 
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
    }

     /* volcano */
    if (x == 15)  {
        if (y == 9) {
            proxim += "Off to the northwest you can see a " +
                "massive shape, the top of an underwater volcano. ";
            add_item(({"top", "underwater volcano", "volcano"}),
                "It looks like the top of a large underwater volcano. " +
                "The bulk of its great mass sinks below you into the " +
                "darkness, but you can see the rim of the crater " +
                "from here.\n");
        }
        else if (y == 6) {
            proxim += "Off to the southwest you can see a " +
                "massive shape, the top of an underwater volcano. ";
            add_item(({"top", "underwater volcano", "volcano"}),
                "It looks like the top of a large underwater volcano. " +
                "The bulk of its great mass sinks below you into the " +
                "darknes, but you can see the rim of the crater " +
                "from here.\n");
        }
        else if ((y == 7) || (y == 8)) { 
             set_short("Swimming near crater of underwater volcano"); 
             w_desc = ("The water here is somewhat darker than other " +
                "places, mainly due to the fine, sooty residue that " +
                "seems to be suspended in the water here. It is " +
                "also very warm, even hot. ");

             proxim += ("To your west you see the top of " +
                "a great underwater volcano that rises from the depths. " +
                "Its sheer size is ominous. When it is active it must " +
                "carry an awesome destructive power. The heat of the water " +
                "around here and the soot which pervades it emanate " +
                "from the wide crater next to you. "); 

             add_item(({"volcano", "underwater volcano"}),
                "Its shape and rock structure is that of a volcano, " +
                "and the great crater next to you provides another clue. " +
                "It is absolutely huge. When it is active it " +
                "must carry an awesome destructive power.\n");

             add_item(({"wide crater", "crater", "crater rim"}), 
               "The crater is wide and rugged. It is heating the water " +
               "of the locality and letting out soot, very slowly but " +
               "ominously. " +
               "This baby looks like it's had a few tantrums in its time, " +
               "and you definitely don't want to be around when it has " +
               "its next one. The heat and soot over the crater " +
               "prevent you from taking a perilous look over the rim.\n"); 
         }
    } 

    add_item(({"sea", "water", "currents"}),
               (w_desc + "The sea, which extends a long way below " + 
               "you, is moving with gentle currents at your " +
               "level.\n"));

    set_long(city + proxim + intro + depth + "\n"); 
    set_tell_time(30); 
    start_creatures();
}

