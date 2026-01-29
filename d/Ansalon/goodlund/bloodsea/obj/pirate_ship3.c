
/* 
    Pirate ship. 

    Coded by Arman, June 2021
 */ 

#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/goodlund/bloodsea/local.h"
#include "/d/Krynn/std/boats/std_boat_defs.h"
#include DL_CLOCK

#pragma save_binary

inherit "/d/Krynn/std/boats/example_large_boat"; 

#include <language.h>

#define ROWER_DESC ({  "imposing", "massive", "menacing", "broad-decked", \
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

string bd, d2, d3, d4 = ""; 

public void
set_ship_desc(string str)
{
    d2 = str;
    add_adj(d2);
}

public void
set_ship_design(string str)
{
    d3 = str;
}

public void
set_ship_figurehead(string str)
{
    d4 = "At the bow of the ship is the " +
       "figurehead of ";
    d4 += str + ". ";
}

void
create_boat()
{
    string *rc = ROWER_DESC;
    string *rd = ROWER_DESIGN;
 
    if(!strlen(d2)) 
        d2 = rc[random(sizeof(rc))];
    if(!strlen(d3))
        d3 = rd[random(sizeof(rd))];

    set_name("ship");
    add_name("frigate");
set_adj(({"pirate",d2}));
    set_short("@@boat_short_desc"); 
    set_long("@@boat_long_desc"); 

    add_item(({"huge black sails", "sails", "four masts", "masts","black sails"}),
        "Four great masts rigged with huge black sails rise from the deck of " +
        "this great vessel.\n");

    // Sets the sailing skill level required to sail the ship
    set_sailing_difficulty(DIFFICULTY_MASTER);

    // Sets the ship size as defined in std_boat_defs.h
    set_ship_size(FRIGATE);

    // Sets the maximum number of passengers the ship can carry
    set_max_passengers(25);

    add_item(({"picture", "side"}), "While beautifully designed, you see nothing " +
                                   "special about the picture.\n");
    add_item(({"figurehead","bow"}),
        "@@figurehead_desc");

}

string
boat_short_desc()
{
    return d2 +" pirate frigate";
}

string
boat_long_desc()
{
    mixed * flag_desc = query_boat_in()->query_flag_desc();

    if(sizeof(flag_desc))
    {
        return capitalize(LANG_ADDART(d2))+ " pirate frigate. Typically " +
            "a flagship for the pirate lords of the Bloodsea, it is a " +
            "fearsome ship and a terror to all merchant vessels that " +
            "sail the high seas. " +d4+ "On its side is painted a picture of " +
            LANG_ADDART(d3) + ". " +flag_desc[2]+ "\n";
    }
    return capitalize(LANG_ADDART(d2))+ " pirate frigate. Typically " +
            "a flagship for the pirate lords of the Bloodsea, it is a " +
            "fearsome ship and a terror to all merchant vessels that " +
            "sail the high seas. " +d4+ "On its side is painted a picture of " +
        LANG_ADDART(d3) + ".\n";
}

string
figurehead_desc()
{
    if(!strlen(d4))
        return "This ship does not seem to have a figurehead.\n";
    else
        return d4;
}


// When the ensign is hoisted from within the boat this function is called.
public void
update_boat_descriptions()
{
    mixed * flag_desc = query_boat_in()->query_flag_desc();

    if(sizeof(flag_desc))
    {
        query_boat_in()->set_long("You are aboard " +LANG_ADDART(d2)+ " pirate frigate. " +
            "Designed by minotaur shipwrights for the pirate lords of the Bloodsea, " +
            "this craft is the flagship of fearsome raids and one of the greatest " +
            "terrors of the water ways. Four masts rigged with huge black sails " +
            "rise high from the main deck, and you cannot help but marvel at this " +
            "warship as it truly is formidable to behold. " +flag_desc[2]+ "\n");
        query_boat_in()->add_item( flag_desc[3] , flag_desc[2] + "\n" );
        return;

    }

    query_boat_in()->set_long("You are aboard " +LANG_ADDART(d2)+ " pirate frigate. " +
            "Designed by minotaur shipwrights for the pirate lords of the Bloodsea, " +
            "this craft is the flagship of fearsome raids and one of the greatest " +
            "terrors of the water ways. Four masts rigged with huge black sails " +
            "rise high from the main deck, and you cannot help but marvel at this " +
            "warship as it truly is formidable to behold.\n");

}

void
config_boat_inside()
{
    ::config_boat_inside();

    query_boat_in()->set_short("aboard a " + d2 +" pirate frigate");
    query_boat_in()->set_long("You are aboard " +LANG_ADDART(d2)+ " pirate frigate. " +
            "Designed by minotaur shipwrights for the pirate lords of the Bloodsea, " +
            "this craft is the flagship of fearsome raids and one of the greatest " +
            "terrors of the water ways. Four masts rigged with huge black sails " +
            "rise high from the main deck, and you cannot help but marvel at this " +
            "warship as it truly is formidable to behold.\n");

    query_boat_in()->add_item(({"huge black sails", "sails", "four masts", 
        "masts","black sails"}),
        "Four great masts rigged with huge black sails rise from the deck of " +
        "this great vessel.\n");
    query_boat_in()->add_item(({ "frigate", "ship", "deck" }), boat_long_desc());

}

