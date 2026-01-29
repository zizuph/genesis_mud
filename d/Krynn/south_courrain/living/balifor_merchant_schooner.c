/* 
    Merchant ship that sails Port Balifor and Courrain Ocean.

    Saved in /d/Krynn/south_courrain/living/ so it can be
    spawned through the /d/Krynn/south_courrain/courrain_placer.c

    Arman, February 2021.
 */ 

#pragma save_binary

#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/std/boats/std_boat_defs.h"
#include <language.h>
#include "../local.h"

inherit STD_BOAT_OUT; 

#define MERCHANT LIVING + "merchant"
#define SAILOR   "/d/Ansalon/goodlund/bloodsea/living/sailor"

void
create_boat()
{
    set_name("schooner"); 
    set_adj(({"merchant", "twin-sailed"})); 
    set_short("twin-sailed merchant schooner"); 
    set_long("@@boat_long_desc");

    // Sets the sailing skill level required to sail the ship
    set_sailing_difficulty(DIFFICULTY_JOURNEYMAN);
    // Sets the ship size as defined in std_boat_defs.h
    set_ship_size(SCHOONER);
    // Sets the maximum number of passengers the ship can carry
    set_max_passengers(10); 

    set_alarm(0.1, 0.0, &config_boat_inside());
}

string
boat_long_desc()
{
    mixed * flag_desc = query_boat_in()->query_flag_desc();

    string boat_long = "A small, sharp-built vessel with two masts and fore-and-aft rig. " +
        "This ship looks like it has been used as a merchant vessel for some time, " +
        "carrying goods from port to port along the Bloodsea. ";

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
 
    string boat_long = "You are standing upon the deck of a small, sharp-built " +
        "schooner. Two masts rise from the deck, rigged with square sails that billow " +
        "with the wind. Triangular fore-and-aft sails have been rigged that allow this " +
        "ship greater manoeuverability. ";

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

    object merchant = clone_object(MERCHANT);
    object s1 = clone_object(SAILOR);
    object s2 = clone_object(SAILOR);
    object s3 = clone_object(SAILOR);

    s1->move_living("into his ship", query_boat_in());
    s1->arm_me();
    s2->move_living("into his ship", query_boat_in());
    s2->arm_me();
    s3->move_living("into his ship", query_boat_in());
    s3->arm_me();
    merchant->move_living("into his ship", query_boat_in());
    query_boat_in()->set_owner(merchant);

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
       "Bloodsea of Istar. It looks like it has been recently used as a merchant " +
       "vessel.\n");

}

