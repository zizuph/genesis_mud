#pragma strict_types

#include "defs.h"
inherit TBASE;

public void
tunnel_room(void)
{
    set_short("dark tunnel");
    set_long("Worn smooth over the years, the floor of this "+
	"tunnel leads down to the @@get_north@@, and back up "+
	"to the @@get_south@@. "+ LDESC +"A soft, warm breeze blows "+
	"down the passage from the @@get_north@@, creating a strange, "+
	"almost musical, sound. Also from the @@get_north@@, there "+
	"emanates a soft glow.\n");

    add_item("glow", "It is indistinct.\n");
    add_item(({ "wall", "walls" }),
	"The walls are smooth and undecorated.\n");

    add_cmd_item(({"music","wind"}), ({"listen","hear"}),
	"The musical sound of the wind fills you, inexplicably, "+
	"with joy.\n");

    southern("tunnel2");
    northern("tunnel4");
}
