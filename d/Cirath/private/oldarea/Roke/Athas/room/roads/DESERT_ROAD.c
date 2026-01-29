inherit "/std/room";

#include "/d/Roke/common/defs.h"

public void
create_desert()	{
}

public nomask void
create_room()
{

	set_short("Desert");
	set_long(BSS("You are walking along in a large desert and the sun "+
		"is shining bright above you, making the heat unbearable "+
		"and you long for shade and water.\n"));

	create_desert();

}
