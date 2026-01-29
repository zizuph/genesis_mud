/*
 * pdoor1.c
 * By Skippern
 *
 * November 2000
 */
#pragma save_binary

#include "../erech.h"

inherit "/std/door";

public void
create_door()
{
    ::create_door();
    set_door_id("erechfield");
    set_pass_command(({"se","southeast"}));
    set_door_name(({"gate","small gate","white gate","small white gate"}));
    set_other_room(E_FIELD + "G6.c");
    set_door_desc("This is a small white gate, commonly used in Gondor as " +
	"farm or house gates. It is made out of tiny planks nailed together " +
	"with two horizontal and many vertical planks. It is painted white. " +
	"\n");
    set_lock_command("lock");
    set_lock_name("padlock");
    set_unlock_command("unlock");
    set_open(0);
    set_locked(0);
    set_pick(35);
    set_key("ErechFarmGate");
    set_knock_command("knock");
}
