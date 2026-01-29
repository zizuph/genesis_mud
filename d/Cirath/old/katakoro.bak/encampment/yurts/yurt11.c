/* Empress' Yurt
 * Chaos, 19 April 1995
 */

inherit "/std/room";

#include "/d/Cirath/common/defs.h"
#include "/d/Cirath/common/mobber.h"

void
reset_room()
{
   bring_room_mob("empress",KAT_DIR+"NPC/empress.c",1,1);
}

void
create_room()
{

    set_short("the Empress' yurt");
    set_long("This yurt is the home of the Khahan's wife, the empress.  " +
	"The decore is spartan yet tasteful adding a livliness to the "+
	"usually dreariness of a yurt.  The decor matched with the "+
	"abundance of light provided by the many lamps make this yurt "+
	"seem more hospitable than many of the others.\n");

    add_exit(KAT_DIR+"encampment/camp12","out");
   reset_room();
}


