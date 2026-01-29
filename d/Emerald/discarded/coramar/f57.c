/*
 * F57.c
 * Forest of Coramar
 * Alaron March 1998
 */

#include "/d/Emerald/defs.h"
#include "dirheader.h"
#include "coramar.h"

inherit BASEFOREST;

void
create_forest()
{
    set_long("   You are in a narrow forest path that has the feeling of a green, "+
	"natural hallway. The sides of the path are made up of extremely tall, flowing "+
	"and smooth bushes, leaves and branches. Thick vines hang down almost to the "+
	"forest floor from unseen branches and limbs in the canopy high above the "+
	"mist. Peering around, the dense, blue-gray fog and high walls of the path "+
	"do a fairly effective job and blocking any view of the surrounding "+
	"area. The path continues to an even more narrow point northwest of here, and "+
	"widens gradually as it heads southeast.\n\n");

    add_fexit(CORAMAR+"f58", "northwest", 0);
    add_fexit(CORAMAR+"f56", "southeast", 0);
}
   