
/* 
    Minotaur raiding ship.

    Saved in /d/Krynn/south_courrain/living/ so it can be
    spawned through the /d/Krynn/south_courrain/courrain_placer.c

    Arman, Feb 2021
 */ 
#include "/d/Krynn/common/defs.h"
#include "../local.h"
#include "/d/Krynn/std/boats/std_boat_defs.h"

#pragma save_binary

inherit "/d/Krynn/std/boats/example_medium_boat"; 

#include <language.h>

#define CAPTAIN (LIVING + "pirate_captain")
#define PIRATE  "/d/Krynn/turbidus_ocean/living/pirate"

#define ROWER_DESC ({  "sleek", "swift", "menacing", "trim", \
                         "black", "black-sailed", "grim" })

#define ROWER_DESIGN ({ "skull over crossbones",  \
                        "flaming jolly roger", \
                        "parrot with an eye-patch", \
                        "crossed sabres dripping blood", \
                        "screaming skull", \
                        "dwarven pirate", \
                        "drunken corsair", \
                        "naked maiden", \
                        "deep sea dragon", \
                        "coy mermaid" })

string bd, d2, d3; 

void
create_boat()
{
    string *rc = ROWER_DESC;
    string *rd = ROWER_DESIGN;
 
    d2 = rc[random(sizeof(rc))];
    d3 = rd[random(sizeof(rd))];

    set_name("ship"); 
    set_adj(({d2, "pirate"})); 
    set_short(d2 +" pirate ship"); 
    set_long("@@boat_long_desc"); 

    // Sets the sailing skill level required to sail the ship
    set_sailing_difficulty(DIFFICULTY_JOURNEYMAN);
    // Sets the ship size as defined in std_boat_defs.h
    set_ship_size(SCHOONER);
    // Sets the maximum number of passengers the ship can carry
    set_max_passengers(10);

    add_item(({"picture", "side"}), "While beautifully designed, you see nothing " +
                                   "special about the picture.\n");

    set_alarm(0.1, 0.0, &config_boat_inside());
}

string
boat_long_desc()
{
    mixed * flag_desc = query_boat_in()->query_flag_desc();

    if(sizeof(flag_desc))
    {
        return "A small " +d2+ " pirate ship, commonly sailed by pirates " +
            "of the Bloodsea in lightning raids on merchant vessels and port " +
            "towns from Nordmaar to Balifor. On its side is painted a picture of a " +
            LANG_ADDART(d3) + ". " +flag_desc[2]+ "\n";
    }
    return "A small " +d2+ " pirate ship, commonly sailed by pirates " +
        "of the Bloodsea in lightning raids on merchant vessels and port " +
        "towns from Nordmaar to Balifor. On its side is painted a picture of a " +
        LANG_ADDART(d3) + ".\n";
}


// When the ensign is hoisted from within the boat this function is called.
public void
update_boat_descriptions()
{
    mixed * flag_desc = query_boat_in()->query_flag_desc();

    if(sizeof(flag_desc))
    {
        query_boat_in()->set_long("You are inside a Bloodsea pirate ship. " +
            "Designed by minotaur shipwrights, this craft can be piloted by a single " +
            "sailor, yet is sturdy enough to handle the high seas of the " +
            "Courrain Ocean and Bloodsea of " +
            "Istar. A single mast rises out of the middle of the deck, its billowing " +
            "canvas sail unfurled, ready for swift sailing. " +flag_desc[2]+ "\n");
        query_boat_in()->add_item( flag_desc[3] , flag_desc[2] + "\n" );

        return;

    }

    query_boat_in()->set_long("You are inside a Bloodsea pirate ship. " +
        "Designed by minotaur shipwrights, this craft can be piloted by a single " +
        "sailor, yet is sturdy enough to handle the high seas of the Courrain " +
        "Ocean and Bloodsea of " +
        "Istar. A single mast rises out of the middle of the deck, its billowing " +
        "canvas sail unfurled, ready for swift sailing.\n");
}

void
config_boat_inside()
{
    ::config_boat_inside();

    string pirate_long = "Before you stands a drunken bloodthirsty pirate, " +
        "itching for battle and longing for the loot found on the fat " +
        "merchant ships that sail the high seas.\n";

    object s1 = clone_object(CAPTAIN);
    object s2 = clone_object(PIRATE);
    object s3 = clone_object(PIRATE);

    s1->move_living("into his ship", query_boat_in());
    s2->move_living("into his ship", query_boat_in());
    s2->set_long(pirate_long);
    s3->move_living("into his ship", query_boat_in());
    s3->set_long(pirate_long);

    query_boat_in()->set_owner(s1);

    query_boat_in()->set_short("aboard a " + d2 +" pirate ship");
    query_boat_in()->set_long("You are inside a Bloodsea pirate ship. " +
        "Designed by minotaur shipwrights, this craft can be piloted by a single " +
        "sailor, yet is sturdy enough to handle the high seas. A single mast " +
        "rises out of the middle of the deck, its billowing " +
        "canvas sail unfurled, ready for swift sailing.\n");

    query_boat_in()->add_item(({"sail", "canvas sail", "billowing canvas sail", 
        "billowing sail"}), "A canvas sail, billowing with the wind.\n"); 
    query_boat_in()->add_item(({"mast", "single mast"}), 
        "A solid mast rises out of the middle of the deck, sturdy enough " +
        "to handle the strong winds common on the Bloodsea of Istar and Courrain " +
        "Ocean.\n");
    query_boat_in()->add_item("ship", "It is a small sailing ship, a quick " +
       "vessel around the coastlines, however not suitable for taking a " +
       "lot of passengers!\n");

}

