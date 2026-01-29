/* Empress' Guard's Yurt
 * Chaos, 5 April 1995
 */

inherit "/std/room";

#include "/d/Cirath/common/defs.h"
#include "/d/Cirath/common/teamer.h"

#define PATH "/d/Cirath/katakoro/"

void
create_room()
{
    bring_room_team(PATH+"NPC/kashik",1,4);
    
    set_short("Guard's yurt");
    set_long("This yurt acts as quarters for the arban assigned "+
	"to guard the Empress.  It is kept in good order, with the "+
	"bedrolls of the men on duty placed out of the way.  There is a "+
	"small cooking fire burning near the center, around which are "+
	"five guards, probably the ones that will go on duty next.\n");

    add_item("yurt","This yurt has been kept very clean.  The thick "+
	"felt carpet on the floor shows little sign of wear, and "+
	"there is no sign of dirt.  The men have kept it so clean out "+
	"of fear of thier commanders.\n");
    add_item("fire","Something unusual smelling is cooking over the fire, "+
	"probably horsemeat, a common staple in a soldiers diet.\n");

    add_prop(ROOM_I_INSIDE,1);

    add_exit(PATH+"encampment/camp20","out");
}
