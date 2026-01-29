/* house8a.c: Second room in the Manor. Zayn 02-16-97 */

#pragma strict_types

inherit "/std/room";
#include "defs.h"
#include "/d/Cirath/common/mobber.h"

void
reset_room()
{
    bring_room_mob("arman", TYR_NPC+"arman.c", 1, 1);
}

void
create_room()
{
	set_short("inner room in the manor");
	set_long("When you enter this room you can feel that the wealth "
		+"of the owner of this house is more than most of the "
		+"nobles in this district. The bed has a bedspread made of "
		+"the finest silk. You can also see different kinds of "
		+"portraits and this room even has wallpaper on the walls. "
		+"A shelf stands on the north wall, full of papers and books "
		+"well organized in alphabetical order. This room is also "
		+"perfectly clean from top to bottom. Everything is shiny "
		+"and well-kept.\n");

	add_item("bed", "It is covered by a bedspread made of the finest "
		+"silk. The bed by itself is luxurious and looks like it "
		+"would be really comfortable to sleep in.\n");

	add_item("bedspread", "It is made of silk, a very soft and smooth "
		+"bedspread. It is also coverd in different patterns and "
		+"all the colours you ever could imagine.\n");

	add_item(({"silk", "finest silk"}), "This silk is incredible soft "
		+"and smooth. The owner must have paid an incredible amount "
		+"of money for this material. Not to mention the cost to "
		+"transform it into a beadspread.\n");

	add_item("portraits", "They mostly appear to be of family members, "
		+"showing many generations of the family. All the frames "
		+"are made of wood and polished to reflect the sun.\n");

	add_item("wallpaper", "It was a long time since you saw wallpaper. "
		+"And this even seems to have been put up recently. It "
		+"hasn't yet been faded by the sun.\n");

	add_item("walls", "Wallpaper covers each wall, apart from the north "
		+"where a shelf takes up the whole wall.\n");

	add_item(({"shelf", "north wall"}), "A big shelf takes up the entire "
		+"north wall. It consists of loads of different books and "
		+"papers organized in alphabetical order.\n");

	add_item(({"papers", "books"}), "They are well-kept and orderly "
		+"arranged.\n");

	INSIDE

	add_exit(TYR_NOBLE+"house8.c", "east", 0, 1);
	reset_room();
}
