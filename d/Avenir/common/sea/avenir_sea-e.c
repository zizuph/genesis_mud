//Eastern Sea. Connects to the Toroid seas.

#pragma strict_types

#include "defs.h"

inherit SEA_SECTOR;


string
long_descr ()
{
  string descr =
        "You are upon the Eastern Ocean, a body of water that " +
        "extends all around you. On the eastern horizon is a perilously " + 
        "steep range of mountains with blue-white glaciers. To the west the "+
        "Eastern Ocean eventually leads to the challenging Toroid High "+
        "Seas.\n";

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
    ::create_sea_sector("Eastern Ocean", TRICKY_DIFFICULTY);

    add_item(({"coastline","coast","horizon","west","land","mountains"}),
        "To your east an imposing line of mountains juts threateningly " +
        "into the sky. They are the icy Dragon Mountains of the continent "+
		"of Terel.\n");

    add_item(({"water", "sea", "ocean", "eastern ocean" }), 
        "The cold dark-gray waters of the Eastern Ocean are somewhat " +
        "choppy, which makes them too tricky for novice sailors.\n");
		
    add_item(({"ice", "chunks", "glacier", "glaciers", "floe", "floes", 
        "ice floe", "ice floes"}),
        "Glaciers flow to the edge of the Eastern Sea, rising dozens "+
        "of meters above the water's surface. Chunks of ice have broken "+
        "off of the glaciers and are floating nearby.\n");
}

