/*
 * F8.c
 * Footpath off of a main trail in the Coramar forest.
 * Alaron - Feb 1998
 */

#include "coramar.h"
#include "dirheader.h"
#include "/d/Emerald/defs.h"
#include <stdproperties.h>

inherit BASEFOREST;

void
create_forest()
{
    set_long("   The narrow footpath is very confining and fills you with a sense "+
	"of being trapped or herded into a pen of some kind. There is barely room "+
	"enough for both feet on the moist, dirt path. On either side of the path, "+
	"tremendous bushes, ferns and flowers with stems as thick as tree trunks "+
	"spring up into the air. Some of the brush is so tall you can't see over it. A "+
	"cool, gentle breeze blows from west to east down the path, softly rustling "+
	"the tall green bushes and shaking the vines which hang down from tremendous "+
	"limbs above. The footpath seems to come to a slightly more maneuverable "+
	"clearing to the east.\n\n");


    add_fexit(CORAMAR+"f5", "west", 0);
    add_fexit(CORAMAR+"f49", "east", 0);
}