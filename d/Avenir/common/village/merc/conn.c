// file name:	/d/Avenir/common/village/merc/conn.c
// creator(s):	Lucius Oct 2008
// revisions:	
// purpose:
// note:           
// bug(s):
// to-do:
#pragma strict_types

#include "../village.h"  
inherit MERC_BASE;

static void
create_merc_room(void)
{
    set_short("pathway between bazaar and garment district");
    set_long("A depressed bowl lies at the south end of this "+
	"sloped, cobblestone lane. To either side run hedges "+
	"which meet a horseshoe shaped stone wall which further "+
	"encircles the area south, known as the garment district. "+
        "The clamour from the bazaar beyond blends with the muted "+
        "sounds of the garment merchants hawking their wares, "+
        "ensuring that silence is a rare commodity here.\n");

    add_hedge();

    add_tell("Lilting, sybarite, voices are brought to you on a "+
	"breeze from the south.");

    add_exit(BAZAAR + "extr/str24", "north", 0);
    add_exit("01", "south", 0);
}
