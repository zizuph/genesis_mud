
/*
    Inherited room for the southwest corner of the lowest level of the 
    Calian water area (sector_1_1_4)

    Coded by Khail, 2/23/96

    Final additions by Maniac 16/7/96
    Added herbs 10-08-97, Jaacar
    Typo corrected, Maniac, 30/5/98

 15                     8  
|------------------------| 
M sb sb sb sb fv fv fv sb| 8
M sb sb sb fv fv f  fv f |      c - currents barrier
| sb sb fv fv f  f  f  fv|      r - island bedrock
| sb sb fv f  f  f  f  f |      sb - sea bed
r sb sb fv fv f  f  f  fv|      f - seaweed forest
| r  sb sb fv fv f  fv fv|      fv - seaweed forest
| r  r  sb sb fv fv fv sb|           visible (edge)
|    r  r  sb sb sb sb sb| 15
|----------r--c--c--c--c-|

*/

#pragma save_binary

inherit "/d/Calia/std/water_room";
inherit "/d/Calia/sea/std/sea_creature_descs"; 
#include <stdproperties.h>
#include "defs.h"
#include KR_HERBSEARCH

#define ROOM_I_SEAWEED_FOREST "_room_i_is_seaweed_forest"


void
make_the_room(string extra_long, int x, int y, int z)
{
    string intro, w_desc, proxim, misc, w_item, seabed_item;

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

    seabed_item = 
        ("The seafloor is covered in a coarse sand, and rather " +
         "unremarkable aside from the occasional sharp stone jutting up.\n");

    add_item(({"stones", "sharp stones", "stone", "sharp stone"}),
        "Here and there, large, sharp stones jut up out of the sea " +
        "bed.\n"); 

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


    /* Current */ 
    if ((y == 15) && (x != 12))  {
        set_short("Swimming north of strong current");
        add_tell("You see what appears to be an old boot flash " +
            "past through the heavy current to the south.\n");

        add_tell("A very panic-stricken looking tuna sails past " +
            "you in the current at a much higher speed than he was " +
            "intended, and apparently prefers, to.\n");

        add_item(({"current"}),
            "To the south a powerful current sweeps away from the " +
            "shore to the east, impossible to pass.\n");

        proxim += ("A fast-moving tidal current is madly churning " +
            "the deep water south of here, progress in that " +
            "direction is not only foolish, but impossible. ");
    }


    /* SW Island bedrock */ 
    if ((x > 11) && (x < 16)) {
        if (x == 12 && y == 15) {
             set_short("Swimming near to bedrock formation"); 
             proxim += "A massive wall formed by bedrock rises " +
                "vertically, and runs from the northwest to " +
                "southeast, preventing any movement to the south " +
                "and west general directions. " +
                "The water seethes and churns here, where the " +
                "southern current rushes against the bedrock. ";
            add_item(({"wall","bedrock"}),
                "The wall rises vertically into the more shallow " +
                "waters above. There's nothing spectacular at all " +
                "about it, just a typical stone cliff, only this " +
                "one is under water.\n");
        }
        else if ((x == 13 && y == 14) || (x == 14 && y == 13)) {
            set_short("Swimming near to bedrock formation"); 
            proxim += ("A massive bedrock formation rises almost " +
                "vertically up out of the seabed and runs roughly " +
                "northwest to southeast, preventing progress " +
                "beyond unless you can walk through solid stone. ");
            add_item(({"wall","formation","bedrock"}),
                "Ancient grey stone, the rock serves as a very real " +
                "boundary to the southwest.\n");
       } 
        else if (x == 15 && y == 12) {
            set_short("Swimming near to bedrock formation"); 
            proxim += ("A massive wall of natural bedrock rises " +
                "vertically up into the water from the seabed. " +
                "Running roughly northwest to southeast, it " +
                "effectively prevents progress in a general " +
                "southwesterly direction. ");
            add_item(({"wall","formation","bedrock"}),
                "Ancient grey stone, the rock serves as a very real " +
                "boundary to the southwest.\n");
        }
        else if ((x == 15) & (y == 11)) {
            proxim += "Off in the depths towards the south, " +
                "you can see a dark shape rising from the seabed. ";
           add_item(({"shape","dark shape"}),
               "It's difficult to tell from here, but it looks " +
               "to be an underwater shelf or wall of some sort.\n");
        }
    }


    /* Underwater volcano */ 
    if (x == 15) {
        if (y == 10) {
             proxim += "Off to the northwest you can see a " +
                 "massive shape of some sort, possibly the " +
                 "the base of a volcano, even. ";
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
         misc = ""; 
    }


    /* Handing of edge of seaweed forest */ 
    if ((x == 8 && (y == 9 || y == 10)) ||
        (x == 9 && (y == 8 || y == 9)))
        misc = "northeastern";
    else if ((x == 8 && (y == 12 || y == 13)) ||
        (x == 9 && (y == 13 || y == 14)))
        misc = "southeastern";
    else if (x == 10 && y == 8)
        misc = "northern";
    else if (x == 10 && y == 14)
        misc = "southern";
    else if ((x == 11 && (y == 8 || y == 9)) ||
        (x == 12 && (y == 9 || y == 10)) ||
        (x == 13 && y == 10))
        misc = "northwestern";
    else if ((x == 11 && (y == 13 || y == 14)) ||
        (x == 12 && (y == 12 || y == 13)) ||
        (x == 13 && y == 12))
        misc = "southwestern";
    else if (x == 13 && y == 11)
        misc = "western";

    if (stringp(misc) && strlen(misc))
    {
        add_item(({"forest","seaweed", "sea weed", "seaweed forest"}),
            "The immense forest-like area of seaweed growth, " +
            "near which you swim at the " + misc + " edge, seems " +
            "be thriving to the degree it dominates the area. " +
            "The seaweed is tall and almost grasslike, except the " +
            "'blades' are easily as broad as your own shoulders, " +
            "and stand several times your height, waving slowly " +
            "in the pulsing current of the sea.\n");
        proxim += "You are swimming at the " + misc + " edge of " +
            "an apparently massive formation of seaweed. It has " +
            "grown to such an amazing size, you find yourself " +
            "comparing it to a forest of oddly shaped, " +
            "green-brown trees. ";
        misc = "";
    }

    /* handling of seaweed forest itself */ 
    if (this_object()->query_prop(ROOM_I_SEAWEED_FOREST))
    {
        set_short("Swimming through seaweed forest"); 
        add_prop(ROOM_I_LIGHT, 0);
        add_prop(ROOM_S_DARK_LONG, "The closeness of the seaweed and the " +
            "silt in the water makes it so dark it's almost impossible " +
            "to see your hand in front of your face.\n");
        add_prop(ROOM_S_DARK_MSG, "The seaweed and silt in the water " +
            "make it too dark to");

        seabed_item = 
           ("The seabed here is mainly a coarse sand, but a thick layer " +
            "of finer silt lies piled up about the roots of the stalks " +
            "of seaweed, trapped by the way the seaweed blocks the sea's " +
            "currents.\n");

        proxim = ("All around you are massive strands of seaweed, as broad " +
            "across at the base as you are across your shoulders and " +
            "several times higher than you, waving in the current. Coloured " +
            "a deep greenish brown, the impression of travelling through a " +
            "very strange forest is almost overwhelming, aside from the " +
            "fact you don't normally swim in a forest. ");

        add_item(({"seaweed", "sea weed"}), (proxim + "\n")); 

        w_desc = ("The seaweed obscures your view in most directions. " +
            "Silt is constantly being whipped up into the water by its " +
            "movement making it very difficult to see anything. ");

        w_item = (w_desc + "\n"); 
        set_search_places(({"seaweed","sea weed","seabed","sea bed"}));
        add_prop(OBJ_I_SEARCH_TIME,3);
        add_prop(OBJ_S_SEARCH_FUN,"herb_search");
        add_herb_file(HERBS+"greenslime");
        add_herb_file(HERBS+"brownslime");
        add_herb_file(HERBS+"angeltear");
        add_herb_file(HERBS+"skullcap");
        add_herb_file(HERBS+"bull_kelp");
        add_herb_file(HERBS+"elkhorn_kelp");
        add_herb_file(HERBS+"laminaria");
    }

    add_item(({"seabed", "floor", "sea floor", 
               "seafloor", "sea bed", "ground"}),
             seabed_item);

    add_item(({"water", "waves", "sea"}), w_item); 

    intro = ("You are swimming in the lowest part of the sea. The sea " +
           "bed is right beneath your feet, but it's much easier to swim " +
           "anyway. ");

    set_long(proxim + intro + w_desc + extra_long);
    start_creatures(); 
}

