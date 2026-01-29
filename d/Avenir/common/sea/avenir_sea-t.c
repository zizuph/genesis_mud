// Southern Coastline Of the Terel Continent

#pragma strict_types

#include "defs.h"

inherit SEA_SECTOR;


string
long_descr ()
{
  string descr =
        "Cliffs rise from the churning sea off the southern coast "+
	    "of Terel. These waters are free of the ice floes that infest "+
	    "the western coastline, where the glacier-dominated Dragon "+
        "Mountains can be seen in the distance. Farther east you "+ 
		"can see that the land drops down toward the sea, and that "+
        "the ice and snow transition to the greens of forests and "+
		"fields.\n";

  return descr;
}

string
get_continents ()
{
  return
        "To your north is a coastline of mostly sheer cliffs, with "+
        "a jagged mountain range beyond. Terel looks like a cold and "+
        "inhospitable land.\n";		
}


public void
create_sea_room()
{
    ::create_sea_sector("Terellian coastal waters", NORMAL_DIFFICULTY);

    set_short("near the coastline of southern Terel");
    set_long("Cliffs rise from the churning sea off the southern coast "+
	    "of Terel. These waters are free of the ice floes that infest "+
	    "the western coastline, where the glacier-dominated Dragon "+
        "Mountains can be seen in the distance. Farther east you "+ 
		"can see that the land drops down toward the sea, and that "+
        "the ice and snow transition to the greens of forests and "+
		"fields.\n");

    add_item(({"ice", "chunks", "glacier", "glaciers", "floe", "floes", 
        "ice floe", "ice floes"}),
        "Chunks of ice that broke off of the glaciers are rapidly "+
        "melting as they drift south and west, into warmer waters.\n");

    add_item(({"horizon","west","land","mountains"}),
        "To your north and west an imposing line of mountains juts " +
        "into the sky. They are the icy Dragon Mountains of the continent "+
		"of Terel.\n");
		
    add_item(({"coastline","coast", "cliffs"}),
        "To your north is a coastline of mostly sheer cliffs. "+
        "This looks like a cold and inhospitable land.\n");

    add_item(({"water", "sea", "ocean"}), 
        "The dark-gray waters of the Sea of Terel are relatively calm " +
        "and considered kind to sailors, so long as you "+
        "are careful not to sail too close to the cliffs.\n");

}

