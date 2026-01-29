// file name:        /d/Avenir/common/city/entry/e6.c
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
    set_short("blue slate path, halfway between the Bath and "+
        "the First Gate");
    set_long("This blue slate path runs between the First Gate "+
        "and Melchior's bath. Far to the west is the courtyard at "+
        "the foot of the Gate, and beyond it, a dark structure. "+
        "Southwest, the Ziggurat stands, pleasure palace "+
        "of the High Lords of Sybarus. Directly south can be seen "+
        "the wall enclosing the Executioner's enclave. "+
        "Bondservants pulling sedan chairs dodge between the large, "+
        "beautifully planted urns lining "+
        "this path.\n");

    add_outside();
    add_bath();
    add_zig();
    add_urns();
    add_walls();

    add_item(({"arena", "small arena"}),
        "It appears to be a practice arena for guards who are waiting to "+
        "go on shift.\n");

    add_item(({"dark structure", "dungeon"}),
        "A stark and imposing building, made of the dark island stone excavated "+
        "during the building of the City walls. Its only embellishment is "+
        "the bars that have been installed over its few windows. It is "+
        "situated just beyond the arena, against a natural outcropping.\n");
}
