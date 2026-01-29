/* File: /d/Shire/common/trollsh/trollsh12.c */
#include "defs.h"
inherit "/d/Shire/common/trollsh/shawrom"; /*master object*/

create_shawrom()
{

    set_short("South in the Troll Shaw");
    set_extraline(
	 "You find yourself northwest on a small ridge in the trollshaws. "
	+"In here the shaws seems too be very unpleasant even if the "
	+"nature itself seems rather natural.  Everywhere around you there "
	+"are small bushes and a few small spruces blocking the view. "
	+"Despite the spruces and the bushes you can see several possibilities "
	+"to get out of this place.  To the north a narrow path leads down "
	+"and up on the other side of a depression to another ridge. To the "
	+"southwest there seems to be some kind of clearing. While walking "
	+"south or east would take you to another part of this ridge. ");


add_item(({"depression","valley"}),
		 "The depression bends down between the two ridges. "
		+"It's full of bushes making it imposible to move down "
		+"there, exept for the path going through it.\n");

    SOUTHWEST("shaws7");
    NORTH("shaws13");
    SOUTH("shaws11");
    EAST("shaws14");
}
