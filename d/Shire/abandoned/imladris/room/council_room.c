#include "defs.h"

create_rivendell_room()
{
	set_short("Council meeting room");
	
	set_long(
	"You are now in the room where the council of the healers usually have "+
	"their meetings. The room is rather small, with a large table situated in "+
	"one corner of the room. Around the table there are 3 chairs.\n");

	add_exit(IML_DIR + "fireroom", "out");
	
	add_item("chair", "Oh yes, that chair looks cosy and comfortable.\n");

	add_item("table", "It is a low table fitting like a glow to the chairs.\n");

	add_prop(ROOM_I_INSIDE, 1);
	add_prop(ROOM_I_LIGHT, 2);
}



