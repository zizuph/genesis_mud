
/* 
   Inherited room northwest sector of level 1 of the Calian sea area,
   (sector_1_0_1).

   Coded by Maniac April 1996

   Typo corrected, Maniac, 30/5/98

|------------------------|
|          s  s  s  s  s |   
|       s  s  s  s  s  s |       s - open sea
|    s  s  s  s  s  s  s |       M - above volcano top 
| s  s  s  s  s  s  s  s |      
| s  s  s  s  s  s  s  s |
| s  s  s  s  s  s  s  s |   
| s  s  s  s  s  s  s  s |
M s  s  s  s  s  s  s  s |
|------------------------|

*/

#pragma save_binary

inherit "/d/Calia/std/water_room";
inherit "/d/Calia/sea/std/sea_creature_descs"; 


void
make_the_room(string extra_long, int x, int y, int z)
{
    string intro, depth, w_desc, proxim; 

    set_short("Swimming not far below the surface");

    intro = ("You are swimming not far below the surface of blue-green " +
             "sea, suspended in a crystal clear but animated aquatic " +
             "world. ");

    w_desc = ("The water is a clear blue-green and feels just the " +
              "right temperature.\n");

    proxim = "";

    add_sea_creature("red herring"); 
    set_presence_chance("red herring", 6); 
    add_sea_creature("frog fish");
    set_presence_chance("frog fish", 11); 
    add_sea_creature("flying fish");
    set_presence_chance("flying fish", 11); 
    add_sea_creature("needle fish");  
    set_presence_chance("needle fish", 11); 
    add_sea_creature("yellowtail fish");  
    set_presence_chance("yellowtail fish", 11); 
    add_sea_creature("aurelia aurita"); 
    set_presence_chance("aurelia aurita", 7); 
    add_sea_creature("chrysaora isosceles"); 
    set_presence_chance("chrysaora isosceles", 7); 
    add_sea_creature("pelagia noctiluca");
    set_presence_chance("pelagia noctiluca", 7); 
    add_sea_creature("cyanea lamarki"); 
    set_presence_chance("cyanea lamarki", 7); 
    add_sea_creature("rhizostoma pulmo"); 
    set_presence_chance("rhizostoma pulmo", 7); 

    switch (random(4)) {
        case 0 : intro += 
                       ("As the sun's rays filter through the infinite " +
             "ripples, the environment takes on an enchanted aura, even " +
             "more so as its reduced sound heightens your senses of vision " +
             "and touch. ");   
             break;
        case 1 : intro += 
                       ("The coursing gentle currents are shimmering " +
                        "across your view. They enliven a vast undersea " +
                        "panorama that spreads out before you. "); 
              break;
        case 2 : intro += 
                       ("There is an occasional blur as shoals of " +
                        "fish stream here and there across the watery " +
                        "backdrop. "); 
                 break;
        default : intro += 
                        ("The currents intertwine " + 
                         "and weave around your floating body, as " +  
                         "bubbles rise from your nose and mouth. "); 
              break;
    }

    /* volcano */ 
    if (x == 15) {
        if (y == 9) {  
            proxim += "Below you to the northwest you can see a " +
                "massive shape, the top of an underwater volcano. ";
            add_item(({"top", "underwater volcano", "volcano"}),
                "The top of a large underwater volcano. " +
                "The colour of the water over the crater is much darker " +
                "than that in which you are currently swimming. You can " +
                "see the upper eastern face of the huge bulk of the " +
                "volcano descending into the depths of the sea.\n"); 
        } 
        else if (y == 6) { 
            proxim += "Below you to the southwest you can see a " +
                "massive shape, the top of an underwater volcano. ";
            add_item(({"top", "underwater volcano", "volcano", "crater"}),
                "The top of a large underwater volcano. " +
                "The colour of the water over the crater is much darker " +
                "than that in which you are currently swimming. You can " +
                "see the upper eastern face of the huge bulk of the volcano " +
                "descending into the depths of the sea.\n"); 
        } 
        else if (y == 7 || y == 8) { 
            set_short("Looking down over underwater volcano");
             w_desc = ("The water here is somewhat darker than other " +
                "places, mainly due to the fine, sooty residue that " +
                "seems to be suspended in the water here. It is " +
                "also quite warm.\n");

             proxim += ("A few fathoms below you to your west you " +
                "see the top of a great underwater volcano. " +
                "The colour of the water over the crater is much darker " +
                "than that in which you are currently swimming. From here " +
                "you can see upper eastern face of the huge bulk of the " +
                "volcano descending into the depths of the sea.\n"); 

             add_item(({"crater", "volcano", "underwater volcano"}),
                "The nearest part of the volcano to you is the crater, " +
                "but you can only see its eastern edge, since directly " +
                "above it the water is darkened into complete blackness. " +
                "Indeed, even where you are swimming now it is " + 
                "somewhat shady.\n");  
        }
     } 

    /* depth related */
    add_item(({"sea", "water", "currents"}),
               "The sea, which extends to a great depth below " + 
               "you, is moving with gentle currents at your " +
               "level. " + w_desc);

    depth = ("Downwards the water extends a very long way, " +
             "so far that you cannot make out the sea bed, " +
             "only a deep, dark impenetrable blue-green. "); 

    set_long(proxim + intro + depth + extra_long); 
    set_tell_time(25); 
    start_creatures();
}

