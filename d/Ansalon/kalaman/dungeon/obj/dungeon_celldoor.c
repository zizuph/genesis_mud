/* 
 * Dungeon Celldoors
 *
 * Lunatari 2008-01-28
 */
#include "/d/Ansalon/kalaman/local.h"
inherit STDDOOR;

create_door()
{
    ::create_door();
    set_door_id("kmancell1");
    set_pass_command("north");
    set_door_name(({"cell door","door"}));
    set_other_room(DUNGEON + "cell1");
    set_door_desc("This is a massive door made out of sturdy oak and with " +
      "a steel barred window. The door hangs on sturdy hinges.\n");
    set_lock_command("lock");
    set_lock_mess(({"locks the cell door.\n","You lock the cell.\n"}));
    set_fail_lock(({"The door is already locked.\n","Lock an open door?\n"}));
    set_unlock_command("unlock");
    set_unlock_mess(({"unlocks the cell door.\n","You unlock " +
	"the cell door with a noisy 'click' of the lock.\n"}));
    set_fail_unlock("The door is already unlocked.\n");
    set_pick(50);
    set_open(0);
    set_locked(1);
    set_key("_kalaman_general_cell_key");
}

/*
    gDoorN = clone_object(POBJ + "d_crypts");
    gDoorN->set_other_room(PSLA + "crypt07");
    gDoorN->set_pass_command(({"n", "north"}));
    gDoorN->set_direction("north");
    gDoorN->move(TO);

    gDoorS = clone_object(POBJ + "d_crypts");
    gDoorS->set_other_room(PSLA + "crypt08");
    gDoorS->set_pass_command(({"s", "south"}));
    gDoorS->set_direction("south");
    gDoorS->move(TO);

    gDoorW = clone_object(POBJ + "d_tomb04");
    gDoorW->move(TO);
    gDoorW->set_key(TOMB_KEY);
*/
