
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


void
create_boat()
{
    set_name("cutter"); 
    set_adj(({"menacing", "black-sailed"})); 
    set_short("menacing black-sailed cutter"); 
    set_long("@@boat_long_desc");

    // Sets the sailing skill level required to sail the ship
    set_sailing_difficulty(DIFFICULTY_JOURNEYMAN);
    // Sets the ship size as defined in std_boat_defs.h
    set_ship_size(CORVETTE);
    // Sets the maximum number of passengers the ship can carry
    set_max_passengers(10);


}
string
boat_long_desc()
{
    mixed * flag_desc = query_boat_in()->query_flag_desc();

    if(sizeof(flag_desc))
    {
        return "This fast sailing vessel is common amongst the corsairs and pirates " +
           "of the Bloodsea. A single mast rises from the deck, and is rigged with " +
           "two black headsails.  Across the bow of this ship is written 'Drenaol's " +
           "Folly'. " +flag_desc[2]+ "\n";
    }
    return "This fast sailing vessel is common amongst the corsairs and pirates " +
       "of the Bloodsea. A single mast rises from the deck, and is rigged with " +
       "two black headsails.  Across the bow of this ship is written 'Drenaol's " +
       "Folly'.\n";
}


// When the ensign is hoisted from within the boat this function is called.
public void
update_boat_descriptions()
{
    mixed * flag_desc = query_boat_in()->query_flag_desc();

    if(sizeof(flag_desc))
    {
        query_boat_in()->set_long("You are standing upon the deck of a pirate ship! This " +
            "swift cutter has a single mast set farther aft than on most ships, however " +
            "this allows for two large headsails to be rigged, giving it an edge when " +
            "persuing other ships. " +flag_desc[2]+ "\n");
        query_boat_in()->add_item( flag_desc[3] , flag_desc[2] + "\n" );

        return;

    }

    query_boat_in()->set_long("You are standing upon the deck of a pirate ship! This " +
        "swift cutter has a single mast set farther aft than on most ships, however " +
        "this allows for two large headsails to be rigged, giving it an edge when " +
        "persuing other ships.\n");
}

void
config_boat_inside()
{
    ::config_boat_inside();

    query_boat_in()->set_short("aboard a menacing black-sailed cutter");
    query_boat_in()->set_long("You are standing upon the deck of a pirate ship! This " +
        "swift cutter has a single mast set farther aft than on most ships, however " +
        "this allows for two large headsails to be rigged, giving it an edge when " +
        "persuing other ships.\n");

    query_boat_in()->add_item(({"sails", "sail", "headsails","large headsails",
        "masts","mast","black sails","black-sails"}), 
        "A single mast rises from the deck to the aft. Two black headsails are " +
        "currently rigged, pulling like tethered dogs eager to hunt.\n"); 
    query_boat_in()->add_item(({"ship", "schooner", "cutter", "black-sailed cutter"}), 
       "This is a single-masted sailing vessel, commonly used by pirates of the Bloodsea.\n");

}

