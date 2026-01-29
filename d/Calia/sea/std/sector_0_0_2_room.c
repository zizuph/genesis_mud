
/* 
   Inherited room for the northeast sector of level 2 under the sea
   of the water area in Calia (sector_0_0_2). 

   Coded by Maniac April 1996

  7                    0 
|------------------------|
| s  s  s sb sb  u       | 0       
| s  s  s sb sb  u       |       s - open sea
| s  s  s sb sb  u       |
| s  s  s sb sb  u       |       u - rising sea bed
| s  s  s sb sb  u       |      sb - sea bed
| s  s  s sb sb  u       |       C - clam room
| s  s  s sb sb  u       |       O - oyster room
| s  s  s sb  C  O       | 7   
|------------------------|      

*/

#pragma save_binary

inherit "/d/Calia/std/water_room";
inherit "/d/Calia/sea/std/sea_creature_descs"; 


void
make_the_room(string extra_long, int x, int y, int z)
{
    string intro, depth, w_desc, proxim; 

    set_short("Swimming a fair way down");

    intro = ("The slightly cool salt water holds you as you paddle around " +
             "some way below the surface. Visibility is good since " +
             "the outstretched fingers of sunlight are still only " +
             "partially doused. ");

    w_desc = ("The water is a clear blue-green and feels a little " +
              "on the cool side but quite comfortable. The shades of " +
              "colour around you are darker than above.\n");

    proxim = "";

    add_sea_creature("red herring"); 
    set_presence_chance("red herring", 5); 
    add_sea_creature("trigger fish"); 
    set_presence_chance("trigger fish", 9); 
    add_sea_creature("frog fish");
    set_presence_chance("frog fish", 7); 
    add_sea_creature("flying fish");
    set_presence_chance("flying fish", 3); 
    add_sea_creature("hatchet fish");
    set_presence_chance("hatchet fish", 3); 
    add_sea_creature("whale shark"); 
    set_presence_chance("whale shark", 3); 
    add_sea_creature("needle fish");  
    set_presence_chance("needle fish", 7); 
    add_sea_creature("yellowtail fish");  
    set_presence_chance("yellowtail fish", 7); 

    switch (random(4)) {
        case 0 : intro += 
                       ("The rippling textures of water play " +
                        "across your view. ");   
             break;
        case 1 : intro += 
                       ("Shades of blue and green undulate " +
                        "around you. "); 
              break;
        case 2 : intro += 
                       ("There is an occasional blur as shoals of " +
                        "fish stream here and there across the deepening " +
                        "watery backdrop. "); 
                 break;
        default : intro += 
                        ("The currents intertwine " + 
                         "and weave around your floating body, as " +  
                         "bubbles rise from your nose and mouth. "); 
              break;
    }

    /* depth related */
    switch (x) {
        case 3 : 
                  set_short("Swimming near rising sea bed"); 
                  proxim += ("To your east the sea bed rises. "); 
                  /* No break as we want stuff from case 4 too */ 
        case 4 :  
                 depth = "The sandy, muddy sea bed is just below you. ";  
                 add_item(({"sea", "water", "currents"}), 
                           "The sea is moving with gentle currents. " + 
                            w_desc); 
                 add_item(({"sea bed", "sandy sea bed", "bottom"}), 
                        "The sea bed, just below you, is " +
                        "sandy but has stones and mud mixed in " +
                        "with it. " +
                        "You notice much sea weed down there, along with " +
                        "many little crabs, star fish and other life.\n"); 
                 add_item(({"sea weed", "little crabs", "crabs", "star fish"}),
                           "One of the many humbler forms of sea life " +
                           "that exist down here.\n"); 
                 break;
        case 5 : 
                 depth = ("Looking down, you can just make out the sea bed " +
                          "a few fathoms below you. ");
                 add_item(({"sea", "water", "currents"}),
                           "The sea is moving with gentle currents. " + 
                           w_desc);
                 add_item(({"sea bed", "bottom"}),
                        "The sea bed is a few fathoms below you. Because " +
                        "of the darkening that occurs at deeper levels " +
                        "you cannot make out any details.\n"); 
                 break;
        case 6 : 
        case 7 : 
                 add_item(({"sea", "water", "currents"}),
                           "The sea, which extends a long way below " + 
                           "you, is moving with gentle currents at your " +
                           "level. " + w_desc);
                 depth = ("Downwards the water extends a long way. " +
                          "The light down there is so much weaker that you " +
                          "cannot make out the sea bed, only a deep, dark " +
                          "impenetrable blue-green. "); 
                 break;
    }

    set_long(proxim + intro + depth + extra_long); 
    set_tell_time(30); 
    start_creatures();
}

