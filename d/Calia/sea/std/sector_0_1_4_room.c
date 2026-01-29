
/*
    Inherited room for the southeast sea bed sector in the Calian sea area
    (sector_0_1_4). 

    Coded by Khail, 23/2/96
    Modified by Maniac 25/6/96

  7                    0                   
|------------------------|      
| sb sb  u               | 8     
| sb sb  u               |
| fv sb  u               |     c - currents barrier
| fv sb  u               |     sb - sea bed
| fv sb  u               |     u - rising sea bed
| sb sb  u               |     fv - seaweed forest
| sb sb  u               |          visible
| sb sb  u               | 15
|-c--c-------------------|

*/

#pragma save_binary

inherit "/d/Calia/std/water_room";
inherit "/d/Calia/sea/std/sea_creature_descs";

#include <stdproperties.h>

void
make_the_room(string extra_long, int x, int y, int z)
{
    string intro, w_desc, proxim;

    set_short("Swimming at the bottom of the sea");

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

    w_desc = "The water here is a deep blue, hardening into midnight " +
        "black in the distance where only a glimmer of light filters " +
        "through. As comfortable as the water seemed at higher points, " +
        "it is uncomfortably cold here. ";

    proxim = ""; 

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
        case 6 :  
            set_short("Swimming near the rising sea bed");
            add_tell("You catch a glimpse of a small crab " +
                "scuttling up the seabed to the east.\n");
            add_tell("A sudden surge of water rushes past you from " +
                "up the slope. You flail helplessly for a moment, but " +
                "finally upright yourself none the worse for wear after " +
                "the surge passes.\n");

            add_item(({"bottom", "sea bed" }),
                "The seabed rises steeply upwards to the east, " +
                "marking the extent of the deepest part of the " +
                "sea.\n");
            add_item(({"sea", "water", "waves"}), 
                "The water is dark, and fairly silty here, " +
                "being pulled down the seabed by the riptide " +
                "from the shore high above.\n");

            proxim = "To the east, the sea bed rises sharply upwards " +
                "towards the distant shore high above. ";

            break;

        case 7 :
            add_tell("You feel the water shift around you, the dispersed " +
                "remains of a riptide current.\n");
            add_tell("A small, brightly coloured fish darts up in front " +
                "of you, stares at you curiously for a moment then " +
                "flickers out of sight.\n");

            add_item(({ "bottom", "sea bed", "ground", "seabed" }),
                 "The sea bed is mainly a heavy, coarse sand, interspersed " +
                 "with a few small stones and the odd crab.\n");
            add_item(({"sea", "water", "waves"}),
                 "The surrounding water is dark, almost black, but quite " +
                 "clear.\n");
    
            if ((y > 9) && (y < 13)) {
                proxim = "Not so far away, you can make out the shapes " +
                    "of what appears to be a seaweed forest, and you are " +
                    "swimming to the east of it. ";
                add_item(({"seaweed","weeds","forest","seaweed forest"}),
                    "You are swimming not far to the east " +
                    "of a massive seaweed forest. It's hard to tell " +
                    "from here, but the seaweed seems to be a normal " +
                    "variety, but has grown to unbelievable proportions, " +
                    "giving this ancient bed of seaweed the appearance " +
                    "of an aquatic forest.\n");
            }
        break;
    }

    if (y == 15)
    {
        set_short("Swimming north of strong current"); 
        add_tell("You see what appears to be an old boot flash " +
            "past through the heavy current to the south.\n");
        add_tell("A very panic-stricken looking tuna sails past " +
            "you in the current at a much higher speed than he was " +
            "intended, and apparently prefers, to.\n");

        add_item(({"current"}),
             "To the south a powerful current sweeps away from the " +
             "shore to the east, impossible to pass.\n");

        proxim += "A fast-moving tidal current is madly churning " +
            "the deep water south of here, progress in that " +
            "direction is not only foolish, but impossible. ";
    }

    intro = "You are swimming in the lowest part of the sea. The sea bed " +
        "is right beneath your feet, but it's much easier to swim " +
        "anyway. ";
    set_long(proxim + intro + w_desc + extra_long);

    start_creatures(); 
}

