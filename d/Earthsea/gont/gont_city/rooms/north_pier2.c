/*
* North pier.
*
* coded by Porta 971121.
*/

#pragma strict_types
#pragma no_clone

#include <stdproperties.h>
#include <macros.h>
#include "/d/Genesis/gsl_ships/ships.h"

//inherit "/d/Earthsea/std/room";
inherit STDPIER;

public void
create_room()
{
    add_prop(ROOM_S_MAP_FILE, "earthsea_map.txt");
    set_short("North Pier of Gont");
    set_long("You are standing on one of the"+
        " northern piers of the city, which extends out into"+
        " the bay of Gont Port, and"+
        " everywhere around you can see different kinds of"+
        " ships anchored. This is a very busy harbour with"+
        " a forest of masts swaying back and forth in the"+
        " breeze coming in from the sea. At this pier"+
        " there are mostly traders, but also a few"+
        " passenger ships with destinations to far-away lands."+
        " You hear the sound of hawsers creaking against"+
        " woodwork when the ships rock in the small waves."+
        " A salty smell of sea and fish is in the air.\n");
    add_item("pier", "The pier is built from sturdy timber"+
        " logs, stretching far out in the bay. There are"+
        " many ships anchored along the side, coming from"+
        " different places of the Archipelago.\n");
    add_item("ships","A great number of ships are anchored"+
        " in Gont Port with masts swaying back and forth in"+
        " the small waves coming in. You see galleys, sloops,"+
        " caravels and many other types.\n");
    add_item("masts","The masts are swaying back and forth"+
        " in the breeze.\n");
    add_item("harbour","This is the Port of Gont, a busy"+
        " trading harbour with many ships visiting every"+
        " year.\n");
    add_item("waves","The waves are very small here, finding"+
        " their way through the narrow canal between the Armed"+
        " Cliffs.\n");
    add_item("cliffs","Almost straight south are the Armed"+
        " Cliffs, and between them the canal leading into the"+
        " secluded bay.\n");
    add_exit("north_pier1", "north");
    add_exit("north_pier3",  "south");
    add_pier_entry(MASTER_OB(TO), "Gont", "Ship to Sparkle");
    initialize_pier();
}

