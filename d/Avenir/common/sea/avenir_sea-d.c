// docks area of the Sybarus Rift

#pragma strict_types

#include "defs.h"

inherit SEA_SECTOR;

string
long_descr ()
{
  string descr =
        "You are sailing through a narrow rift between mountains "+
        "whose steep, jagged walls bear mute testimony to the violence "+
	    "that shaped them. Nearby are the docks of the port area of " +
        "Sybarus - gateway to the Utterdark and the Dragon Mountains of " + 
        "Terel. To your west are the icy waters of the Eastern Ocean.\n";

  return descr;
}

string
get_continents ()
{
  return
        "Here you are nearly close enough to touch the walls of the "+
        "great rift that tore a mountain apart and split the Dragon "+
        "Range of Terel in two.";
		
}


public void
create_sea_room()
{
    ::create_sea_sector("Port of Sybarus", TRICKY_DIFFICULTY);
  
    add_item(({"sybarus","port","harbour", "harbor","docks"}),
        "To your east are the docks of the port of Sybarus, with its "+
        "warehouses, inn, and great waterfall.\n");

    add_item(({"water", "sea", "ocean","eastern ocean"}), 
        "The dark waters of the Eastern Ocean are relatively calm, " +
        "once you are out of the Rift.\n");
	
	add_item(({"rift", "sybarus rift", "mountains", "walls", 
        "dragon mountains", "dragon range"}),
        "Here you are nearly close enough to touch the walls of the "+
        "great rift that tore a mountain apart and split the Dragon "+
        "Range in two.\n");

}

