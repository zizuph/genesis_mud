// file name:        /d/Avenir/common/city/entry/e8.c
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
    set_short("blue slate path, right near the Bath");
    set_long("Sedan chairs flow along the path, making the occasional "+
        "abrupt change of direction in order to avoid collision as "+
        "the bondservants pull their passengers to and from the Bath. "+
        "Directly south can be seen the wall enclosing the Executioner's "+
        "enclave. The First Gate still dominates the skyline to the "+
        "north and west, even though it lies some distance away. "+
        "Carried upon the breeze is the scent of herbs and essential "+
        "oils from the low, domed building of Melchior's bath.\n");

    add_outside();
    add_bath();
    add_zig();
    add_urns();
    add_walls();
}
