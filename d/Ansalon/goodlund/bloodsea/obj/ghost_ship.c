
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
    set_name("ship"); 
    set_adj(({"ghostly","pirate"})); 
    set_short("ghostly pirate ship"); 
    set_long("@@boat_long_desc");

    // Sets the sailing skill level required to sail the ship
    set_sailing_difficulty(DIFFICULTY_GURU);
    // Sets the ship size as defined in std_boat_defs.h
    set_ship_size(MAN_OF_WAR);
    // Sets the maximum number of passengers the ship can carry
    set_max_passengers(40);
}


string
boat_long_desc()
{
    mixed * flag_desc = query_boat_in()->query_flag_desc();

    string boat_long = "Gazing upon this vessel from the Abyss makes you tremble with " +
       "fear! This is a ghostly pirate ship, whose crew were so villanous that " +
       "they continue to ply the seven seas even after death! ";

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
 
    string boat_long = "You are standing upon the deck of a cursed " +
       "ghost ship, once sailed by the infamous dwarven pirate Captain Kharasa! " +
       "Trying to examine details of the ship dazes you, as they shift like " +
       "tortured souls... ";

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

    query_boat_in()->set_short("Inside a ghostly pirate ship");
    query_boat_in()->set_long("You are standing upon the deck of a cursed " +
       "ghost ship, once sailed by the infamous dwarven pirate Captain Kharasa! " +
       "Trying to examine details of the ship dazes you, as they shift like " +
       "tortured souls...\n");

    query_boat_in()->add_item(({"details","deck","tortured souls","souls"}), 
        "You feel dizzy as you look around you... the details of this ship remind " +
        "you of tortured souls writhing in eternal suffering!\n");
}

