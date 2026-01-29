/* Pax Tharkas, inside Sla-Mori.
 *
 * 950406 by Rastlin 
 */

#include <stdproperties.h>
#include "/d/Krynn/common/defs.h"
#include "../local.h"

inherit PAXINROOM;

object gDoorN, gDoorS;

public string door_line();

void
reset_doors()
{
    gDoorN->crypt_close_door();
    gDoorS->crypt_close_door();
    tell_room(TO,"With a scraping sound the doors to the crypts slowly " +
	      "close.\n");
}

void
create_pax_room()
{
    set_short("Tomb");
    set_long("@@my_desc");

    add_item("dust", "The dust seems to be very, very old.\n");

    add_item("floor", "There is a lot of dust and loose chunks of rock " +
		"on the floor.\n");

    add_item(({"track", "tracks"}), BS("It is tracks of rats and none of " +
		"the tracks are approaching the doors.", 70));

    add_exit(PSLA + "tomb02", "east");
    add_exit(PSLA + "tomb04", "west");

    seteuid(getuid());

    gDoorN = clone_object(POBJ + "d_crypts");
    gDoorN->set_other_room(PSLA + "crypt05");
    gDoorN->set_pass_command(({"n", "north"}));
    gDoorN->set_direction("north");
    gDoorN->move(TO);

    gDoorS = clone_object(POBJ + "d_crypts");
    gDoorS->set_other_room(PSLA + "crypt06");
    gDoorS->set_pass_command(({"s", "south"}));
    gDoorS->set_direction("south");
    gDoorS->move(TO);

    add_prop(ROOM_I_LIGHT, 0);
}

public string
my_desc()
{
    string desc;

    desc = "You are standing in the west part of a large hall, " +
	"obviously constructed with " +
	"care in some distant age. A wide center aisle stretches east " +
	"and westward into the darkness. This is the " +
	"tomb of Kith-Kanan's elite royal guard. On " +
	"each side of the hall is a stone door. " + door_line() + ". " +
	"This is where the malevolent evil is centered. The tracks " +
	"in the dust are few and none of the them approach the doors.";

    return BS(desc, 70);
}

public string
door_line()
{
    string desc;

    if (gDoorN->query_open() && gDoorS->query_open())
	return "Both the north and the south door are open";

    if (!gDoorN->query_open() && !gDoorS->query_open())
	return "Both the north and south door are closed";

    if (gDoorN->query_open())
	return "The north stone door is wide open but the south door is closed";
    else
	return "The north door is closed and south door is open";
}

void
open_doors()
{
    tell_room(TO, BS("Suddenly you hear the sound of huge stone blocks " +
	"shifting, of rusting iron hings creaking. Each of the stone doors begin " +
	"to swing wide. The hallway is filled with a cold so severe that " +
	"your feeling in your fingers goes numb.", 70));

    if (!gDoorN->query_open() && !gDoorS->query_open())
    {
	gDoorN->crypt_open_door();    
	gDoorS->crypt_open_door();
	return;
    }

    if (!gDoorN->query_open())
    {
	gDoorN->crypt_open_door();
	return;
    }
    else
    {
	gDoorS->crypt_open_door();
	return;
    }
}
