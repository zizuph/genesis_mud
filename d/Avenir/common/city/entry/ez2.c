// file name:  /d/Avenir/common/city/entry/ez2.c
// creator(s): Lucius
// revisions:	Lucius Oct 2008
// purpose:
// note: based on e5.c by Lilith.
// bug(s):
// to-do:
#pragma strict_types

#include "entry.h"
inherit ENTRY_ROOM;

static void
create_entry_room(void)
{
    set_short("yellow stone path, inside the Forbidden City");
    set_long("Sedan chairs flow along the path, making the occasional "+
        "abrupt change of direction in order to avoid collision as "+
        "the bondservants pull their passengers to and from the Ziggurat "+
	"and other points within the Forbidden City. The terraced pyramid "+
        "known as the Ziggurat dominates the view to the south. Breaks in "+
	"the walls to the east and west reveal glimpses of the enclaves "+
	"for the Lords Executioner and Inquisitor. Beyond the Ziggurat "+
	"looms the High Commissoners enclave.\n");

    add_inside();
}
