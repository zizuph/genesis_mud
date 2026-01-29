/* 
    Rowing boat, varying types. 

    Coded by Maniac, 30/7/96

    Borrowed by Arman Kharas 14/4/04
    
    Borrowed and modified into a Minotaur warship by Cherek 12/3/07
    
 */ 
#pragma save_binary

#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/std/boats/std_boat_defs.h"
#include <language.h>

inherit STD_BOAT_OUT; 

#define BOBJ "/d/Ansalon/goodlund/bloodsea/obj/"

object cabin_room = BOBJ + "mino_warship_cabin";
object down_room = BOBJ + "mino_warship_down";
object mast_room = BOBJ + "mino_warship_mast";

string* climb_data = ({"second mast", BOBJ+"mino_warship_mast", "up the mast like a monkey"});


void
create_boat()
{
    set_name("warship"); 
    set_adj(({"swift", "minotaur"})); 
    set_short("swift minotaur warship"); 
    set_long("@@boat_long_desc");

    add_item(({"wood", "dark wood", "ship", "warship"}),
        "Looking closely you notice that the hull of the ship has " +
        "recently been patched and repaired.\n");
               
    add_item(({"red shield", "shield", "sails", "main sails"}),
        "The red shield is the mark of the Orilg tribe minotaurs " +
        "from Kothas.\n");

    // Sets the sailing skill level required to sail the ship
    // As it is a quest ship, making it unable to be sailed away
    set_sailing_difficulty(NO_SAIL_ANCHORED);

    // Sets the ship size as defined in std_boat_defs.h
    set_ship_size(FRIGATE);
    // Sets the maximum number of passengers the ship can carry
    set_max_passengers(30);
}

string
boat_long_desc()
{
    mixed * flag_desc = query_boat_in()->query_flag_desc();

    string boat_long = "A warship made of dark wood rises out of the water before " +
        "you. The flawless minotaur design makes it a very beautiful ship. It is " +
        "not the largest ship on the Bloodsea but it makes up for that with its " +
        "superior speed an maneuverability. A red shield has been painted on the " +
        "main sails. ";

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

    query_boat_in()->set_short("aboard a swift minotaur warship");
    query_boat_in()->set_long("You stand on the main deck of a minotaur " +
                              "warship. The worn dark wood has been " +
                              "patched and replaced on several places, " +
                              "evidence of a ship that has seen battle on " +
                              "more than one occasion. Two long masts rise " +
                              "from the deck and the billowing white sails " +
                              "have been decorated with a painted " +
                              "red shield. To the aft the lies the " +
                              "entrance to a cabin and a hatch leads " +
                              "down below the deck. \n");

    query_boat_in()->add_item(({"sail", "sails", "billowing sails", 
                                "white sails"}),
                                "There are five sails in total. The two " +
                                "main sails have a red shield painted on " +
                                "them. The sign of the Orilg tribe " +
                                "minotaurs of Kothas. \n");

    query_boat_in()->add_item(({"shield", "red shield"}),
                                "The sign of the Orilg tribe minotaurs has " +
                                "been painted on two of the sails. \n");

    query_boat_in()->add_item(({"mast", "masts"}),
                                "Two long masts extend from the main deck, " +
                                "they look slightly worn, yet sturdy. \n");

    query_boat_in()->add_item("deck",
                              "Made from dark wooden planks it is very " +
                              "clean and well-polished. Clearly the " +
                              "captain takes great pride in every detail " +
                              "of his ship. \n");
                              
    query_boat_in()->add_item("cabin",
                              "It seems to provide good shelter from the " +
                              "elements.\n");                                
                              
    query_boat_in()->add_item("hatch",
                              "It looks dark and damp below deck. \n");                              

    query_boat_in()->add_item("wood",
                              "Almost every part of the wooden structure " +
                              "that makes up this ship has been reinforced, " +
                              "patched or replaced. \n");

    query_boat_in()->add_item(({"ship", "warship"}),
                                "A fairly small warship somewhat resembling " +
                                "a Sloop-of-war. It is about 150 feet in " +
                                "length and 30 feet wide with two main " + 
                                "masts and square-rigged sails. The " +
                                "excellent minotaur craftmanship makes " +
                                "the ship look very sturdy yet extremely " +
                                "swift and maneuverable. \n");

    query_boat_in()->add_cmd_item("mast","climb","There are two masts.\n");

    query_boat_in()->add_cmd_item("first mast","climb","You try to climb the " +
                                  "mast but fail miserably. \n");

    query_boat_in()->add_exit(BOBJ + "mino_warship_cabin", "cabin", 0, 1);                                 
    query_boat_in()->add_exit(BOBJ + "mino_warship_down", "down", 0, 1);  
                                  
    cabin_room->set_exit(file_name(query_boat_in())); 
    down_room->set_exit(file_name(query_boat_in()));
    mast_room->set_exit(file_name(query_boat_in()));
    query_boat_in()->set_climb_data(climb_data);
}
