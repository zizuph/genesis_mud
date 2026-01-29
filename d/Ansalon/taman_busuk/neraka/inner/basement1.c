/* Elmore, 23 Dec 15 */

#include "/d/Ansalon/common/defs.h";
#include "../local.h";

inherit INNER_IN;

void
create_neraka_room()
{
    set_short("in an ancient stone basement");
    set_long("You have entered an ancient stone basement below the city of Neraka. This area must "+
	    "lie almost underneath the Temple, its ancient stone walls are covered with moisture, moss and "+
		"fungi. There is huge crack in the ceiling leading to an old house.\n");

    add_item_inside();
    add_item(({"crates","crate"}),
        "Stacks of crates line the walls. Looking further it seems as if there's a crack in the floor "+
		"leading down into the darkness.\n");
    add_item("crack","It seems to lead out of the basement back to the old house.\n");
	add_item("light","The light seems to be caused by torches, flickering in the small "+
	    "breeze thats down here.\n");
    add_item(({"moisture","moss", "fungi"}),"The water on the walls seems to come from above "+
	    " and this seems to create the ideal environment for the fungi and moss growing on the walls.\n");
	
    add_exit(NINNER + "house1", "out");
   // add_exit(NINNER + "drac_guild", "north");
}
