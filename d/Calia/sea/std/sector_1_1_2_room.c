
/* 
   Inherited room for the southwest sector of level 2 of the Calia
   water area, (sector_1_1_2).

   Coded by Maniac May 1996

 15                    8 
|------------------------|    
M s  s  s  s  s  s  s  s | 8       s - open sea 
| s  s  s  s  s  s  s  s |        sv - city vis*
| s  s  s  s  s  s  s  s |        sf - city further vis*
| sf s  s  s  s  s  s  s |         M - Mt Pyros top east
| sv sf s  s  s  s  s  s |
|    sv sf s  s  s  s  s |         *  from above and to side
|       sv sf s  s  s  s |
|          sv sf s  s  s | 15
|------------------------|

*/

#pragma save_binary

inherit "/d/Calia/std/water_room";
inherit "/d/Calia/sea/std/sea_creature_descs"; 


void
make_the_room(string extra_long, int x, int y, int z)
{
    string city, intro, depth, w_desc, proxim; 

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

    if (random(2))
          depth = (" Below you the marine colours darken slowly into " +
                   "unseen depths."); 
    else
          depth = " Below you the waterworld gets progressively darker."; 

    /* City far */ 
    if (((x == 11) && (y == 15)) ||  
        ((x == 12) && (y == 14)) ||  
        ((x == 13) && (y == 13)) || 
        ((x == 14) && (y == 12)) || 
        ((x == 15) && (y == 11))) { 
         set_short("Distant view above underwater ruins"); 
         city = ("Many fathoms below you, on the edge of your field " +
                 "of vision to the southwest, you see the ruins of " +
                 "an underwater city spreading out. "); 
         add_item(({"ruins", "city", "underwater city"}), 
                 "It's hard to make out much detail from here, " + 
                 "but you make out collapsed buildings in " +
                 "the dimness.\n"); 
         add_item(({"buildings", "collapsed buildings"}), 
              "The light is really very dim down there. Since you " +
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
         set_short("View of ruined city below and to southwest"); 
         city = ("What must once have been a great city opens out below " +
           "you, to the southwest. The dark shapes of derelict halls, " +
           "crumbled houses, fallen towers and vacant temples loom " +
           "like the bones of " +
           "a great dead beast, broken and silent, but grimly conveying " +
           "echos of the majesty that was once there. Somewhat " +
           "disturbingly, you get a strong impression that there " +
           "are `things' lurking down there, like scavengers on a " +
           "carcass. Below you is the rubble that was once a " +
           "mighty wall. ");  
         add_item(({"city", "underwater city", "great city", 
                    "great underwater city"}), 
            "Clearly this is a land city that has sunk. It must once " +
            "have been a splendid sight. " +
            "You have a suspicion that much of the visible damage " +
            "was done in a violent turmoil rather than simply by " +
            "natural decay, although it is hard to be more definite.\n"); 
         add_item(({"rubble", "walls", "walls"}), 
           "What were once the city walls lie below you to the " +
           "southwest, now just heaps of broken stonework that tumbled " +
           "down in a turmoil long ago. The once proud city gates " + 
           "lie alongside at a focal point in the fallen stonework.\n");  
         add_item(({"gate", "gates", "city gates"}), 
            "The huge iron gates and now rusted and barnacled. They " +
            "lie unhinged, bent and twisted next to the rubble of " +
            "the walls, a sign of the broken spirit of this place.\n");  
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
                "darkness, but you can see the rim of the crater " +
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

