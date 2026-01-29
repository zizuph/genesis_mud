//Sea of Terel rooms, south and east of the Rift.
//Should connect to DaBaay in Terel, some day.

#pragma strict_types

#include "defs.h"

inherit SEA_SECTOR;


string
long_descr ()
{
  string descr =
        "You are upon the Terellian Sea, a body of water that " +
        "extends all around you. On the northern horizon is a " + 
        "perilously steep set of cliffs, and beyond them, a range of "+
        "mountains with blue-white glaciers. To the west the "+
        "Eastern Ocean eventually leads to the challenging Toroid High "+
        "Seas.\n";

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
    ::create_sea_sector("Terellian Seas", TRICKY_DIFFICULTY);

    set_long("You are upon the Terellian Sea, a body of water that " +
        "extends all around you. On the northern horizon is a perilously " + 
        "steep set of cliffs, and beyond them, a range of mountains "+
        "with blue-white glaciers. To the west the "+
        "Eastern Ocean eventually leads to the challenging Toroid High "+
        "Seas.\n");
		
    add_item(({"coastline","coast","horizon","west","land","mountains",
	    "cliffs"}),
        "To your north is a coastline of mostly sheer cliffs, with "+
        "a jagged mountain range beyond. This looks like a cold and "+
        "inhospitable land.\n");

    add_item(({"water", "sea" }), 
        "The cold blue waters of the Terellian Sea are somewhat " +
        "choppy, which makes them too tricky for novice sailors.\n");
		
    add_item(({"ice", "chunks", "glacier", "glaciers", "floe", "floes", 
        "ice floe", "ice floes"}),
        "Chunks of ice that broke off of the glaciers are rapidly "+
        "melting as they drift south and west, into these warmer waters.\n");
}

