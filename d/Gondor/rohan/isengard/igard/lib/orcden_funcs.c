/*
 *  IGARD_LIB + "orcden_funcs.c"
 *
 *  Various functions common to Isengard orcden rooms.
 *
 *  Last modified by Alto, 24 November 2001
 *
 */

#pragma strict_types

inherit "/d/Gondor/std/room.c";

#include "../igard_defs.h"

inherit IGARD_LIB + "deep_funcs.c";

#include <macros.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"
#include "/sys/formulas.h"

/* GLOBAL VARIABLES */

string               *handle    =({});
string               *extradesc =({});
string               Exline, Vehicle;
static object *Yorc  = allocate(3);
static object *Torc  = allocate(3);
static object *Yuruk = allocate(3);
static object *Turuk = allocate(3);


/* PROTOTYPES */

public string        orcden_extraline();
public void          orcden_add_items();
public string        orcden_long_desc();
public void          add_youngorcs_to_room();
public void          add_teenorcs_to_room();
public void          add_younguruks_to_room();
public void          add_teenuruks_to_room();
public int           check_monster();

string
orcden_extraline()
{
    int position;

    string *extradesc =
/*1*/   ({"The floor is covered with a thick layer of straw which seems to "
               + "be surprisingly free of dirt and vermin.", 
/*2*/     "Chains and manacles hang from the walls, but whatever creatures "
               + "they once restrained must have broken free long ago.", 
/*3*/     "It stinks almost beyond bearing, as if hundreds of orcs have "
               + "urinated and defecated here.",
/*4*/     "The floor is covered with a thin layer of soiled and moldy "
               + "straw. Rats scurry away at your approach, darting "
               + "beneath the larger clumps of straw.",
/*5*/     "Your feet slosh through a slimy muck. The stench "
               + "rising up from the muck makes its origin clear.",
/*6*/     "Great cobwebs stream down from the ceiling and brush the "
               + "top of your head. Everything is covered in a fine layer "
               + "of dust, suggesting that this room sat long vacant "
               + "until recently being opened as a nursery for orcs.",
/*7*/     "The straw scattered across the stone floor is wet, mildewed "
               + "and infested with lice, fleas and other vermin.",
/*8*/     "The straw scattered across the stone floor is wet, mildewed "
               + "and infested with lice, fleas and other vermin."});


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
orcden_add_items()
{
    add_prop(ROOM_M_NO_TELEPORT, 1);

    add_item(({"steam", "cloud", "clouds", "wisp", "wisps"}), "Wisps "
        + "and clouds of steam pour through cracks along the walls.\n");
    add_item(({"crack", "cracks"}), "Tiny cracks run from floor to ceiling "
        + "along the walls.\n");
    add_item(({"bone", "bones"}), "There are numerous bones scattered "
        + "here and there, wedged into cracks on the floor and walls. Some "
        + "of them appear to be animal bones, but others look human.\n");
    add_item(({"debris"}), "Wedged into cracks on the floor and walls "
        + "are a variety of things which have been chewed and gnawed "
        + "beyond recognition.\n");

    switch (Vehicle)
    {
    case "lone":
        add_item(({"straw"}), "The straw looks fresh and clean. It must "
            + "have been changed recently.\n");
        break;

    case "ltwo":
        add_item(({"chain", "chains"}), "The chains are rusted and "
            + "broken.\n");
        add_item(({"manacle", "manacles"}), "The manacles at the "
            + "ends of the chains have been snapped and broken with "
            + "great force.\n");
        break;

    case "lthree":
        break;

    case "lfour":
        add_item(({"straw", "filthy straw"}), "Filthy straw is scattered "
            + "about the floor. It seems to be the home for a number of "
            + "squeaking rodents.\n");
        add_item(({"clump", "clumps"}), "Here and there are larger clumps "
            + "of the filthy straw. They seem to be the home of numerous "
            + "rats.\n");
        add_item(({"rat", "rats", "rodent", "rodents"}), "Out of the "
            + "corner of your eye, you occasionaly catch a glimpse of a "
            + "rat scurrying about in the straw.\n");
        break;

    case "lfive":
        add_item(({"muck", "slimy muck"}), "As your feet disappear into "
            + "the slimy muck, you find yourself hoping it is not composed "
            + "of what you think it is. The stench rising from it, however, "
            + "gives you a sinking feeling your thoughts are right on the "
            + "mark.\n");
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
    case "leight":
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
orcden_long_desc()
{
    string extra;

    extra = Exline;

    return "The air in this room is oppressively hot and muggy, due largely "
        + "to the steam flowing in through cracks in the walls. " 
        + extra + " Bones and other debris are scattered here and there "
        + "about the room.\n";
}


public void
add_youngorcs_to_room()
{
    clone_npcs(Yorc,  IGARD_NPC + "igard_young_orc",  -1.0);
}



public void
add_teenorcs_to_room()
{
    clone_npcs(Torc,  IGARD_NPC + "igard_teen_orc",  -1.0);
}



public void
add_younguruks_to_room()
{
    clone_npcs(Yuruk,  IGARD_NPC + "igard_young_uruk",  -1.0);
}


public void
add_teenuruks_to_room()
{
    clone_npcs(Turuk,  IGARD_NPC + "igard_teen_uruk",  -1.0);
}


public int
check_monster()
{
    if (TP->id("_igard_monster"))
    {
    return 1;
    }

    if (TP->query_attack() != 0)
    {
    TP->catch_tell("You start to run that direction, but quickly realise "
        + "that doing so would invite a quick death from behind.\n");
    return 1;
    }

    write("With a sigh of relief, you leave the den behind you.\n");
    return 0;
}
