//Icy waters, filled with ice floes and icebergs.

#pragma strict_types

#include "defs.h"

inherit SEA_SECTOR;

string
long_descr ()
{
  string descr =
        "You are sailing upon rough waters thick with ice-floes "+
        "all around you. The view to the east is dominated by the "+
        "mountainous, glaciated coastline of Terel, while to the "+
        "southwest the waters of the Eastern Ocean meet those of the " +
        "Toroid High Seas.\n";

  return descr;
}

string
get_continents ()
{
  return
        "To your east an imposing line of mountains juts threateningly " +
        "into the sky. They are the icy Dragon Mountains of the continent "+
		"of Terel.\n";
		
}


public void
create_sea_room()
{
    ::create_sea_sector("ice-packed Eastern Ocean", HIGH_SEAS_DIFFICULTY);
	

    add_item(({"coastline","coast","horizon","west","land","mountains"}),
        "To your east an imposing line of mountains juts threateningly " +
        "into the sky. They are the icy Dragon Mountains of the continent "+
		"of Terel.\n");

    add_item(({"ice", "chunks", "glacier", "glaciers", "floe", "floes", 
        "ice floe", "ice floes", "sea ice", "ice pack"}),
        "Chunks of ice have broken off of the glaciers and are floating "+
        "nearby. North of here, the sea ice forms a solid sheet.\n");

    add_item(({"toroid high seas","high seas","seas", "toroid seas"}),
        "To the southwest the waters become rougher where the Eastern " +
        "Ocean meets the Toroid High Seas. " +
        "The Toroid High Seas are incredibly " +
        "difficult to navigate, but with it being one of the few " +
        "ways to reach the many continents of Genesis, it is still " +
        "travelled by highly skilled ship captains.\n");

    add_item(({"water", "ocean","eastern", "eastern ocean"}),
        "The waters of the Eastern Ocean are not as rough as " +
        "those of the Toroid High Seas, but neither can they be "+
        "considered kind to novice sailors, especially here, where "+
		"a fall into the ice-cold water could mean certain death.\n");

}

