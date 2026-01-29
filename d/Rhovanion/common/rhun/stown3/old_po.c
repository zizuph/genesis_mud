
#pragma save_binary

inherit "/d/Rhovanion/lib/room";
#include <macros.h>
#include "/sys/stdproperties.h"
#include "/d/Rhovanion/farlong.h"

create_room()
{
set_short("Abandoned Post Office");
set_long(break_string("This old, decayed wooden building was apparently"
	+" once a thriving post office.  It is now desolate and empty,"
	+" though, and no more mail passes through these hallowed halls."
	+"  The old sign still hangs overhead here, carved from a board"
	+" of some ancient, dark wood.  The only exit lies back to the"
	+" northeast, heading out onto the street."
	+"\n",75));

AE(RHUN+"stown3/crossroads","northeast",0);

add_prop(ROOM_I_LIGHT,1);IN

add_cmd_item("sign","read","The old sign has instructions on how this post office would be used, were it still in operation.\n");

add_item("sign",break_string("The old post office sign still hangs,"
	+" bearing its message to whomever might care to read it."
	+"\n",75));



}
