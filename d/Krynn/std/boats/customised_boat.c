/* 
 *    Customisable ship object.
 *
 *    Arman Kharas, September 2020
 */ 
#pragma save_binary

#include "/d/Krynn/common/defs.h"
#include "std_boat_defs.h"
#include <language.h>

inherit STD_BOAT_OUT; 

string ship_name, * ship_adj, ship_long;
string ship_long_in, ship_naming, ship_figurehead;
int ship_passengers, ship_difficulty, ship_size;

public string
query_ship_name()
{
    if(!strlen(ship_name))
        return "boat";

    return ship_name;
}

public void
set_ship_name(string str)
{
    ship_name = str;
}

public string *
query_ship_adj()
{
    if(!sizeof(ship_adj))
        ship_adj = ({ "well-made", "fishing" });

    return ship_adj;
}

public void
set_ship_adj(string * str)
{
    ship_adj = str;
}

public string
query_ship_naming()
{
    if(!strlen(ship_naming))
        return "";

    return "Along the starboard bow her name has been " +
        "painted - '" +capitalize(ship_naming)+ "'. ";
}

public void
set_ship_naming(string str)
{
    ship_naming = str;
}

public string
query_ship_figurehead()
{
    if(!strlen(ship_figurehead))
        return "";

    return "Mounted on the prow is a figurehead of " +
        LANG_ADDART(ship_figurehead)+ ". ";
}

public void
set_ship_figurehead(string str)
{
    ship_figurehead = str;
}

public int
query_max_ship_passengers()
{
    return ship_passengers;
}

public void
set_max_ship_passengers(int x)
{
    ship_passengers = x;
}

public int
query_custom_sailing_difficulty()
{
    return ship_difficulty;
}

public void
set_custom_sailing_difficulty(int x)
{
    ship_difficulty = x;
}

public int
query_custom_ship_size()
{
    return ship_size;
}

public void
set_custom_ship_size(int x)
{
    ship_size = x;
}

public string
query_ship_long()
{
    if(!strlen(ship_long))
        return capitalize(LANG_ADDART(query_short()))+ 
            ", commonly seen sailing the seas of Ansalon. ";

    return ship_long;
}

public void
set_ship_long_in(string str)
{
    ship_long_in = str;
}

public string
query_ship_long_in()
{
    if(!strlen(ship_long_in))
        return "You stand aboard " +LANG_ADDART(query_short())+ 
            ", commonly seen sailing the seas of Ansalon. ";

    return ship_long_in;
}

public void
set_ship_long(string str)
{
    ship_long = str;
}

void
create_boat()
{  
}

void
create_the_boat()
{  
    set_name(query_ship_name()); 
    set_adj(query_ship_adj()); 

    if(sizeof(query_ship_adj()) > 1)
        set_short(ship_adj[0]+ " " +ship_adj[1]+ " " + query_ship_name()); 
    else
        set_short(ship_adj[0]+ " " + query_ship_name());

    set_long("@@boat_long_desc"); 

    set_sailing_difficulty(query_custom_sailing_difficulty());
    set_ship_size(query_custom_ship_size());
    set_max_passengers(query_max_ship_passengers());

}

string
boat_long_desc()
{
    mixed * flag_desc = query_boat_in()->query_flag_desc();

    if(sizeof(flag_desc))
    {
        return query_ship_long() + query_ship_figurehead() +
            query_ship_naming() + flag_desc[2]+ "\n";
    }
    return query_ship_long() + query_ship_figurehead() + 
        query_ship_naming() + "\n";
}


// When the ensign is hoisted from within the boat this function is called.
public void
update_boat_descriptions()
{
    mixed * flag_desc = query_boat_in()->query_flag_desc();

    if(sizeof(flag_desc))
    {
        query_boat_in()->set_long(query_ship_long_in() +flag_desc[2]+ "\n");
        query_boat_in()->add_item( flag_desc[3] , flag_desc[2] + "\n" );

        return;
    }

    query_boat_in()->set_long(query_ship_long_in());
}

