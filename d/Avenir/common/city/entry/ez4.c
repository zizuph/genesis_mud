// file name:   /d/Avenir/common/city/entry/ez4.c
// creator(s):  Lucius
// revisions:	Lucius Oct 2008
// purpose:
// note: based on e7.c by Lilith.
// bug(s):
// to-do:
#pragma strict_types

#include "entry.h"
inherit ENTRY_ROOM;

static void
create_entry_room(void)
{
    set_short("yellow stone path, near the Ziggurat");
    set_long("The rainbow paths of the Forbidden City are thick with "+
	"sedan chairs as they flow to and from the Ziggurat, the pleasure "+
	"palace of Sybarus, which rises majestically just to the south. "+
	"The high walls of the three enclaves to the High Lords dominate "+
	"the rest of the skyline, with the First Gate but a reminder to "+
	"the north. Gorgeously planted urns line the coloured paths.\n");

    add_inside();
}
