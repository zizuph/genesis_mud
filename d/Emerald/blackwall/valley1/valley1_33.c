/* Woodlands south of the Blackwall mountains.

   Code (c) 1999 to Damian Horton - BKA Casimir.
*/
 
#pragma strict_types
#pragma save_binary 

#include "/d/Emerald/sys/paths.h"

inherit BLACKWALL_VALLEY1_DIR + "base_valley.c";

void
create_valley_room()
{
    set_short("Gulley.");
    set_em_long("In a densely vegetated gulley in forest not far from "+
		"the Blackwall mountains. The ground underfoot is "+
		"soggy, muddy and inundanted in "+
		"ferns. The gulley slopes gently downward "+
		"to the north. You could leave the gulley most "+
		"easily by heading west.\n");

    remove_item("sky");
    add_item(({"sky", "up", "canopy", "forest canopy"}),
	     "Your view of it is obscured by the forest canopy.\n"); 

    add_item(({"mountains", "blackwall mountains", "canopy"}),
	     "The canopy overhead is too thick, you cannot see the "+
	     "mountains from here.\n");

    add_item("ferns",
	     "The bottom of this gulley is almost completly covered "+
	     "by ferns. They grow well in waterlogged ground such as "+
	     "this. Though some ferns are edible, and some even have "+
	     "medicinal properties, the species found here appears to "+
	     "be neither.\n");

    add_item(({"ground", "mud", "water", "waterlogged ground"}),
	     "As the lowest point in the immediate area, rain "+
	     "runoff naturally flows into the gulley. "+
	     "The ground is consequently "+
	     "wet and muddy, and generally unpleasant to traverse.\n");

    add_cmd_item(({"get", "take", "pick"}),({"fern", "ferns"}),
        "You can think of absolutly no reason whatsoever why you want "+
	"some ferns, and thus decide to leave them be.\n");

    add_cmd_item("eat", ({"fern", "ferns"}),
		 "Bluck! They certainly cannot have any nutritional "+
		 "value.\n");
    
    add_exit(BLACKWALL_VALLEY1_DIR + "valley1_34", "north", 0, 4);
    add_exit(BLACKWALL_VALLEY1_DIR + "valley1_32", "west", 0, 5);
}

/* Special smell for this room. */

public void
hook_smelled(string arg)
{
    if (strlen(arg) && !(parse_command(arg, ({}), "[the] 'forest' / " +
        "'woods' / 'plants' / 'trees' / 'bushes' / 'ferns' "))) 
    {
        return;
    }
    
    // player may "smell woods", "smell the plants" etc. and will
    // receive the same message
	
    write("The gulley smells of something in between a pleasant "+
	  "earthy smell and the stench of decay. It reeks of "+
	  "moisture and mud.\n");
}









