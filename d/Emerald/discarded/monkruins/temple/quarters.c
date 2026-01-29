inherit "/std/room";
 
#include "/d/Emerald/defs.h"
 
void create_room()
{
    set_short("Living quarters");
	set_long("   You have entered the monk's living quarters in " +
	"the monastary. All the monks are probably busy now, since " +
      "nobody prevented you from walking in their private "+
	"chambers. The walls and floors are completely devoid of ornamentation.\n\n");
    add_exit(TEMPLE_DIR + "monastery", "north", 0);
    add_exit(TEMPLE_DIR + "dormatory", "south", 0);
}
