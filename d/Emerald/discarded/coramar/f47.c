/*
 * F47.c
 * Path through the coramar forest.
 * Alaron - Feb 1998
 */

#include "/d/Emerald/defs.h"
#include "dirheader.h"
#include "coramar.h"
#include <stdproperties.h>

inherit BASEFOREST;

void
create_forest()
{
    set_long("   The trail through the mist-covered forest curves here. One section "+
	"of the path continues into the mirky grayness to the north, and the other "+
	"section disappears into the mist to the west. A cool breeze whistles gently "+
	"through the trees and tall plants surrounding the path from the north and "+
	"blows into a small clearing to the south. Hidden carefully near the east edge "+
	"of the trail is a small hole. It looks as though an animal might have at "+
	"one point inhabited it.\n\n");

    add_item( ({"hole", "animal hole", "small hole", "small animal hole"}),
	"The small hole has the characteristics of something that a small, "+
	"moisture-loving animal may have dug. You can hear the sound of running "+
	"water nearby, the there is a lot of moisture collected at the top of the "+
	"hole. It appears uninhabited now.\n");

    add_fexit(CORAMAR+"f46", "northeast", 0);
    add_fexit(CORAMAR+"f48", "south", 0);
    add_fexit(CORAMAR+"f53", "west", 0);
}
