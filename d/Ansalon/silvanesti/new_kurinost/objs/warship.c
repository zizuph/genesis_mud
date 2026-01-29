
#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/goodlund/bloodsea/local.h"
#include DL_CLOCK

#pragma save_binary

inherit ANSALON_BOAT; 

#include <language.h>


void
create_boat()
{
    set_name("warship"); 
    set_adj(({"massive", "dragonarmy"})); 
    set_short("massive dragonarmy warship"); 
    set_long("A monster of a ship rises out of the water before you. Four masts rigged " +
       "with great canvas sails, this warship transports ground troops across the Bay " +
       "of Balifor for the Green Dragonarmy's invasion of the elven kingdom of " +
       "Silvanesti. Across its bow has been carved the name 'Verdigris'.\n");
    add_item(({"canvas sails", "sails", "four masts", "masts"}),
       "Four great masts rigged with canvas sails rise from the deck of this great vessel.\n");

    set_max_passengers(30); 
}


void
config_boat_inside()
{
    ::config_boat_inside();

    query_boat_in()->set_short("the deck of a mighty warship");
    query_boat_in()->set_long("You are standing upon the deck of a mighty warship. This " +
        "capital vessel has four great masts rising from the deck, allowing it to travel " +
        "swiftly for a craft of its size. This craft is armed with a number of heavy " +
        "ballistas, making it a dangerous threat to even the swiftest of ships.\n");

    query_boat_in()->add_item(({"sails", "sail", "great masts","four great masts",
        "masts","mast"}), 
        "Four great masts rigged with canvas sails rise from the deck of this craft.\n"); 
    query_boat_in()->add_item(({"ship", "warship", "mighty warship"}), 
       "This is the prized warship of the Green Dragonarmy.\n");
    query_boat_in()->add_item(({"ballista","ballistas","heavy ballistas"}),
       "This ship is armed with a number of heavy ballistas. With them this ship " +
       "Can destroy the rigging of swift ships, allowing for easy boarding.\n");
    query_boat_in()->add_cmd_item(({"ballista","ballistas","heavy ballistas"}),
       ({"fire", "load", "push", "pull"}), "You decide not to mess with the " +
       "ballistas.\n");

}

