/*
 * F27.c
 * One room in the 'Grave of the First'
 */

#include "/d/Emerald/defs.h"
#include "coramar.h"
#include "dirheader.h"

inherit BASEGRAVE;

void
create_graveyard()
{
    set_short("A graveyard in the forest");

    set_long("   You are standing in a clearing in the middle of the mist-shrouded "+
	"forest. The clearing has been incredibly well cared for. The grass is cut "+
	"short and neatly, and patches of weeds have been removed. The clearing is "+
	"wide and rectangular shaped, extending further to the east within the borders "+
	"of a low, black iron fence. The ground here seems more sturdy and less affected "+
	"by the constant attack of moisture on the soil. Arranged in perfectly ordered "+
	"rows throughout the rectangle of the iron fence are small marble squares. The "+
	"marble squares have writing on them. There is a small break in the iron "+
	"border fence, providing easy access to a path that leads off into the "+
	"blue-gray haze to the southwest.\n\n");
   
    add_fexit(CORAMAR+"f26", "southwest", 0);
    add_fexit(CORAMAR+"f28", "east", 0);
}
