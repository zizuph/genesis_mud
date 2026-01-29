/* 
 *    Example large boat object.
 *
 *    Arman Kharas, September 2020
 */ 
#pragma save_binary

#include "/d/Krynn/common/defs.h"
#include "std_boat_defs.h"
#include <language.h>

inherit STD_BOAT_OUT; 

#define ROWER_DESC ({  "twin-sailed", "weathered", "barnacled", "trim", \
                         "well-made", "white-sailed", "battered" })

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

string d2, d3; 

void
create_boat()
{
    string *rc = ROWER_DESC;
    string *rd = ROWER_DESIGN;
  
    d2 = rc[random(sizeof(rc))];
    d3 = rd[random(sizeof(rd))];

    set_name("schooner"); 
    set_adj(({"merchant", d2 })); 
    set_short(d2 + " merchant schooner"); 
    set_long("@@boat_long_desc");

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

    if(sizeof(flag_desc))
    {
        return "A small, sharp-built vessel with two masts and fore-and-aft rig. " +
           "This ship looks like it has been used as a merchant vessel for some time, " +
           "carrying goods from port to port. On its side is painted a picture of " +
           LANG_ADDART(d3) + ". " +flag_desc[2]+ "\n";
    }
    return "A small, sharp-built vessel with two masts and fore-and-aft rig. " +
       "This ship looks like it has been used as a merchant vessel for some time, " +
       "carrying goods from port to port. On its side is painted a picture of " +
       LANG_ADDART(d3) + ".\n";
}


// When the ensign is hoisted from within the boat this function is called.
public void
update_boat_descriptions()
{
    mixed * flag_desc = query_boat_in()->query_flag_desc();

    if(sizeof(flag_desc))
    {
        query_boat_in()->set_long("You are standing upon the deck of a small, " +
            "sharp-built schooner. Two masts rise from the deck, rigged with " +
            "square sails that billow with the wind. Triangular fore-and-aft " +
            "sails have been rigged that allow this ship greater manoeuverability. " +
            flag_desc[2]+ "\n");
        query_boat_in()->add_item( flag_desc[3] , flag_desc[2] + "\n" );

        return;
    }

    query_boat_in()->set_long("You are standing upon the deck of a small, sharp-built " +
        "schooner. Two masts rise from the deck, rigged with square sails that billow " +
        "with the wind. Triangular fore-and-aft sails have been rigged that allow this " +
        "ship greater manoeuverability.\n");
}

void
config_boat_inside()
{
    ::config_boat_inside();

    query_boat_in()->set_name("schooner");
    query_boat_in()->set_short("aboard a schooner");
    query_boat_in()->set_long("You are standing upon the deck of a small, sharp-built " +
        "schooner. Two masts rise from the deck, rigged with square sails that billow " +
        "with the wind. Triangular fore-and-aft sails have been rigged that allow this " +
        "ship greater manoeuverability.\n");
    query_boat_in()->add_item(({"sails", "sail", "square sails", "rigging", 
        "fore-and-aft sails", "triangular sails","masts","mast"}), 
        "The two masts of this ship are rigged with great square sails that billow " +
        "with the wind. Triangular sails at the fore and aft of the schooner have " +
        "also been rigged to this ship, allowing for greater manoeuverability.\n"); 
    query_boat_in()->add_item(({"ship", "schooner"}), 
       "This is one of the smaller ships that can handle the brutal storms of the " +
       "high seas. It looks like it has been recently used as a merchant " +
       "vessel.\n");

}

