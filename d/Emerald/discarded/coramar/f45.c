/*
 * F45.c
 * curve along the edge of a brook - coramar forest.
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
    set_long("   The trail curves around from northwest to east here. A cool "+
	"breeze blows low across the forest floor, stirring up leaves and rustling "+
	"the long, snake-like vines. As the wind drifts in between the huge tree trunks, "+
	"it makes an ominous howling noise. You can hear the sounds of a small brook "+
	"trickling down across rocks and dirt just beyond the trees and bushes to the "+
	"southwest. You look but can't seem to find a way to get through the brush.\n\n");


    add_fexit(CORAMAR+"f56", "northwest", 0);
    add_fexit(CORAMAR+"f43", "east", 0);
}