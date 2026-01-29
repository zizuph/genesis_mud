
/* 
    Rowing boat, varying types. 

    Coded by Maniac, 30/7/96

    Borrowed by Arman Kharas 14/4/04
 */ 
#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/goodlund/bloodsea/local.h"
#include "/d/Krynn/std/boats/std_boat_defs.h"
#include DL_CLOCK

#pragma save_binary

inherit "/d/Krynn/std/boats/example_medium_boat"; 

#include <language.h>

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
    set_adj(({ "pirate"})); 
set_adj(({"pirate",d2}));
    set_short("@@boat_short_desc"); 
    set_long("@@boat_long_desc"); 

    // Sets the sailing skill level required to sail the ship
    set_sailing_difficulty(DIFFICULTY_JOURNEYMAN);
    // Sets the ship size as defined in std_boat_defs.h
    set_ship_size(CORVETTE);
    // Sets the maximum number of passengers the ship can carry
    set_max_passengers(10);

    add_item(({"picture", "side"}), "While beautifully designed, you see nothing " +
                                   "special about the picture.\n");

}

string
boat_short_desc()
{
    return d2 +" pirate ship";
}

string
boat_long_desc()
{
    mixed * flag_desc = query_boat_in()->query_flag_desc();

    if(sizeof(flag_desc))
    {
        return "A small " +d2+ " pirate ship, commonly sailed by pirates " +
            "of the Bloodsea in lightning raids on merchant vessels and port " +
            "towns. On its side is painted a picture of " +
            LANG_ADDART(d3) + ". " +flag_desc[2]+ "\n";
    }
    return "A small " +d2+ " pirate ship, commonly sailed by pirates " +
        "of the Bloodsea in lightning raids on merchant vessels and port " +
        "towns. On its side is painted a picture of " +
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
            "sailor, yet is sturdy enough to handle the high seas of the Bloodsea of " +
            "Istar. A single mast rises out of the middle of the deck, its billowing " +
            "canvas sail unfurled, ready for swift sailing. " +flag_desc[2]+ "\n");
        query_boat_in()->add_item( flag_desc[3] , flag_desc[2] + "\n" );

        return;

    }

    query_boat_in()->set_long("You are inside a Bloodsea pirate ship. " +
        "Designed by minotaur shipwrights, this craft can be piloted by a single " +
        "sailor, yet is sturdy enough to handle the high seas of the Bloodsea of " +
        "Istar. A single mast rises out of the middle of the deck, its billowing " +
        "canvas sail unfurled, ready for swift sailing.\n");
}

void
config_boat_inside()
{
    ::config_boat_inside();

    query_boat_in()->set_short("aboard a " + d2 +" pirate ship");
    query_boat_in()->set_long("You are inside a Bloodsea pirate ship. " +
        "Designed by minotaur shipwrights, this craft can be piloted by a single " +
        "sailor, yet is sturdy enough to handle the high seas of the Bloodsea of " +
        "Istar. A single mast rises out of the middle of the deck, its billowing " +
        "canvas sail unfurled, ready for swift sailing.\n");

    query_boat_in()->add_item(({"sail", "canvas sail", "billowing canvas sail", 
        "billowing sail"}), "A canvas sail, billowing with the wind.\n"); 
    query_boat_in()->add_item(({"mast", "single mast"}), 
        "A solid mast rises out of the middle of the deck, sturdy enough " +
        "to handle the strong winds common on the Bloodsea of Istar. \n");
    query_boat_in()->add_item("ship", "It is a small sailing ship, a quick " +
       "vessel around the coastlines, however not suitable for taking a " +
       "lot of passengers!\n");

}

