
/* 
   Inherited room northeast sector of level 1 of the Calian sea area, 
   (sector_0_0_1). 

   Coded by Maniac April 1996

  7                    0 
|------------------------|
| s  s  s  s  s          | 0     r - rock barrier
| s  s  s  s  s sb       |       s - open sea
| s  s  s  s  s sb  r    |
| s  s  s  s  s sb  r    |       u - rising sea bed
| s  s  s  s  s sb  u    |      
| s  s  s  s  s sb  u    |       sb - sea bed
| s  s  s  s  s sb  u    |
| s  s  s  s  s sb  u    | 7
|------------------------|

*/

#pragma save_binary 

inherit "/d/Calia/std/water_room";
inherit "/d/Calia/sea/std/sea_creature_descs"; 


void
make_the_room(string extra_long, int x, int y, int z)
{
    string intro, depth, w_desc, proxim; 
    int rocks_present;

    set_short("Swimming not far below the surface");

    intro = ("You are swimming not far below the surface of blue-green " +
             "sea, suspended in a crystal clear but animated aquatic " +
             "world. ");

    w_desc = ("The water is a clear blue-green and feels just the " +
              "right temperature.\n");

    proxim = "";

    add_sea_creature("red herring"); 
    set_presence_chance("red herring", 4); 
    add_sea_creature("frog fish");
    set_presence_chance("frog fish", 7); 
    add_sea_creature("flying fish");
    set_presence_chance("flying fish", 7); 
    add_sea_creature("needle fish");  
    set_presence_chance("needle fish", 7); 
    add_sea_creature("yellowtail fish");  
    set_presence_chance("yellowtail fish", 7); 
    add_sea_creature("aurelia aurita"); 
    set_presence_chance("aurelia aurita", 5); 
    add_sea_creature("chrysaora isosceles"); 
    set_presence_chance("chrysaora isosceles", 5); 
    add_sea_creature("pelagia noctiluca");
    set_presence_chance("pelagia noctiluca", 5); 
    add_sea_creature("cyanea lamarki"); 
    set_presence_chance("cyanea lamarki", 5); 
    add_sea_creature("rhizostoma pulmo"); 
    set_presence_chance("rhizostoma pulmo", 5); 

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

    /* depth related */
    switch (x) {
        case 0 : 
        case 1 : 
        case 2 : depth = "The sandy sea bed is just below you. ";  
                 add_item(({"sea", "water", "currents"}), 
                           "The sea, quite shallow here, is moving " + 
                           "with gentle currents. " + w_desc); 
                 add_item(({"sea bed", "sandy sea bed", "bottom"}), 
                           "The sea bed, just below you, is white and " +
                           "sandy. You notice sea weed, little crabs, " +
                           "star fish and other life on it.\n"); 
                 add_item(({"sea weed", "little crabs", "crabs", "star fish"}),
                           "One of the many humbler forms of sea life " +
                           "that exist down here.\n"); 
                 if ((y < 4) && (y > 1))  {
                     proxim += ("To your east you see the base of some " +
                           "large craggy rocks. "); 
                     rocks_present = 1; 
                 }
                 if ((y > 3) && (y < 14)) 
                     proxim += ("To your east the sea bed rises. "); 
                 if (y > 12) {
                     proxim += ("Just southeast of you, running from " +
                           "southwest to northeast, are the " + 
                           "lower sections of some large craggy rocks. "); 
                     rocks_present = 1; 
                 }
                 break;
        case 3 :  
                 if (y == 15)  { 
                     proxim += ("Just southeast of you, running from " +
                           "southwest to northeast, are the " + 
                           "lower sections of some large craggy rocks. "); 
                     rocks_present = 1; 
                 }
                /* No break here as we want to carry on into 4 */ 
        case 4 : 
                 depth = ("Looking down, you can make out the sea bed " +
                          "a few fathoms below you. ");
                 add_item(({"sea", "water", "currents"}),
                           "The sea, fairly deep here, is moving " +
                           "with gentle currents. " + w_desc);
                 add_item(({"sea bed", "bottom"}),
                           "The sea bed is a few fathoms below you. Even " +
                           "from here you can make out that it is sandy " +
                           "and decorated by simple forms of sea life.\n");
                 break;
        case 5 : 
                 add_item(({"sea", "water", "currents"}),
                           "The sea, which extends to a great depth below " + 
                           "you, is moving with gentle currents at your " +
                           "level. " + w_desc);
                 add_item(({"sea bed", "bottom"}),
                           "The sea bed is quite a long way below you, " +
                           "it looks like a rough blanket as you can't " +
                           "make out any details.\n");
               depth = ("Looking down, you see that water is quite deep " +
                        "here. A darker blue-green gradually takes over " +
                        "and you can only just make out the sea bed a long " +
                        "way below. "); 
                 break;
        case 6 : 
        case 7 : 
                 add_item(({"sea", "water", "currents"}),
                           "The sea, which extends to a great depth below " + 
                           "you, is moving with gentle currents at your " +
                           "level. " + w_desc);
                 depth = ("Downwards the water extends a very long way, " +
                          "so far that you cannot make out the sea bed, " +
                          "only a deep, dark impenetrable blue-green. "); 
                 break;
    }

    if (rocks_present) 
         add_item(({"rocks", "large craggy rocks", "large rocks", 
                   "craggy rocks" }), 
             ("They are large craggy rocks that extend outwards " +
              "in irregular patterns along much of the coast.\n")); 

    set_long(intro + depth + proxim + extra_long); 
    set_tell_time(25); 
    start_creatures();
}

