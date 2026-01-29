// Western coastline near Sybarus Rift. 

#pragma strict_types

#include "defs.h"

inherit SEA_SECTOR;

string
long_descr ()
{
  string descr =
        "Steep mountains rise up out of the water, their flanks "+
        "covered in blue glaciers topped with snow. Chunks of ice float "+
		"on the surface of the water, a hazard to even the largest ships. "+
        "To the north, water flows into a jagged rift where the "+
        "mountains have been torn asunder by some unimaginable force. "+
        "A skilled sailor should be able to navigate through the Rift "+
        "and dock at the Port of Sybarus.\n";

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
    ::create_sea_sector("icy coastal waters", NORMAL_DIFFICULTY);

    add_item(({"ice", "chunks", "glacier", "glaciers", "floe", "floes", 
        "ice floe", "ice floes"}),
        "Chunks of ice have broken off of the glaciers and are floating "+
        "nearby.\n");

    add_item(({"horizon","west","land","mountains"}),
        "To your east an imposing line of mountains juts threateningly " +
        "into the sky. They are the icy Dragon Mountains of the continent "+
		"of Terel.\n");
		
    add_item(({"coastline","coast", "cliffs"}),
        "To your east is an icy coastline of mostly sheer glacial cliffs. "+
        "This looks like a cold and inhospitable land.\n");

    add_item(({"rift", "mountains"}),
        "The mountains here look like they have been torn apart like a piece "+
        "of bread! Into the rift where the world was ripped asunder, the "+
        "Eastern Ocean flows, creating a harbor of sorts.\n");
	
    add_item(({"sybarus","port", "harbor"}),
        "It lies in the the rift between the mountains.\n");

    add_item(({"water", "sea", "ocean"}), 
        "The dark-gray waters of the Eastern Ocean are relatively calm " +
        "and considered kind to sailors, so long as you "+
        "are careful not to sail into ice floes.\n");

}

