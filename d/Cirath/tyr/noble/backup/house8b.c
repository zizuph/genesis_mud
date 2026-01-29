/* house8b.c: Garden in the Manor. Zayn 02-16-97 */

#pragma strict_types

inherit "/std/room";
#include "defs.h"
#include "/d/Cirath/common/mobber.h"

void
reset_room()
{
    bring_room_mob("slave", TYR_NPC+"slav_hmn.c", 2);
}

void
create_room()
{
	set_short("garden of the manor");
	set_long("It is very uncommon to have a private garden like this. "
		+"To maintain it probably costs more than a whole "
		+"family would earn in a year or maybe five years. There are "
		+"many different plants and even trees here. You can't even "
		+"imagine how much water it would require to keep them "
		+"alive. The sun is burning from above and the soil is of "
		+"remarkably high quality and rich in nourishment.\n");

	add_item("plants", "Here are plants that you never have seen before. "
		+"They all look well-kept and put in rows depending on type "
		+"and size. One could feed a whole family for many months on "
                +"these.\n");

	add_item("trees", "Some of the trees have flowers while others bear fruit. "
		+"They are as everything else well-kept and full of leaves. "
		+"Even though the sun is burning the leaves they are green "
		+"and prosperous. It must depend on the soil and the good "
		+"access to water.\n");

	add_item("soil", "Wonder where this nourishing soil comes from? It "
		+"must have been a very high price paid for it. It is not "
		+"soil from Athas, that is for sure.\n");

	OUTSIDE
	ADD_SUN_ITEM;

	add_exit(TYR_NOBLE+"house8.c", "west", "@@walk_inside", 1);
	reset_room();
}

public int
walk_inside()
{
    TP->catch_msg("How good it is to be on the inside again.\n");
    return 0;
}
