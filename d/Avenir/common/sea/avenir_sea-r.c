// Rift of Sybarus

#pragma strict_types

#include "defs.h"

inherit SEA_SECTOR;

string
long_descr ()
{
  string descr =
        "You are sailing through a rift between steep cliffs that "+
	    "resulted when some unspeakable power broke the back of the "+
		"Dragon Mountain range. The cliff walls are dark and slick with "+
		"ice, and they speed by quickly with the force of the current "+
		"flowing through them. If you can navigate further east and "+
		"then north, you'll be near the docks of the port area of "+
        "Sybarus - the gateway to the Underdark. To your west are the " + 
        "icy waters of the Eastern Ocean.\n";
		
  return descr;
}

string
get_continents ()
{
  return
        "Here you are nearly close enough to touch the walls of the "+
        "great rift that resulted when something tore a mountain "+
        "apart and split the Dragon Mountain range of Terel in two.\n";
}

public void
create_sea_room()
{
    ::create_sea_sector("Rift of Sybarus", ROUGH_SEAS_DIFFICULTY);

    add_item(({"sybarus","port","harbour", "harbor","docks"}),
        "To your east are the docks of the port of Sybarus, with its "+
        "warehouses, inn, and great waterfall.\n");

    add_item(({"water", "sea", "ocean","eastern ocean"}), 
        "The dark waters of the Eastern Ocean are relatively calm, " +
        "once you are out of the Rift.\n");
	
	add_item(({"rift", "sybarus rift", "mountains", "walls", 
        "dragon mountains"}),
        "Here you are nearly close enough to touch the walls of the "+
        "great rift that resulted when something tore a mountain "+
        "apart and split the Dragon Mountain range in two.");
}

