/*
 * Shack in Hargnak
 * Varian - June 2015
 */

#include "../defs.h"
#include <stdproperties.h>
#include <macros.h>

inherit MIRKWOOD_OLDROAD_DIR + "base";
inherit MIRKWOOD_STD_DIR + "room";


void create_room()
{       
    set_short("Shack in the village of Hargnak");
    
    set_long("This tiny shack is obviously home to a family of goblins " +
    	"that live here in Hargnak. There are two beds, one larger and one smaller, " +
    	"which are lined up against the wall opposite the door. While filling " +
    	"up the rest of the shack is a circular table with five wooden chairs " +
    	"huddled around it. In a corner, half-hidden behind the table, is a " +
    	"small metal stove nestled between two tall wooden cabinets. This " +
    	"shack really is quite small, as you notice that despite having " +
    	"only minimal furnishings, the space feels quite crowded in here.\n");

    add_item_light(({"bed", "beds", "larger bed", "smaller bed"}),
    	"There are two beds here, one larger and one smaller. They are currently " +
    	"unoccupied, with heavy blankets and pillows stacked neatly atop them. " +
    	"They are not fancy, but they do look reasonably comfortable for a " +
    	"nights sleep.\n", LIGHT_ALL);
    add_item_light(({"table", "circular table"}),
    	"This circular, wooden table is reasonably large, considering the " +
    	"size of this shack. It is surrounded by five simple, wooden chairs " +
    	"which have all been tucked underneath the table. The smooth surface " +
    	"of the table has been marred by the occasional scratch or stain, " +
    	"but it is still quite sturdy.\n", LIGHT_ALL);
    add_item_light(({"chair", "wooden chair", "chairs", "wooden chairs"}),
    	"You count five wooden chairs here, all tucked neatly underneath " +
    	"the table. The chairs are not carved, but are instead simply " +
    	"fashioned for practical usage and appear to be quite sturdy.\n", LIGHT_ALL);
    add_item_light(({"stove", "metal stove"}),
    	"This is a small metal stove, from which you feel heat eminating. " +
    	"The stove appears to be used not only for cooking foor, but is also " +
    	"for heating this small shack. As the stove is currently lit, it " +
    	"would probably be a bad idea to touch it.\n", LIGHT_ALL);
    add_item_light(({"cabinets", "wooden cabinets", "tall cabinets"}),
    	"Two tall, wooden cabinets stand against a wall, sheltering a " +
    	"small metal stove which sits between them. The cabinets are " +
    	"closed and locked, but probably only contain food and the " +
    	"personal belongings of the woodsmen who live in this shack.\n", LIGHT_ALL);
    add_item_light(({"shack", "tiny shack"}),
    	"This tiny shack is obviously home to a family of woodsmen " +
    	"that live here in Weanting. There are two beds, one larger and one smaller, " +
    	"which are lined up against the wall opposite the door. While filling " +
    	"up the rest of the shack is a circular table with five wooden chairs " +
    	"huddled around it. In a corner, half-hidden behind the table, is a " +
    	"small metal stove nestled between two tall wooden cabinets. This " +
    	"shack really is quite small, as you notice that despite having " +
    	"only minimal furnishings, the space feels quite crowded in here.\n", LIGHT_ALL);

    add_exit("hargnak2", "out", "@@harg@@");

    add_prop(ROOM_I_INSIDE,1);
}
int
harg()
{
write("You step through the door and back out into the village of Hargnak.\n");
return 0;
}
