// file name:   /d/Avenir/common/city/entry/ez5.c
// creator(s):  Lucius
// revisions:	Lucius Oct 2008
// purpose:
// note: based on e8.c by Lilith.
// bug(s):
// to-do:
#pragma strict_types

#include "entry.h"
inherit ENTRY_ROOM;

static void
create_entry_room(void)
{
    set_short("yellow stone path, in the shadow of the Ziggurat");
    set_long("The yellow stone path runs past and curves to the south "+
	"side of the Ziggurat, granting you a glimpse of this marvelous "+
	"terraced structure overflowing with green gardens. The scent "+
	"of trees, flowers and grass is detectable drifting on the currents "+
	"this close to the Ziggurat. In the distant north stands the Gate "+
	"that welcomes visitors to the City. Directly to the south now "+
	"are the walls behind which lie the Hegemon's palace. Curving "+
	"walls to the northwest and northeast hide the enclaves for the "+
	"High Lords Inquistor and Executioner. The path here is thick "+
	"with weaving and dodging sedans coming to and from the pleasure "+
	"palace.\n");

    add_inside();
}
