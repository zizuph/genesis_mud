
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
    set_name("warship"); 
    set_adj(({"massive", "dragonarmy"})); 
    set_short("massive dragonarmy warship"); 
    set_long("@@boat_long_desc");
    add_item(({"black sails", "sails", "four masts", "masts"}),
       "Four great masts rigged with black sails rise from the deck of this great vessel.\n");

    // Sets the sailing skill level required to sail the ship
    set_sailing_difficulty(DIFFICULTY_MASTER);
    // Sets the ship size as defined in std_boat_defs.h
    set_ship_size(MAN_OF_WAR);
    // Sets the maximum number of passengers the ship can carry
    set_max_passengers(30);
}

string
boat_long_desc()
{
    mixed * flag_desc = query_boat_in()->query_flag_desc();

    string boat_long = "A monster of a ship rises out of the water before you. " +
        "Four masts rigged with great black sails, this warship is the pride of " +
        "the Black Dragonarmy. Unrivaled on the Bloodsea of Istar, this vessel " +
        "is truly the master of these regions. Across its " +
        "bow has been carved the name 'Sea Queens Fury'. ";

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
 
    string boat_long = "You are standing upon the deck of a mighty warship. This " +
        "capital vessel has four great masts rising from the deck, allowing it to travel " +
        "swiftly for a craft of its size. This craft is armed with a number of heavy " +
        "ballistas, making it a dangerous threat to even the swiftest of ships. ";

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

    query_boat_in()->set_short("the deck of a mighty warship");
    query_boat_in()->set_long("You are standing upon the deck of a mighty warship. This " +
        "capital vessel has four great masts rising from the deck, allowing it to travel " +
        "swiftly for a craft of its size. This craft is armed with a number of heavy " +
        "ballistas, making it a dangerous threat to even the swiftest of ships.\n");

    query_boat_in()->add_item(({"sails", "sail", "great masts","four great masts",
        "masts","mast"}), 
        "Four great masts rigged with black sails rise from the deck of this craft.\n"); 
    query_boat_in()->add_item(({"ship", "warship", "mighty warship"}), 
       "This is the prized warship of the Black Dragonarmy.\n");
    query_boat_in()->add_item(({"ballista","ballistas","heavy ballistas"}),
       "This ship is armed with a number of heavy ballistas. With them this ship " +
       "Can destroy the rigging of swift ships, allowing for easy boarding.\n");
    query_boat_in()->add_cmd_item(({"ballista","ballistas","heavy ballistas"}),
       ({"fire", "load", "push", "pull"}), "You decide not to mess with the " +
       "ballistas.\n");

}

