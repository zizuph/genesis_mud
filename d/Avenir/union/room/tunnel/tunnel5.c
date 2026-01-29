#pragma strict_types

#include "defs.h"
inherit TBASE;

public void
tunnel_room(void)
{
    set_short("warm tunnel");
    set_long("The air here is warm and dry, and is moving steadily "+
	"to the @@get_north@@ in a strong breeze. The passage "+
	"descends gently to the @@get_north@@, and rises at a "+
	"steeper angle to the @@get_south@@, from where emanates "+
	"a gentle glow." + LDESC + "\n");

    add_item("glow", "It is indistinct.\n");

    add_cmd_item(({"music","wind"}), ({"listen","hear"}),
	"The musical sound of the wind fills you, inexplicably, "+
	"with joy.\n");

    southern("tunnel4");
    northern("tunnel6");
}
