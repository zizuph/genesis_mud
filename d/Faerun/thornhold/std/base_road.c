/*
 * Base Room for Road to Thornhold
 * -- Twire/Gnim, June 2016
 */
#pragma no_clone
#pragma strict_types

#include "/d/Faerun/defs.h"
#include "../defs.h"
#include <stdproperties.h>
#include <terrain.h>

inherit FAERUN_OUTDOOR_BASE;

string extraline = "";

void
create_road()
{
}

void
create_faerun_room()
{
    setuid(); 
    seteuid(getuid());
    
    ::create_faerun_room();

    add_prop(ROOM_S_MAP_FILE, "thornhold_map.txt");
	
    create_road();

	set_extraline(extraline);
}

/*
 * Function name : add_extra_string_end
 * Description   : adds std road string
 */
void add_extra_string_end(string extra)
{
	extraline += extra + " ";
}

/*
 * Function name : add_twoway_road_string
 * Description   : adds std road string
 */
void add_twoway_road_string(string exit_left, string exit_right)
{
	add_extra_string_end("The road may be followed " + exit_left + " or " +
	             exit_right + " along a ridge.");
}

/*
 * Function name : add_road
 * Description   : adds descr of the village road
 */
void add_road()
{
    set_short("The road to Thornhold");

    extraline = "The rutted road runs along the southern perimeter of " +
		"the saltwater swamp known as the Mere of Dead Men. Jagged rocks " +
		"block passage into the swamp as the road ascends towards a sturdy " +
		"stone hold atop a cliff overlooking the Sea of Swords. ";

	add_item(({ "road", "high road", "down", "ground", "road run" }),
		"The road is rutted with deep grooves and hooves that suggest " +
		"the passage of many wagons and horses.\n");
        
	add_item(({ "rocks", "mere", "swamp", "mere", "jagged rocks" }),
		"Jagged rocks and a sharp ridge prevents passage to the swamp " +
		"known as the Mere of Dead Men. From this vantage point, you " +
		"determine it is possible to access the Mere by making your way " +
		"back down to the High Road.\n");
	
	add_item(({ "dead men" }),
		"The name 'Mere of Dead Men' referred to the thousands " +
		"of dwarves, elves, and humans of the Fallen Kingdom " +
		"who were slain here during the invasion of an orc army.\n");
        
	add_item(({ "sea", "swords" }),
		"To the west, you can see the Sea of Swords stretching off into " +
		"distance beyond the Sword Coast.\n");

	add_item(({ "thornhold", "Thornhold", "hold", "fortress", "fort" }),
		"A great, gray stone fortress sits at the highest plateau " +
		"at the edge of a cliff, blotting out part of the sky.\n");

	add_item(({ "ridge", "cliff" }),
		"This ridge leads up to seaside cliff, atop which stands " +
		"an impressive fortress.\n");

	add_item(({ "tower", "towers", "battlement"}),
		"The fortress atop the cliff is flanked by two tall towers " +
		"that rise up above a crenellated battlement.\n");

	add_item(({"up", "sky", "sun", "moon","stars","twinkle",
		"stars twinkle","night sky","night"}),TIME_DESC_ROOM + "\n");

}

void add_cliff()
{
    set_short("A narrow cliffside");
		
	add_item(({"up", "sky"}),
        TIME_DESC_ROOM + "\n");

}

/*
 * Function name : add_courtyard
 * Description   : adds descr of courtyard
 */
void add_yard()
{
    set_short("The courtyard of Thornhold");

    extraline = "The broad open area is enclosed by the buildings of the " +
        "hold. Supplies are stacked against the walls. ";

	add_item(({ "yard", "down", "ground" }),
		"The ground of the courtyard is packed dirt dotted with patches " +
		"of grass.\n");
		
	add_item(({ "supplies", "crates", "barrels", "stacks" }),
		"The supplies are packed in crates, barrels, and stacks. They are " +
		"intended for merchants who stop by Thornhold to resupply their " +
		"caravans, and are of no interest to you.\n");

    add_item(({"up", "sky"}),
        TIME_DESC_ROOM + "\n");
}

