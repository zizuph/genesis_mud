/* 
 *    Standard fishing boat object.
 *
 *    Arman Kharas, September 2020
 */ 
#pragma save_binary

#include "/d/Krynn/common/defs.h"
#include "std_boat_defs.h"
#include <language.h>

inherit STD_BOAT_OUT; 

#define ROWER_DESC ({  "leaky", "weathered", "barnacled", "trim", \
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

string bd; 

void
create_boat()
{
    string *rc = ROWER_DESC;
    string *rd = ROWER_DESIGN;

    string d2, d3;
 
    d2 = rc[random(sizeof(rc))];
    d3 = rd[random(sizeof(rd))];

    set_name("boat"); 
    set_adj(({d2, "fishing"})); 
    set_short(d2 +" fishing boat"); 
    set_long("A small " +d2+ " fishing boat, commonly " +
        "seen chasing the schools of fish that are common along the " +
        "coastlines of Ansalon. On its side is painted a picture of " +
        LANG_ADDART(d3) + ".\n"); 

    add_item(({"picture", "side", d3}), 
        "While beautifully designed, you see nothing special about the picture.\n");

    set_max_passengers(3);
    set_sailing_difficulty(DIFFICULTY_LAYMAN);
    set_ship_size(SLOOP);
}

void
config_boat_inside()
{
    ::config_boat_inside();

    query_boat_in()->set_name("fishing boat");
    query_boat_in()->set_short("Inside a small fishing boat");
    query_boat_in()->set_long("You are sitting inside a small fishing boat. " +
        "While nothing particularly special compared to the well-crafted ships " +
        "of the minotaurs, or the elegant vessels piloted by the elves, it meets " +
        "the purposes of any local fisherman. A single mast rises out of the " +
        "middle of the deck, its billowing canvas sail unfurled, ready for swift " +
        "sailing.\n");

    query_boat_in()->add_item(({"sail", "canvas sail", "billowing canvas sail", 
        "billowing sail"}), "A canvas sail, billowing with the wind.\n"); 
    query_boat_in()->add_item(({"mast", "single mast"}), 
        "A solid mast rises out of the middle of the deck, sturdy enough " +
        "to handle the strong winds common on seas of Ansalon. \n");
    query_boat_in()->add_item(({"boat","ship"}), "It is a small fishing boat, common " +
       "around the coastlines of Ansalon.\n");

}

