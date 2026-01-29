// file name:        /d/Avenir/common/city/entry/e4.c
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
    set_short("blue slate path, between the Bath and the First Gate");
    set_long("Few of the visitors to the Bath actually walk there "+
        "themselves, as can be seen by the number of sedan chairs "+
        "coming and going along this path. The First Gate dominates "+
        "the skyline west, while the Ziggurat rises gracefully to "+
        "the south. East lays the bath house with its concealed "+  
        "splendors, along a path lined with gorgeously planted "+
        "urns.\n");

    add_outside();
    add_bath();
    add_zig();
    add_urns();
    add_walls();
}
