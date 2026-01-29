
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
    set_name(({"ship"})); 
    set_adj(({"large","slave"})); 
    set_short("large slave ship"); 
    set_long("@@boat_long_desc");

    // Sets the sailing skill level required to sail the ship
    // As it is a quest ship, making it unable to be sailed away
    set_sailing_difficulty(NO_SAIL_ANCHORED);

    // Sets the sailing skill level required to sail the ship
    set_sailing_difficulty(DIFFICULTY_PROFESSIONAL);

    // Sets the ship size as defined in std_boat_defs.h
    set_ship_size(CORVETTE);

    // Sets the maximum number of passengers the ship can carry
    set_max_passengers(20);
}

string
boat_long_desc()
{
    mixed * flag_desc = query_boat_in()->query_flag_desc();

    string boat_long = "This large imposing ship is an ogre slave vessel, shipping " +
        "its immoral cargo from Kern to the pirate isles. ";

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
 
    string boat_long = "You are standing upon the deck of a large slave ship. " +
        "Sailed by ogres, this ship is filthy, and slaves condition little better. ";

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

    query_boat_in()->set_short("aboard a large slave ship");
    query_boat_in()->set_long("You are standing upon the deck of a large slave ship. " +
         "Sailed by ogres, this ship is filthy, and slaves condition little better.\n");

    query_boat_in()->add_item(({"sails", "sail", "masts","three masts",
        "mizzen mast","main mast", "foremast"}), 
        "Three masts rise from the deck of the ship.\n"); 
    query_boat_in()->add_item(({"ship", "slave ship", "large slave ship"}), 
       "A large slave ship, sailed from Kern to the pirate isles. It is filthy, with the " +
       "waste of the slaves left on the lower and upper decks of the ship.\n");

}

