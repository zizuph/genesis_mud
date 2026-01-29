// file name:        /d/Avenir/common/city/entry/e5.c
// creator(s):       Lilith, June 2003
// revisions:	Lucius Oct 2008
// purpose:
// note:
// bug(s):
// to-do:
#pragma strict_types

#include "entry.h"
inherit ENTRY_ROOM;

static void
create_entry_room(void)
{
    set_short("blue slate path, about a third of the way to the Bath");
    set_long("Sedan chairs flow along the path, making the occasional "+
        "abrupt change of direction in order to avoid collision as "+
        "the bondservants pull their passengers to and from the Bath. "+
        "A stepped hill rises nearby, surrounded by a curving wall, "+
        "and beyond it, to the south, can be seen the terraced pyramid "+
        "known as the Ziggurat. East lays the bath house with its "+
        "concealed splendors, along a path lined with gorgeously "+
        "planted urns.\n");

    add_outside();
    add_bath();
    add_zig();
    add_urns();
    add_walls();
}
