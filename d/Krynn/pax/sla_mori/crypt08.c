/* Pax Tharkas, inside Sla-Mori.
 *
 * 950406 by Rastlin 
 */

#include <stdproperties.h>
#include "/d/Krynn/common/defs.h"
#include "../local.h"

inherit PAXINROOM;

object gDoor;
object gZombie;
int gZombieactive = 0;

void
create_pax_room()
{
    set_short("Crypt");
    set_long("@@my_desc");

    gDoor = clone_object(POBJ + "d_crypts");
    gDoor->set_other_room(PSLA + "tomb04");
    gDoor->set_pass_command(({"n", "north"}));

    add_item(({"bier", "stone bier"}), "A normal stone bier that is attached " +
		"to the wall.\n");

    gDoor->move(TO);

    add_prop(ROOM_I_LIGHT, 0);
}

start_zombie_alarm()
{
    set_alarm(3.0, 0.0, "start_zombies");
}

public void
start_zombies()
{
    object key;

    gZombieactive = 1;

    tell_room(TO, BS("Slowly the body begins to move. As you look into " +
                "the face of it, you start in horror: the once noble " +
		"guard has become a zombie-- one of the living dead. " +
		"The guard rises from the bier and slowly approaches " +
                "you.", 70));

    gZombie = clone_object(PMONSTER + "zombie_elf");
    gZombie->move(TO);

    if (PAXMASTER->query_zombie() == 8)
    {
	key = clone_object(POBJ + "tomb_key");
	key->move(gZombie);
    }
}

public string
my_desc()
{
    string desc;

    desc = "You are standing inside a small crypt. On the opposite side of " +
	"the crypt is a stone bier.";

    if (!gZombieactive)
        desc += " On the bier is a body of a tall figure " +
	"dressed in resplendent armour lying. Skeletal hands grasping the " +
	"hilt of a longsword lying across the body.";

    desc += " The room is totally free from dust and hasn't been visited " +
	"for many many years.\n";

    return desc;
}
