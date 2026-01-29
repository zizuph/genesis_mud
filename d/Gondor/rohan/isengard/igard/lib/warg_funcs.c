/*
 *  IGARD_LIB + "warg_funcs.c"
 *
 *  Various functions common to Isengard warg rooms.
 *
 *  Last modified by Alto, 24 November 2001
 *
 */

#pragma strict_types

inherit "/d/Gondor/std/room.c";
inherit "/d/Gondor/common/lib/drink_water.c";

#include "../igard_defs.h"

inherit IGARD_LIB + "deep_funcs.c";

#include <macros.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"
#include "/d/Gondor/std/tell.c"
#include "/sys/formulas.h"

/* GLOBAL VARIABLES */

string               *handle    =({});
string               *extradesc =({});
string               Exline, Vehicle;
static object *Warg  = allocate(3);
static object *Wolf  = allocate(3);
static object *Puppy = allocate(5);


/* PROTOTYPES */

public string        warg_extraline();
public void          warg_add_items();
public string        warg_long_desc();
public void          add_wargs_to_room();
public void          add_wolves_to_room();
public void          add_pups_to_room();


string
warg_extraline()
{
    int position;

    string *extradesc =
/*1*/   ({"The floor is covered with a thick layer of straw which seems to "
               + "be surprisingly free of dirt and vermin. The air is warm, "
               + "but not too stuffy or humid. In one corner there is an "
               + "especially large clump of straw.", 
/*2*/     "Fur seems to be everywhere you look. It covers the floor, the "
               + "walls and the ceiling. The warm air is filled with swirling "
               + "clouds of down and dander, making your nose itch "
               + "uncontrollably.", 
/*3*/     "A strong kennel scent wafts through the air. From the smell of "
               + "things, hundreds, if not thousands, of dogs or wolves "
               + "have slept, urinated and defecated here.",
/*4*/     "The floor is covered with a thin layer of soiled and moldy "
               + "straw. Rats scurry away at your approach, darting "
               + "beneath the larger clumps of straw in the corners.",
/*5*/     "Although there is no straw in this room, large bundles of cloth "
               + "have been torn into strips and scattered about the floor. "
               + "A great heap of cloth has been piled into one corner.",
/*6*/     "Great cobwebs stream down from the ceiling and brush the "
               + "top of your head. Everything is covered in a fine layer "
               + "of dust, suggesting that this room sat long vacant "
               + "until recently being opened to house breeding wargs.",
/*7*/     "The straw scattered across the stone floor is wet, mildewed "
               + "and infested with lice, fleas and other vermin.",
/*8*/     "The floor is covered with a thick layer of straw which seems to "
               + "be surprisingly free of dirt and vermin. The air is warm, "
               + "but not too stuffy or humid. In one corner there is an "
               + "especially large clump of straw."});


    string *handle =
/*1*/     ({"lone", 
/*2*/       "ltwo", 
/*3*/       "lthree",
/*4*/       "lfour",
/*5*/       "lfive",
/*6*/       "lsix",
/*7*/       "lseven",
/*8*/       "leight"});


    Exline = ONE_OF_LIST(extradesc);

    position = member_array(Exline, extradesc);

    Vehicle = handle[position];

    return Vehicle;

}


void
warg_add_items()
{
    add_prop(ROOM_M_NO_TELEPORT, 1);
    set_drink_from("basin");

    add_prop(OBJ_I_CONTAIN_WATER, -1);

    add_item(({"basin", "stone basin"}), "The stone basin is filled with "
        + "surprisingly clean water. Perhaps it would not kill you if "
        + "you were to drink from it.\n");
    add_item(({"water", "water in basin", "water in the basin"}), "For "
        + "a fortress filled with orcs and other maggot folk, the water "
        + "here is astonishingly clean.\n");
    switch (Vehicle)
    {
    case "lone":
    case "leight":
        add_item(({"layer", "straw", "layer of straw"}), "The layer of "
            + "straw on the floor looks fresh. It is probably changed "
            + "regularly by the keepers of the den.\n");
        add_item(({"corner", "clump", "large clump", "clump of straw",
            "nest"}), "It looks like a female warg pushed a great deal "
            + "of straw into one corner to make a nest for her pups.\n");
        break;

    case "ltwo":
        add_item(({"fur", "dander", "down"}), "Fur seems to be everywhere "
            + "you look. It also seems to be finding its way into your "
            + "nose. The need to sneeze is driving you rather insane.\n");
        add_item(({"water", "water in basin", "water in the basin"}), "When "
            + "you take a closer look, you see the water has a fair amount "
            + "of fur floating in it. Yuck!\n");
        add_item(({"cloud", "clouds"}), "Clouds of dander and down float "
            + "around the room, getting into everything, especially your "
            + "nose.\n");
        break;

    case "lthree":
        break;

    case "lfour":
        add_item(({"straw", "filthy straw"}), "Filthy straw is scattered "
            + "about the floor. It seems to be the home for a number of "
            + "squeaking rodents.\n");
        add_item(({"clump", "clumps", "corner"}), "The straw is pushed "
            + "into the corners in large clumps.\n");
        add_item(({"rat", "rats", "rodent", "rodents"}), "Out of the "
            + "corner of your eye, you occasionaly catch a glimpse of a "
            + "rat scurrying about in the straw.\n");
        break;

    case "lfive":
        add_item(({"cloth", "strips"}), "Looking carefully at the cloth, "
            + "you realize that this is the homespun used by the peasants "
            + "of Rohan to make garments and bedclothes. Now they are "
            + "used by the folk of Isengard as bedding for their wargs.\n");
        add_item(({"heap", "corner", "great heap"}), "A great heap of "
            + "cloth has been piled into one corner, where it serves as "
            + "nesting material for bitch wargs.\n");
        break;

    case "lsix":
        add_item(({"cobweb", "cobwebs", "great cobweb", "great cobwebs"}), 
            "Great dusty cobwebs dangle from the ceiling, brushing your "
            + "face as you move about the room.\n");
        add_item(({"dust", "layer", "fine layer of dust", 
            "layer of dust"}), "A fine layer of dust coats everything "
            + "in the room. You kick up small clouds of it as you move "
            + "about the room.\n");
        break;

    case "lseven":
        add_item(({"straw"}), "The straw beneath your feet is covered "
            + "in mildew and looks entirely unsavoury.\n");
        add_item(({"lice", "louse", "fleas", "flea", "vermin"}), "The "
            + "damp straw is literally crawling with a revolting "
            + "array of lice and fleas.\n");
        break;

    default:
        write("This is one of those wrongness in space and time messages, "
            + "which means you should probably file a bugreport in this "
            + "room.\n");
        break;
    }
}


string
warg_long_desc()
{
    string extra;

    extra = Exline;

    return "The room you are standing in has a ceiling so low that you "
        + "need to duck your head slightly to avoid brushing against it. " 
        + extra + " A stone basin rests along one wall.\n";
}


public void
add_wargs_to_room()
{
    clone_npcs(Warg,  IGARD_NPC + "igard_warg",  -1.0);
}



public void
add_wolves_to_room()
{
    clone_npcs(Wolf,  "/d/Gondor/common/npc/wolf",  -1.0);
    Wolf->set_restrain_path(IGARD_DEEP_WARG);
}



public void
add_pups_to_room()
{
    clone_npcs(Puppy,  IGARD_NPC + "igard_wolf_pup",  -1.0);
}