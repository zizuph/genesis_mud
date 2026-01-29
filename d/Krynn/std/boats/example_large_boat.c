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

#define ROWER_DESC ({  "massive", "huge", "imposing", "magnificent", \
                       "powerful", "broad-decked", "grand", "imperial", \
                         "commanding", "majestic", "towering" })

string d2; 

void
create_boat()
{
    string *rc = ROWER_DESC;
 
    d2 = rc[random(sizeof(rc))];

    set_name("warship"); 
    set_adj(({d2, "sailing"})); 
    set_short(d2 +" warship"); 

    set_long("@@boat_long_desc");  
    add_item(({"huge white sails", "sails", "four masts", "masts","white sails"}),
        "Four great masts rigged with huge white sails rise from the deck of " +
        "this great vessel.\n");
    add_item(({"ballistas","ballista"}),
        "A number of ballistas line both sides of the deck, " +
        "making it a nasty enemy to other ships at close range.\n");

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

    if(sizeof(flag_desc))
    {
        return "A monster of a ship rises out of the water before you. Four " +
            "masts rigged with huge white sails rise high from the main deck, " +
            "and you cannot help but marvel at this warship as it truly is " +
            "magnificent to behold. Without a doubt this massive vessel " +
            "would be the pride of any fleet, the flagship of admirals. Armed with " +
            "a number of ballistas on both sides of the deck, this warship would be " +
            "approached with caution at best. " +flag_desc[2]+ "\n";
    }
    return "A monster of a ship rises out of the water before you. Four " +
        "masts rigged with huge white sails rise high from the main deck, " +
        "and you cannot help but marvel at this warship as it truly is " +
        "magnificent to behold. Without a doubt this massive vessel " +
        "would be the pride of any fleet, the flagship of admirals. Armed with " +
        "a number of ballistas on both sides of the deck, this warship would be " +
        "approached with caution at best.\n";
}

public void
update_boat_descriptions()
{
    mixed * flag_desc = query_boat_in()->query_flag_desc();

    if(sizeof(flag_desc))
    {
        query_boat_in()->set_long("You are standing upon the deck of a mighty " +
            "warship. This capital vessel has four great masts rising from the " +
            "deck, allowing it to travel swiftly for a craft of its size. " +
            flag_desc[2]+ " This craft is armed with a number of heavy ballistas, " +
            "making it a dangerous threat to even the swiftest of ships.\n");
        query_boat_in()->add_item( flag_desc[3] , flag_desc[2] + "\n" );

        return;

    }

    query_boat_in()->set_long("You are standing upon the deck of a mighty " +
        "warship. This capital vessel has four great masts rising from the " +
        "deck, allowing it to travel swiftly for a craft of its size. This " +
        "craft is armed with a number of heavy ballistas, making it a " +
        "dangerous threat to even the swiftest of ships.\n");
}

void
config_boat_inside()
{
    ::config_boat_inside();

    query_boat_in()->set_name("warship");
    query_boat_in()->set_short("The deck of " +LANG_ART(d2)+ " warship");
    query_boat_in()->set_long("You are standing upon the deck of a mighty " +
        "warship. This capital vessel has four great masts rising from the " +
        "deck, allowing it to travel swiftly for a craft of its size. This " +
        "craft is armed with a number of heavy ballistas, making it a " +
        "dangerous threat to even the swiftest of ships.\n");

    query_boat_in()->add_item(({"sails", "sail", "great masts","four great masts",
        "masts","mast"}), 
        "Four great masts rigged with black sails rise from the deck of this " +
        "craft.\n"); 
    query_boat_in()->add_item(({"ship", "warship", "mighty warship"}), 
       "This is " +LANG_ART(d2)+ " warship, a great vessel truly magnificent " +
       "to behold.\n");
    query_boat_in()->add_item(({"ballista","ballistas","heavy ballistas"}),
       "This ship is armed with a number of heavy ballistas. With them this ship " +
       "can destroy the rigging of swift ships, allowing for easy boarding.\n");

    query_boat_in()->add_cmd_item(({"ballista","ballistas","heavy ballistas"}),
       ({"fire", "load", "push", "pull"}), 
       "You don't know how to use these nasty " +
       "weapons of war, so decide to leave them alone.\n");

}

