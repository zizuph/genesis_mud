// Connection rooms to the Toroid Seas

#pragma strict_types

#include "defs.h"

inherit SEA_SECTOR;


string
long_descr ()
{
  string descr =
        "You are upon the Eastern Ocean, which stretches " +
        "out all around you. To your east you can make out " +
        "a jagged, mountainous coastline on the far horizon, while "+
        "to your west the waters become more difficult as the "+
        "Eastern Ocean meets the Toroid High Seas.\n";
  return descr;
}

string
get_continents ()
{
  return
        "The continent of Terel is far east of here, a jagged line "+
        "on the horizon.\n";		
}


public void
create_sea_room()
{
    ::create_sea_sector("Far Eastern Ocean", ROUGH_SEAS_DIFFICULTY);

    add_item(({"coastline","coast","horizon","east","land"}),
        "To your East you can just make out a jagged line of " +
        "land on the horizon.\n");

    add_item(({"toroid high seas","high seas","seas", "toroid seas", "west"}),
        "To your west the waters become rougher where the Eastern " +
        "Ocean meets the Toroid High Seas. " +
        "The Toroid High Seas are incredibly " +
        "difficult to navigate, but with it being one of the few " +
        "ways to reach the many continents of Genesis, it is still " +
        "travelled by highly skilled ship captains.\n");

    add_item(({"water", "ocean","eastern", "eastern ocean" }), 
        "The waters of the Eastern Ocean are not as rough as " +
        "those of the Toroid High Seas, but neither can they be "+
        "considered kind to novice sailors.\n");

    add_row_exit(SPARKLE_LINK, "west", 0, 1);
}

