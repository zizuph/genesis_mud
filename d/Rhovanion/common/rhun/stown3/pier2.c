
/* Pier #2 in SmallTOWN3, where the ship to Pier3 in Emerald starts
 * (ship2)
 * Copied from examples supplied by Plugh.
 */

#pragma save_binary

inherit "/d/Rhovanion/lib/room";
#include <macros.h>
#include "/sys/stdproperties.h"
#include "/d/Rhovanion/farlong.h"

void load_ship();

void
create_room()
{
set_short("Pier");
set_long(break_string("A heavy wooden pier extends into the River"
	+" Carnen here, where a faraway ship sometimes ties up.  A"
       +" stout wooden sign stands nearby.  On it is painted a"
	+" depiction of a glowing green gemstone, now faded by time"
	+" and nature's influences.  A section of the pier extends"
	+" southeast, connecting with the nearby town."
	+"\n",75));

AE(RHUN+"stown3/pier1","southeast",0);

add_item("sign",break_string("The sign bears"
	+" a picture of a glowing green gem.\n",75));

add_prop(ROOM_I_LIGHT,1);

/* This room preloads to start the ship line */
add_prop(ROOM_I_NO_CLEANUP ,1);

    add_prop(OBJ_S_WIZINFO, "@@wizinfo@@");

#ifdef Genesis
    load_ship();
#endif
}

void
load_ship()
{
    object ship;

    add_prop(ROOM_I_NO_CLEANUP, 1);

    seteuid(getuid());
    ship=clone_object(RHUN+"ships/ship2");
    ship->move(this_object());
    ship->start_ship();
}

string
wizinfo()
{
    return break_string("To restart the ship line, first make sure it "+
	   "is not already running. If it is, it should be removed "+
	   "completely (ie. ship & captain destructed). If the ship have "+
	   "been changed, update it before restarting.\n",76) + "\n" +
	   "To actually load & restart the ship, give the following command:\n\n"+
	   "  Call here load_ship\n";
}

