/*
 * Thornhold
 * -- Twire/Gnim June 2016
 */
#pragma no_clone
#pragma strict_types

#include "/d/Faerun/defs.h"
#include "defs.h"
#include <stdproperties.h>
#include <terrain.h>

inherit BASE_ROAD;

void
create_road()
{
    set_short("The courtyard of Thornhold");

    extraline = "The broad open area is enclosed by the buildings " +
        "of the hold. Supplies are stacked against the walls. ";

	add_item(({ "yard", "down", "ground" }),
		"The ground of the courtyard is packed dirt dotted " +
		"with patches of grass.\n");
		
	add_item(({ "supplies", "crates", "barrels", "stacks" }),
		"The supplies are packed in crates, barrels, and stacks. " +
		"They are intended for merchants who stop by Thornhold " +
		"to resupply their caravans, and are of no " +
		"interest to you.\n");

    add_item(({"up", "sky"}),
        TIME_DESC_ROOM + "\n");
    
    add_item(({"gate", "main gate"}),
    	"The main gate can be seen to the south.\n");
    	
	add_item(({ "thornhold", "Thornhold", "hold", "fortress", "fort" }),
		"You stand within the southern courtyard of the great " +
		"fortress of Thornhold.\n");
    
	add_extra_string_end("The aroma of the sea combines " +
	"with the smell of horses, and hay spills into the " +
	"courtyard from a stable to the east. " +
	"To west you can enter an austere guardroom. The " +
	"courtyard continues to the north to a bustling " +
	"area where caravans resupply and trade " +
	"with the locals. To the south, you can leave Thornhold " +
	"through the main gate.");
	
    reset_faerun_room();

    add_exit(ROOM_DIR + "courtyard_north",    "north");
    add_exit(ROOM_DIR + "gate",   "south");
    add_exit(ROOM_DIR + "stables",   "east");
    add_exit(ROOM_DIR + "guardroom",   "west");
}

public void
init()
{
    ::init();
}

void
reset_faerun_room()
{
    set_searched(0);
}
