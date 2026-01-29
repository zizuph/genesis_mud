/* Pax Tharkas, inside Sla-Mori.
 *
 * 950408 by Rastlin 
 */

#include <stdproperties.h>
#include <macros.h>
#include "/d/Krynn/common/defs.h"
#include "../local.h"

inherit PAXINROOM;

public string door_line();

object gDoorN, gDoorS;

void
reset_doors()
{
    gDoorN->crypt_close_door();
    gDoorS->crypt_close_door();
    tell_room(TO,"With a scraping sound the doors to the crypts slowly " +
	      "close.\n");
}

void
reset_pax_room()
{
    if (random(2))
      return;
    reset_doors();
    (PSLA + "tomb02")->reset_doors();
    (PSLA + "tomb03")->reset_doors();
    (PSLA + "tomb04")->reset_doors();
}

void
create_pax_room()
{
    set_short("East part of the tomb");
    set_long("@@my_desc");

    add_item("dust", "The dust seems to be very, very old.\n");

    add_item("floor", "There is a lot of dust and loose chunks of rock " +
		"on the floor.\n");

    add_item(({"track", "tracks"}), BS("It is tracks of rats and none of " +
		"the tracks are approaching the doors.", 70));

    add_item("hole", "Looking through the hole you can see a tunnel.\n");

    add_cmd_parse("[the] 'hole'", "enter", "@@do_enter");

    add_exit(PSLA + "tomb02", "west");

    seteuid(getuid());

    gDoorN = clone_object(POBJ + "d_crypts");
    gDoorN->set_other_room(PSLA + "crypt01");
    gDoorN->set_pass_command(({"n", "north"}));
    gDoorN->set_direction("north");
    gDoorN->move(TO);

    gDoorS = clone_object(POBJ + "d_crypts");
    gDoorS->set_other_room(PSLA + "crypt02");
    gDoorS->set_pass_command(({"s", "south"}));
    gDoorS->set_direction("south");
    gDoorS->move(TO);

    add_prop(ROOM_I_LIGHT, 0);
}

public int
do_enter()
{
    set_dircmd("hole");
    TP->move_living("through the hole", PSLA + "tunnel07", 0);
    return 1;
}

public string
my_desc()
{
    string desc;

    desc = "You are standing in the east end of a large hall, obviously constructed " + 
	"with care in some distant age. A wide center aisle stretches " +
	"westward into the darkness. On each side of the hall is a " +
	"stone door. " + door_line() + ". In the east rock wall is " +
	"a huge hole. This is where the evil is centered. The tracks " +
	"in the dust are " + 
	"few and none of the them approach the doors. This is the " +
	"tomb of Kith-Kanan's elite royal guard. Through a lifetime " +
	"of valued service to their lord, these honored elves, " +
	"dwarves, and men have earned the right to burial here.";

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

void
open_other_doors()
{
    open_doors();
    (PSLA + "tomb02")->open_doors();
    (PSLA + "tomb03")->open_doors();
    (PSLA + "tomb04")->open_doors();
}
