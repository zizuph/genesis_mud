
/*
    Inherited room used in southeast sector of the third level of the
    calian sea area (sector_0_1_3). 

    Coded by Khail, 23/2/96
    Copied over from adapted northeast sector by Maniac, 27/5/96

 7                     0
|------------------------|
| s  s sb  u             | 8
| s  s sb  u             |
| s  s sb  u             |      s - open sea
| s  s sb  u             |      u - rising sea bed
| s  s sb  u             |      sb - sea bed
| s  s sb  u             |
| s  s sb  u             |
| s  s sb  u             | 15
|------------------------|

*/

#pragma save_binary

inherit "/d/Calia/std/water_room";
inherit "/d/Calia/sea/std/sea_creature_descs";
#include <stdproperties.h>

void
make_the_room(string extra_long, int x, int y, int z)
{
    string intro, w_desc, proxim, w_item;  

    set_short("Swimming deep in the sea");
    proxim = ""; 

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
        w_desc += ("The light filtering down through the shallower levels " +
                  "shimmers and shifts due to waves on the surface. ");  

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

    switch (x)
    {
        case 5 :  
            add_tell("You catch a glimpse of a small crab " +
                "scuttling up the sea bed to the east.\n");
            add_tell("A sudden surge of water rushes past you from " +
                "up the slope. You flail helplessly for a moment, but " +
                "finally upright yourself none the worse for wear after " +
                "the surge passes.\n");

            add_item(({"bottom", "sea bed" }),
                "The sea bed rises steeply upwards to the east, " +
                "marking the extent of the deepest part of the " +
                "sea.\n");

            w_item = ("The water is dark, and fairly silty here, " +
                "being pulled down the seabed by the riptide " +
                "from the shore high above.\n");

            proxim = "To the east, the sea bed rises sharply upwards " +
                "towards the distant shore high above. ";

            break;

        case 6 :
            add_tell("You feel the water shift around you, the dispersed " +
                "remains of a riptide current.\n");
            add_tell("A small, brightly coloured fish darts up in front " +
                "of you, stares at you curiously for a moment then " +
                "flickers out of sight.\n");
        break;
    }

    add_item(({"sea", "water", "waves"}), w_item); 

    intro = "You are swimming deep in the sea, immersed in a world of " +
        "blues and greens, devoid of sound except the rush of the " +
        "water past your ears. ";

    set_long(proxim + intro + w_desc + extra_long);
    start_creatures(); 
}

