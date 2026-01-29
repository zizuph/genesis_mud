// file name:  /d/Avenir/common/city/entry/ez1.c
// creator(s): Lucius
// revisions:	Lucius Oct 2008
// purpose:
// note: based on e4.c by Lilith
// bug(s):
// to-do:
#pragma strict_types

#include "entry.h"
inherit ENTRY_ROOM;

static void
create_entry_room(void)
{
    set_short("yellow stone path, just inside the Forbidden City");
    set_long("Few visitors to the Forbidden City are given leave "+
        "to walk around freely and most of its inhabitants eschew "+
        "the practice, so the number of sedan chairs is "+
	"markedly increased as you are driven deeper into the city. "+
        "The First Gate still dominates the skyline to the north, "+
        "while the Ziggurat rises gracefully to the south. "+
	"Still to the northeast lays the bath house with "+
	"its concealed splendors, along a path lined with gorgeously "+
	"planted urns.\n");

    add_bath();
    add_inside();
}
