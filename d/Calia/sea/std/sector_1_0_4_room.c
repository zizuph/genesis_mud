
/*
    Inherited room for the northwest sector of the lowest level of the
    Calian sea area (sector 1_0_4). 

    Coded by Khail 23/2/96

    Final additions by Maniac 29/6/96 


i 15                   8 
|-------r--r--c--c--c--c-|
|    r  r  sb sb sb sb sb| 0       
| r  r  sb sb sb sb sb sb|          c - currents barrier 
| r  sb sb sb sb sb sb sb|          sb - sea bed
r sb sb sb sb sb sb sb sb|          r - island bedrock 
| sb sb sb sb sb sw sw sw|          M - Mt Pyros low east
| sb sb sb sb sf sw SW sw|          sw - wreck visible
M sb sb sb sb sb sw sw sw|          SW - Over wreck (connect here)  
M sb sb sb sb sb sb sb sb| 7        
|------------------------|

*/

#pragma save_binary

inherit "/d/Calia/std/water_room";
inherit "/d/Calia/sea/std/sea_creature_descs"; 

#include <stdproperties.h>

void
make_the_room(string extra_long, int x, int y, int z)
{
    string intro, w_desc, proxim, misc, w_item;

    proxim = "";

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

    w_item = ("You are completely surrounded by the dark blue water, " +
     "and you reluctantly consider the irony of something so seemingly " +
     "peaceful being so readily capable of ending your life.\n");

    w_desc = ("The water here is a deep blue, hardening into midnight " +
        "black in the distance where only a glimmer of light filters " +
        "through. As comfortable as the water seemed at higher points, " +
        "it is uncomfortably cold here. ");

    add_item(({"seabed", "floor","seafloor","sea bed","ground"}),
        "The seafloor is covered in a coarse sand, and rather " +
        "unremarkable aside from the occasional sharp stone jutting up.\n"); 

     add_item(({"stones", "sharp stones", "stone", "sharp stone"}),
        "Here and there, large, sharp stones jut up out of the sandy " +
        "seabed. Many are covered by various forms of sea life, but " +
        "primarily a variety of mollusks.\n");

     add_item(({"mollusks","barnacles","mussels"}),
         "A variety of mollusks are firmly attached to the " +
         "stones, primarily barnacles and deep water mussels.\n");

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


    /* Shipwreck descs */ 
    if ((x < 12) && (x > 7))  {
        if (x == 8 && y == 4)
            misc = "southwest";
        else if (x == 8 && y == 6)
            misc = "northwest";
        else if (x == 9 && y == 4)
            misc = "south";
        else if (x == 9 && y == 6)
            misc = "north";
        else if (x == 10 && y == 4)
            misc = "southeast";
        else if (x == 10 && y == 6)
            misc = "northeast";
        else if (x == 11 && y == 5)
            misc = "east";

        if (stringp(misc) && strlen(misc)) {
            add_item(({"ship","shipwreck","wreck","ship wreck"}),
                "Far off to the " + misc + ", you can dimly make out " +
                "the shape of what must be a shipwreck of some sort.\n");
            proxim += ("In the dim depths to the " + misc + 
                ", you see the shape of what appears to be a " +
                "shipwreck of some sort. ");
            misc = "";
        }

        if (x == 8 && y == 5)
            misc = "west";
        else if (x == 10 && y == 5)
            misc = "east";

        if (stringp(misc) && strlen(misc)) {
            add_item(({"ship","shipwreck","wreck","ship wreck"}),
                "Just to the " + misc + ", you see the dark shape of " +
                "a shipwreck.\n");
            proxim += ("Nearby to the " + misc + ", you can see a dark " +
                "curved shaped, which appears to be a shipwreck of " +
                "some kind. ");
            misc = "";
        }

        /* At shipwreck */ 
        if (x == 9 && y == 5) {
            set_short("Swimming over ship wreck"); 
            add_item(({"ship","shipwreck","wreck","ship wreck"}),
                "Before you rests the decaying hull of a ship that " +
                "appears to have sunk long ago. The hull planks " +
                "have begun to decay, and a large hole gapes in the " +
                "bow.\n");
            add_item(({"hull"}),
                "The hull of the ancient shipwreck is riddled with " +
                "rot and wormholes.\n");
            add_item(({"keel"}),
                "The keep cuts a smooth, dark curve through the dark " +
                "water, except for the occasional spot where small " +
                "plants have grown.\n");
            add_item(({"hole"}),
                "Looking closely, you realize the hole wasn't caused " +
                "from an impact of any kind, but looks more like the " +
                "wood that held the figurehead in place rotted away " +
                "and the weight of the heavy carving tore it away " +
                "from the hull. It's a pretty fair size, you'd have " +
                "no problem swimming through it.\n");
            add_item(({"mound","mast"}),
                "Brushing aside some of the silt from the mound, you " +
                "realize that this is the remains of the ship's main " +
                "mast, torn aside as it sank to the bottom.\n");

            proxim += ("Upon the seabed before you lies the " +
                "hull of a ship that sank long ago. A "+
                "large, ragged hole gapes open in the hull beneath " +
                "the bowsprit. Across the seabed nearby, you see a " +
                "long, straight mound in the sand, a few inches high " +
                "which seems to start beneath the wreck and extend " +
                "away from it. ");
           }
     }

    /* Nw island bedrock */ 
    if ((x > 11) && (x < 16)) {
        if (x == 12 && y == 0) {
             set_short("Swimming near to bedrock formation");
             proxim += "A massive wall formed by bedrock rises " +
                "vertically, and runs from the northeast and " +
                "southwest, preventing any movement to the north " +
                "and west general directions. " +
                "The water seethes and churns here, where the " +
                "northern current rushes against the bedrock. ";
            add_item(({"wall","bedrock"}),
                "The wall rises vertically into the more shallow " +
                "waters above. There's nothing spectacular at all " +
                "about it, just a typical stone cliff, only this " +
                "one is under water.\n");
        }
        else if ((x == 13 && y == 1) || (x == 14 && y == 2)) {
            set_short("Swimming near to bedrock formation");
            proxim += ("A massive bedrock formation rises almost " +
                "vertically up out of the seabed and runs roughly " +
                "northeast and southwest, preventing progress " +
                "beyond unless you can walk through solid stone. ");
            add_item(({"wall","formation","bedrock"}),
                "Ancient grey stone, the rock serves as a very real " +
                "boundary to the northwest.\n"); 
        }
        else if (x == 15 && y == 3) {
            set_short("Swimming near to bedrock formation");
            proxim += ("A massive wall of natural bedrock rises " +
                "vertically up into the water from the seabed. " +
                "Running roughly northeast to southwest, it " +
                "effectively prevents progress in a general " +
                "northwesterly direction. "); 
            add_item(({"wall","formation","bedrock"}),
                "Ancient grey stone, the rock serves as a very real " +
                "boundary to the northwest.\n"); 
        }
        else if ((x == 15) & (y == 4)) {
            proxim += "Off in the depths towards the north, " +
                "you can see a dark shape rising from the seabed. ";
           add_item(({"shape","dark shape"}),
               "It's difficult to tell from here, but it looks " +
              "to be an underwater shelf or wall of some sort.\n");
        }
    }


    if (x == 15) { 
        if (y == 5) {
             proxim += "Off to the southwest you can see a " +
                 "massive shape of some sort, possibly the " +
                 "base of a volcano, even. ";
             add_item(({"shape","volcano","base"}),
                  "You really can't tell from here, the water just " +
                  "is too dark for any real identification, but " +
                  "your best guess places it as the base of a " +
                  "large, conical shaped volcano.\n");
        }
       else if ((y > 5) && (y < 10)) {
           set_short("Swimming near base of underwater volcano"); 
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

           proxim += ("To your " + misc + " the base of " +
              "a great underwater volcano rises up. Its sheer size " +
              "is ominous, when it is active it must carry an " +
              "awesome destructive power. ");
           add_item(({"base", "volcano", "underwater volcano"}),
              "Its shape and rock structure is that of a volcano, " +
              "and the water nearby provides another clue. This volcano " +
              "is absolutely huge, when it is active it must carry " +
              "an awesome destructive power.\n");
         }
    }

    if ((y == 0) && (x != 12))  {
        set_short("Swimming south of strong current");

        add_tell("You see what appears to be an old boot flash " +
            "past through the heavy current to the north.\n");

        add_tell("A very panic-stricken looking tuna sails past " +
            "you in the current at a much higher speed than he was " +
            "intended, and apparently prefers, to.\n");

        add_item(({"current", "tidal current"}),
            "To the north a powerful current sweeps away from the " +
            "shore to the east, impossible to pass.\n");

        proxim += ("A fast-moving tidal current is madly churning " +
            "the deep water north of here, progress in that " +
            "direction is not only foolish, but impossible. ");
    }

    intro = ("You are swimming in the lowest part of the sea. The sea " +
           "bed is right beneath your feet, but it's much easier to swim " +
           "anyway. ");

    add_item(({"water", "waves", "sea"}), w_item);

    set_long(proxim + intro + w_desc + extra_long);
    start_creatures(); 
}

