/*
 * F39.c
 * Forest of Coramar
 * Alaron March 1998
 */

#include "/d/Emerald/defs.h"
#include "coramar.h"
#include "dirheader.h"

inherit BASEFOREST;

void
create_forest()
{
    set_long("   You are standing between two high walls of ferns, bushes and "+
	"tangled vines. Thick, twisted vines hang down from the unseen branches in "+
	"the forest canopy high above. A cool, wet breeze blows across the trail, "+
	"rustling the leaves and bushes and making the vines sway back and forth. The "+
	"soft, dark soil of the forest floor is well-packed and hardly covered with "+
	"many fallen leaves. This indicates a well-travelled section of the trail. The "+
	"path continues into the blue-gray mist northeast and southwest.\n\n");


    add_fexit(CORAMAR+"f38", "northeast", 0);
    add_fexit(CORAMAR+"f40", "southwest", 0);
}