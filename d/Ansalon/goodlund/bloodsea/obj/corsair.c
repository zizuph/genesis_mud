
/* 
    Rowing boat, varying types. 

    Coded by Maniac, 30/7/96

    Borrowed by Arman Kharas 14/4/04
 */ 
#pragma save_binary

#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/std/boats/std_boat_defs.h"
#include <language.h>

inherit STD_BOAT_OUT; 

void
create_boat()
{
    set_name(({"sloop-of-war","sloop"})); 
    set_adj(({"swift","ship-rigged"})); 
    set_short("swift ship-rigged sloop"); 
    set_long("@@boat_long_desc");

    // Sets the sailing skill level required to sail the ship
    set_sailing_difficulty(DIFFICULTY_PROFESSIONAL);
    // Sets the ship size as defined in std_boat_defs.h
    set_ship_size(FRIGATE);
    // Sets the maximum number of passengers the ship can carry
    set_max_passengers(20);
}

string
boat_long_desc()
{
    mixed * flag_desc = query_boat_in()->query_flag_desc();

    string boat_long = "This is a swift-looking sloop-of-war, commonly used by the " +
        "seafarers of Saifhum as convoy escorts, messengers, scouts, and even raiders. " +
        "Along the bow of this vessel has been engraved in silver 'Cormorant'. ";

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
 
    string boat_long = "You are standing upon the deck of a swift sloop-of-war. " +
        "Flush decked with a no forecastle, this ship has been built for speed. " +
        "Three masts rise from the deck, a mizzen, main, and foremast, allowing for " +
        "swift travel across the seas. This craft is armed with a heavy " +
        "ballista, making it a a threat to all but the boldest pirates. ";

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

    query_boat_in()->set_short("Inside a swift sloop-of-war");
    query_boat_in()->set_long("You are standing upon the deck of a swift sloop-of-war. " +
        "Flush decked with no forecastle, this ship has been built for speed. " +
        "Three masts rise from the deck, a mizzen, main, and foremast, allowing for " +
        "swift travel across the seas. This craft is armed with a heavy " +
        "ballista, making it a a threat to all but the boldest pirates.\n");

    query_boat_in()->add_item(({"sails", "sail", "masts","three masts",
        "mizzen mast","main mast", "foremast"}), 
        "Three masts rise from the deck of the ship.\n"); 
    query_boat_in()->add_item(({"ship", "sloop", "sloop-of-war"}), 
       "This ship is a sloop-of-war, common amongst the seafarers of the isle of " +
       "Saifhum.\n");
    query_boat_in()->add_item(({"ballista","heavy ballista"}),
       "This ship is armed with a heavy ballista. With it this ship " +
       "Can destroy the rigging of swift ships, or put a big hole in a sea creature.\n");
    query_boat_in()->add_cmd_item(({"ballista","heavy ballista"}),
       ({"fire", "load", "push", "pull"}), "You decide not to mess with the " +
       "ballista.\n");

}

