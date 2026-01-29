/*
 * F31
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
    set_long("   You are on a narrow path leading through a mist-shrouded forest. The "+
	"mist hangs low above the forest floor, bathing everything with a thick, "+
	"blue-gray blanket that hides the trees, plants and grass in shadows. Huge "+
	"plants spring forth out of the ground on either side of the path, coming "+
	"to a point high above your head. The huge trunks of trees appear as nothing "+
	"more than vague, giant black cylinders in the distance behind the fog. Thick, "+
	"twisting vines hang down onto the path from hidden branches and limbs "+
	"above. To the northwest, you can see a small iron fence surrounding a clearing. "+
	"To the southeast you can see a large, rectangular stone structure hidden "+
	"behind the blue-gray misty veil.\n\n");

    add_item( ({"fence", "small fence", "small iron fence", "iron fence"}),
	"The small, iron vence is hardly discernable from here. The thick blanket of "+
	"hovering fog creates too much of a distortion of it to get a good look.\n");

    add_item( ({"rectangle", "rectangular structure", "stone structure",
	"rectangular stone structure", "structure"}),
	"It is too far away and too hidden behind the fog to get a good look. You can "+
	"tell that it is made of a light-colored stone.\n");

    add_fexit(CORAMAR+"f30", "northwest", 0);
    add_fexit(CORAMAR+"f32", "southeast", 0);
}