void
config_boat_inside()
{
    ::config_boat_inside();

    query_boat_in()->set_name(query_ship_name());
    query_boat_in()->set_short("aboard " +LANG_ADDART(query_short()));
    query_boat_in()->set_long(query_ship_long_in());

    switch(query_custom_ship_size())
    {
        case SLOOP:
            query_boat_in()->add_item(({"sail", "canvas sail", "billowing canvas sail", 
                "billowing sail"}), "A canvas sail, billowing with the wind.\n"); 
            query_boat_in()->add_item(({"mast", "single mast"}), 
                "A solid mast rises out of the middle of the deck, sturdy enough " +
                "to handle the strong winds common on seas of Ansalon. \n");
            query_boat_in()->add_item(({"boat","ship", query_short(), query_name() }), 
                "It is " +LANG_ADDART(query_short())+
                ", common around the coastlines of Ansalon.\n");
        break;
        case CUTTER:
            query_boat_in()->add_item(({"sail", "canvas sail", "billowing canvas sail", 
                "billowing sail"}), "A canvas sail, billowing with the wind.\n"); 
            query_boat_in()->add_item(({"mast", "single mast"}), 
                "A solid mast rises out of the middle of the deck, sturdy enough " +
                "to handle the strong winds common on seas of Ansalon. \n");
            query_boat_in()->add_item(({"boat","ship", query_short(), query_name()}), 
                "It is " +LANG_ADDART(query_short())+
                ", commonly found sailing around the coastlines of Ansalon.\n");
        break;
        case SCHOONER:
            query_boat_in()->add_item(({"sails", "sail", "square sails", "rigging", 
                "fore-and-aft sails", "triangular sails","masts","mast"}), 
                "The two masts of this ship are rigged with great sails that billow " +
                "with the wind.\n"); 
            query_boat_in()->add_item(({"ship", "schooner", "brigantine", 
                query_short(), query_name()}), 
                "This is one of the smaller ships that can handle the brutal storms of the " +
                "high seas.\n");
        break;
        case CORVETTE:
            query_boat_in()->add_item(({"sails", "sail", "square sails", "rigging", 
                "fore-and-aft sails", "triangular sails","masts","mast"}), 
                "The three masts of this ship are rigged with great sails that billow " +
                "with the wind.\n"); 
            query_boat_in()->add_item(({"ship", "corvette", "patrol boat", "sloop-of-war",
                query_short(), query_name() }), 
                "This is one of the smaller warships that can handle the brutal storms of the " +
                "high seas.\n");
        break;
        case FRIGATE:
            query_boat_in()->add_item(({"sails", "sail", "square sails", "rigging", 
                "fore-and-aft sails", "triangular sails","masts","mast"}), 
                "The three masts of this ship are rigged with great sails that billow " +
                "with the wind.\n"); 
            query_boat_in()->add_item(({"ship", "corvette", "patrol boat", "sloop-of-war",
                query_short(), query_name() }), 
               "This is one of the larger warships that can handle the brutal storms of the " +
               "high seas.\n");
            if(query_name() == "galley")
                query_boat_in()->add_item(({"oars" }), 
                   "This galley is primarily propulsed by many ranks of oars, " +
                   "manned by slaves or sailors.\n");
        break;
        case MAN_OF_WAR:
            query_boat_in()->add_item(({"sails", "sail", "great masts","four great masts",
                "masts","mast"}), 
                "Four great masts rigged with white sails rise from the deck of this " +
                "craft.\n"); 
            query_boat_in()->add_item(({"ship", "warship", "mighty warship", 
                query_short(), query_name()}), 
               "This is " +LANG_ADDART(query_short())+ ", a great vessel truly " +
               "magnificent to behold.\n");
            query_boat_in()->add_item(({"ballista","ballistas","heavy ballistas"}),
               "This ship is armed with a number of heavy ballistas. With them this ship " +
               "can destroy the rigging of swift ships, allowing for easy boarding.\n");

            query_boat_in()->add_cmd_item(({"ballista","ballistas","heavy ballistas"}),
               ({"fire", "load", "push", "pull"}), 
               "You don't know how to use these nasty " +
               "weapons of war, so decide to leave them alone.\n");
        break;
    }

}

