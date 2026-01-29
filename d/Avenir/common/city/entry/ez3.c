// file name:  /d/Avenir/common/city/entry/ez3.c
// creator(s): Lucius
// revisions:	Lucius Oct 2008
// purpose:
// note: based on e6.c by Lilith.
// bug(s):
// to-do:
#pragma strict_types

#include "entry.h"
inherit ENTRY_ROOM;

static void
create_entry_room(void)
{
    set_short("yellow stone path, between the Ziggurat and the Gate");
    set_long("On a yellow stone path running between the First Gate "+
        "and the Ziggurat. Far to the north is the courtyard at "+
        "the foot of the Gate. Directly south, the Ziggurat stands, "+
	"pleasure palace of the High Lords of Sybarus. Further south "+
	"can be seen the wall enclosing the Hegemon's enclave. Likewise "+
	"to the east a wall surrounding Executioner's Palace and west the "+
	"Inquisitors enclave. Bondservants pulling sedan chairs dodge "+
	"between the large, beautifully planted urns lining this path.\n");

    add_inside();
}
