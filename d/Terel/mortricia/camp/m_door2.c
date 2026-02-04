/*
 * A wooden door for the manager's secret room. Mortricia 920929
 */
inherit "/std/door";

#include "/d/Terel/common/terel_defs.h"

#define CAMP_DIR     MORTRICIADIR + "camp/"

create_door() {
    ::create_door();

    set_door_id("manager_door");
    set_pass_command(({"e", "east"}));
    set_door_name(({"door", "wooden door"}));
    set_other_room(CAMP_DIR + "mana_carr");
    set_lock_name("lock");
    set_lock_command("lock");
    set_unlock_command("unlock");

/* This door is closed and locked */
    set_open(0);
    set_locked(1);
}
