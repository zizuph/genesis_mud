/* Sentry's Yurt
 * Chaos, 5 April 1995
 */

inherit "/std/room";

#include "/d/Cirath/common/defs.h"
#include "/d/Cirath/common/teamer.h"

#define PATH "/d/Cirath/katakoro/"

void
create_room()
{
    bring_room_team(PATH+"NPC/offguard",1,7);
    
    set_short("Sentry's yurt");
    set_long("This yurt acts as quarters for the arban of men assigned "+
	"as guards "+
	"to this part of the camp.  It is kept in good order, with the "+
	"bedrolls of the men on duty placed out of the way.  There is a "+
	"small cooking fire burning near the center, around which are "+
	"four guards, probably the ones that will go on duty next.  Four "+
	"other guards are resting on their bedrolls.  The only exit "+
	"is back out.\n");

    add_item("yurt","This yurt has been kept very clean.  The thick "+
	"felt carpet on the floor shows little sign of wear, and "+
	"there is no sign of dirt.  The men have kept it so clean out "+
	"of fear of thier commanders.\n");
    add_item("bedrolls","Currently these are occupied by four guards who "+
	"appear to be sleeping.  Though resting, they could quickly rush "+
	"to the assistance of thier comrades.\n");
    add_item("fire","Something unusual smelling is cooking over the fire, "+
	"probably horsemeat, a common staple in a soldiers diet.\n");

    add_prop(ROOM_I_INSIDE,1);

    add_exit(PATH+"encampment/camp2","out");
}
