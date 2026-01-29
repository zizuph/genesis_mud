/* 
    Ergothian galleon    
 */ 
#pragma save_binary

#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/std/boats/std_boat_defs.h"
#include <language.h>

inherit STD_BOAT_OUT; 

#define BOBJ "/d/Krynn/turbidus_ocean/obj/"

object cabin_room = BOBJ + "ergothian_warship_cabin";
object mast_room = BOBJ + "ergothian_warship_mast";

string* climb_data = ({"second mast", mast_room, 
    "up the mast like a monkey"});


void
create_boat()
{
    set_name("galleon"); 
    add_name("warship");
    add_name("_turbidus_battling_ship");
    set_adj(({"ergothian"})); 
    set_short("Ergothian galleon"); 
    set_long("@@boat_long_desc");

    add_item(({"wood", "dark wood", "ship", "warship"}),
        "Looking closely you notice that the hull of the ship has " +
        "recently been patched and repaired.\n");

    // Sets the sailing skill level required to sail the ship
    set_sailing_difficulty(DIFFICULTY_PROFESSIONAL);
    // Sets the ship size as defined in std_boat_defs.h
    set_ship_size(FRIGATE);
    // Sets the maximum number of passengers the ship can carry
    set_max_passengers(30);
}

string
boat_long_desc()
{
    mixed * flag_desc = query_boat_in()->query_flag_desc();

    string boat_long = "A large square-rigged galleon rises out of the water before " +
        "you. This heavy sailing vessel has been the mainstay of the Ergothian " +
        "royal navy since before the Cataclysm. While old in design it still makes " +
        "for an imposing warship, and is often used as an armed high-value cargo " +
        "carriers. ";

    if(sizeof(flag_desc))
    {
        return boat_long + flag_desc[2]+ "\n";
    }

    return boat_long + "\n"+ 
        "The Ergothian galleon is currently grappled to the side of a " +
        "pirate frigate, and a fierce battle is going on between " +
        "the crew of both ships!\n";
}

public void
update_boat_descriptions()
{
    mixed * flag_desc = query_boat_in()->query_flag_desc();
 
    string boat_long = "You are standing upon the deck of a large square-rigged " +
        "galleon of the royal Ergothian navy. Large and heavy, this vessel is powered " +
        "by large sails rigged to three great masts, allowing it to transport cargo " +
        "and troops swiftly across the high seas. This craft is armed with a heavy " +
        "ballista, making it a dangerous ship to raise arms against. ";

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

    query_boat_in()->add_name("_turbidus_battling_ship");
    query_boat_in()->set_short("aboard an Ergothian galleon");
    query_boat_in()->set_long("You are standing upon the deck of a large square-rigged " +
        "galleon of the royal Ergothian navy. Large and heavy, this vessel is powered " +
        "by large sails rigged to three great masts, allowing it to transport cargo " +
        "and troops swiftly across the high seas. This craft is armed with a heavy " +
        "ballista, making it a dangerous ship to raise arms against.\n");

    query_boat_in()->add_item(({"sail", "sails", "billowing sails", 
       "white sails"}), "There are five sails in total. The three main sails are white " +
       "with the Imperial Shield of the Empire of Ergoth emblazoned across them.\n");

    query_boat_in()->add_item(({"mast", "masts"}),
       "Three great masts extend from the main deck, they look slightly worn, yet sturdy. \n");

    query_boat_in()->add_item("deck",
       "Made from dark wooden planks it is very clean and well-polished. Clearly the " +
       "captain takes great pride in every detail of his ship. \n");
                              
    query_boat_in()->add_item("cabin",
       "It seems to provide good shelter from the elements.\n");                                

    query_boat_in()->add_item(({"ship", "warship", "galleon"}),
       "This is the deck of a large square-rigged galleon of the royal Ergothian navy. \n");

    query_boat_in()->add_cmd_item("mast","climb","There are three masts.\n");

    query_boat_in()->add_cmd_item("first mast","climb","You try to climb the " +
                                  "mast but fail miserably.\n");

    query_boat_in()->add_exit(BOBJ + "ergothian_warship_cabin", "cabin", 0, 1);                                                                   
    cabin_room->set_exit(file_name(query_boat_in())); 
    mast_room->set_exit(file_name(query_boat_in()));
    query_boat_in()->set_climb_data(climb_data);
}
