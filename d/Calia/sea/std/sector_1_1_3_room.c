
/*

    Inherited room for the southwest corner of the third level of 
    the Calian water area (sector_1_1_3). 

    Coded by Khail and Maniac March/June 1996 

 15                    8 
|------------------------|      M  - Mt Pyros mid east
M s  s  s  s  s  s  s  s | 8    s - open sea
M s  s  s  s  s  fv s  s |      sv - city vis,    sf - city further vis
| s  s  s  s  fv fv fv s |      fv - seaweed forest
| sf s  s  fv fv fv fv fv|           visible*
| sv sf s  s  fv fv fv s |     W - city wall barrier,   CG - city gate
| W  sv sf s  s  fv s  s |      * - from above
|    CG sv sf s  s  s  s |
|       W  sv sf s  s  s | 15
|------------------------|

*/

#pragma save_binary

inherit "/d/Calia/std/water_room";
inherit "/d/Calia/sea/std/sea_creature_descs"; 
#include <stdproperties.h>

#define ROOM_I_SEAWEED_FOREST "_room_i_is_seaweed_forest"


void
make_the_room(string extra_long, int x, int y, int z)
{
    string intro, w_desc, w_item, proxim, gates, misc, city;

    set_short("Swimming deep in the sea");

    proxim = "";
    city = ""; 

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

    w_desc = ("The water here is a cool blue, deepening into a " +
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

    if (x == 8 && y == 11)
        misc = "to the west";
    else if (x == 9 && y == 10)
        misc = "to the southwest";
    else if (x == 10 && y == 9)
        misc = "to the south";
    else if (x == 11 && y == 10)
        misc = "to the southeast";
    else if (x == 12 && y == 11)
        misc = "to the east";
    else if (x == 11 && y == 12)
        misc = "to the northeast";
    else if (x == 10 && y == 13)
        misc = "to the north";
    else if (x == 9 && y == 12)
        misc = "to the northwest";
    else if ((x == 9 && y == 11) || 
             (x == 11 && y == 11) || 
             (x == 10 && y == 10)  ||  
             (x == 10 && y == 12)) 
        misc = "to the north, south, east and west"; 
    else if (x == 10 && y == 11)
        misc = "in all directions";

    if (stringp(misc) && strlen(misc))
    {
        set_short("Swimming above seaweed forest"); 
        add_item(({"forest","seaweed","seaweed forest"}),
            "The dark mass beneath you spreads out " + misc +
            " from here, a surging mass of seaweed pulsing back and forth " +
            "in the shifting currents.\n");
        proxim += "Below you, a dark mass spreads out " + misc +
            ", and moves somewhat in the changing currents. Looking more " +
            "closely you realize that what you see is the tops of a " +
            "massive underwater forest of tree-sized seaweed. ";
        misc = "";
    }


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

    if (((x == 11) && (y == 15)) ||  
        ((x == 12) && (y == 14)) ||  
        ((x == 13) && (y == 13)) || 
        ((x == 14) && (y == 12)) || 
        ((x == 15) && (y == 11))) { 
         set_short("Distant view of underwater ruins"); 
         city = ("On the edge of your field of vision to the " +
                 "southwest, you see the ruins of an underwater city " + 
                 "spreading out at your level. "); 
         add_item(({"city", "underwater city"}), 
                 "It's hard to make out much detail from here, " + 
                 "but you make out collapsed buildings in " +
                 "the dimness.\n"); 
         add_item(({"buildings", "collapsed buildings"}), 
              "The light is really very dim over there. Since you " +
              "are also far quite far away, all you can discern are " +
              "massive, dark angular shapes - shapes that must be " +
              "buildings. Their disordered arrangement, coupled with " +
              "the darkness, suggests that these are ruins rather " +
              "than a city intact.\n"); 
    }

    if (((x == 12) && (y == 15)) || 
        ((x == 13) && (y == 14)) || 
        ((x == 14) && (y == 13)) || 
        ((x == 15) && (y == 12))) {
        set_short("Near to underwater ruins"); 

        proxim += ("There is a mass of grey bedrock below you " +
                    "running from northwest to southeast. ");  
        add_item(({"bedrock", "mass of bedrock", "grey bedrock"}),
            "The mass of ancient grey stone rises from the deeper " +
            "waters below.\n"); 

         city = ("What must once have been a great city opens out in " +
           "front of you to the southwest. The dark shapes of derelict " +
           "halls, crumbled houses, fallen towers and vacant temples loom " +
           "like the bones of " +
           "a great dead beast, broken and silent, but grimly conveying " +
           "echos of the majesty that was once there. Somewhat " +
           "disturbingly, you get a strong impression that there " +
           "are `things' lurking over there, like scavengers on a " +
           "carcass. Next to you is the rubble that was once a " +
           "mighty wall. ");  

         if ((x == 13) && (y == 14)) 
             city += ("Directly in front of you are the huge rusted " +
                  "city gates, which lie unhinged, bent and twisted, " +
                  "like the skeleton of a creature that died in agony. ");

         add_item(({"city", "underwater city", "great city", 
                    "great underwater city"}), 
            "Clearly this is a land city that has sunk. It must once " +
            "have been a splendid sight. " +
            "You have a suspicion that much of the visible damage " +
            "was done in a violent turmoil rather than simply by " +
            "natural decay, although it is hard to be more definite.\n"); 
         add_item(({"rubble", "walls", "walls"}), 
           "What were once the city walls lie in front of you to the " +
           "southwest, now just heaps of broken stonework that tumbled " +
           "down in a turmoil long ago. The once proud city gates " + 
           "lie alongside at a focal point in the fallen stonework.\n");  
         add_item(({"gate", "gates", "city gates"}), 
             ("The huge iron gates are now rusted and barnacled. They " +
             "lie unhinged, bent and twisted next to the rubble of " +
             "the walls, a sign of the broken spirit of this place.\n"));  
          
         add_item(({"buildings"}), 
                "Which buildings do you want to look at, " +
                "halls, houses, towers or temples?\n"); 
         add_item(({"house", "houses"}), 
                "It seems that most of the houses were " + 
                "terraced in semi-circular rows. The general " +  
                "pattern is visible but the houses themselves " + 
                "are nearly all crumbled.\n"); 
         add_item(({"hall", "halls"}), 
                "It is evident that there were once great columned " +
                "halls down there, built in a Romanesque style. " +
                "Some columns are still standing, at funny angles, " + 
                "poking out of the otherwise wrecked structures.\n");    
         add_item(({"temple", "temples"}), "The inhabitants " + 
                "seem to have valued their Gods, as there are " +
                "four temples, at axis points in the dead city. " +  
                "Each temple appears to have been built within " + 
                "its own compound, with a statue of a deity at " + 
                "its centre.\n"); 
         add_item(({"tower", "towers"}), "What is left of the " +
                "towers stands at various points in the city, " +
                "but mostly along the walls. Since they have fallen " +
                "it is difficult to tell how high they once were, " + 
                "yet even now they stand higher than the " + 
                "rest of the city.\n"); 
    }


    intro = "You are swimming deep in the sea, immersed in a world of " +
        "blues and greens, devoid of sound except the rush of the " +
        "water past your ears. ";

    add_item(({"water", "waves", "sea"}), w_item); 

    set_long(city + proxim + intro + w_desc + extra_long);

    start_creatures(); 
}

