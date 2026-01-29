
/* 
    Rowing boat, varying types. 

    Coded by Maniac, 30/7/96

    Borrowed by Arman Kharas 14/4/04
 */ 

/**
 * Navarre Feb 4th 2007, fixed typos on boats
 */

#pragma save_binary

#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/std/boats/std_boat_defs.h"
#include <language.h>

inherit STD_BOAT_OUT; 

#define ROWER_DESC ({  "sleek", "swift", "barnacled", "trim", \
                         "black", "white-sailed", "elegant" })

#define ROWER_DESIGN ({ "beautiful mermaid",  \
                        "vicious sea snake", \
                        "gangling octopus", \
                        "terrifying shark", \
                        "sleek dolphin", \
                        "speeding swordfish", \
                        "draconian head on a spear", \
                        "proud minotaur warrior", \
                        "deep sea dragon", \
                        "drunken dwarf" })

string bd, d2, d3; 

void
create_boat()
{
    string *rc = ROWER_DESC;
    string *rd = ROWER_DESIGN;
 
    d2 = rc[random(sizeof(rc))];
    d3 = rd[random(sizeof(rd))];

    set_name("ship"); 
    set_adj(({d2, "sailing"})); 
    set_short(d2 +" sailing ship"); 
    set_long("@@boat_long_desc"); 

    add_item(({"picture", "side"}), "While beautifully designed, you see nothing " +
                                   "special about the picture.\n");

    // Sets the sailing skill level required to sail the ship
    set_sailing_difficulty(DIFFICULTY_JOURNEYMAN);
    // Sets the ship size as defined in std_boat_defs.h
    set_ship_size(SCHOONER);
    // Sets the maximum number of passengers the ship can carry
    set_max_passengers(10);

}

string
boat_long_desc()
{
    mixed * flag_desc = query_boat_in()->query_flag_desc();

    string boat_long = "A small " +d2+ " sailing ship, commonly seen sailed by " +
        "corsairs of the Bloodsea. On its side is painted a picture of " +
        LANG_ADDART(d3) + ". ";

    if(sizeof(flag_desc))
    {
        return boat_long + flag_desc[2]+ "\n";
    }

    return boat_long + "\n";
}

public void
update_boat_descriptions()
{
    mixed * flag_desc = query_boat_in()->query_flag_desc();
 
    string boat_long = "You are sitting inside a small sailing ship. " +
        "Designed by minotaur shipwrights, this craft can be piloted by a single " +
        "sailor, yet is sturdy enough to handle the high seas of the Bloodsea of " +
        "Istar. A single mast rises out of the middle of the deck, its billowing " +
        "canvas sail unfurled, ready for swift sailing. ";

    if(sizeof(flag_desc))
    {
        query_boat_in()->set_long(boat_long + flag_desc[2]+ "\n");
        query_boat_in()->add_item( flag_desc[3] , flag_desc[2] + "\n" );

        return;
    }

    query_boat_in()->set_long(boat_long + "\n");
}

void
config_boat_inside()
{
    ::config_boat_inside();

    query_boat_in()->set_short("aboard " + LANG_ADDART(d2) +" sailing ship");
    query_boat_in()->set_long("You are sitting inside a small sailing ship. " +
        "Designed by minotaur shipwrights, this craft can be piloted by a single " +
        "sailor, yet is sturdy enough to handle the high seas of the Bloodsea of " +
        "Istar. A single mast rises out of the " +
        "middle of the deck, its billowing canvas sail unfurled, ready for swift " +
        "sailing.\n");

    query_boat_in()->add_item(({"sail", "canvas sail", "billowing canvas sail", 
        "billowing sail"}), "A canvas sail, billowing with the wind.\n"); 
    query_boat_in()->add_item(({"mast", "single mast"}), 
        "A solid mast rises out of the middle of the deck, sturdy enough " +
        "to handle the strong winds common on the Bloodsea of Istar. \n");
    query_boat_in()->add_item("ship", "It is a small sailing ship, a quick " +
       "vessel around the coastlines, however not suitable for taking a " +
       "lot of passengers!\n");

}

