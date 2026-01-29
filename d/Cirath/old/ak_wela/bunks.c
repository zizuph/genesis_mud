/* innroom: Place to sleep in Golden Inix Inn
 *   Based on Prancing Pont Inn in Bree, which seems to have come
 *   from the Ri Albi hotel room and been modified all sorts.
 */

inherit "/std/room.c";
inherit "/d/Cirath/ak_wela/inherit/outside.c";
#include "/d/Cirath/common/defs.h"

void
create_room()
{
    set_short("A room in the Smiling Shark inn");
    set_long("This room has rice paper walls. You can hear your neighbours "+
             "snoring quite clearly. There is a matress made of straw "+
             "in the corner, otherwise the room is pretty empty. "+
             "Some symbols adorn the wall.\n");

    add_item(({"wall", "walls"}), "Walls made of rice paper. You don't "+
         "feel particularly safe, but you do not fell alone either, "+
         "as you can hear everyone sleeping here, not matter how hard" +
         "you try not to.\n");

    add_item("matress", "The straw matress looks fresh, and feels surprisingly "+
             "comfortable. You think you will be able to sleep here.\n");

    add_item(({"wall", "symbol", "symbols"}), "Painted on the wall "+
             "you recognise the symbols meaning that it is deemed safe for a "+
             "person to 'start here'.\n");

    INSIDE

    add_exit(AK_WELA_DIR+"inn", "down", 0, 1);
}

init()
{
    ::init();
    add_action("start","start");
}

int
start(string s)
{
    NF("Start where?\n");
    if(s!="here") return 0;
    
    if(!TP->query_prop("_have_bought_key"))
	{
	NF("You haven't bought a key.. you must have stolen someones.\n");
	return 0;
	}
    setuid();
    seteuid(getuid());
    TP->set_temp_start_location("/d/Cirath/mansho/bunks.c");
    write("You make yourself at home here, and feel confident that "+
          "you will wake up in here next time.\n");
return 1;
}
