/*
   Test of High Sorcery room
*/

#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/wayreth/local.h"
#include "/d/Krynn/guilds/wohs/defs.h"
#include <ss_types.h>
#include <language.h>
#include <macros.h>

inherit WOHS_TEST_BASE;

object key, staff;

void
reset_tower_room()
{
    if(!objectp(key))
    {
       key = clone_object("/d/Krynn/guilds/wohs/test/obj/heartroom_key");
       key->move(TO);
    }

    if(!objectp(staff))
    {
       staff = clone_object("/d/Krynn/guilds/wohs/test/obj/wohs_test_staff");
       staff->move(TO);
    }
}

void
create_tower_room()
{
   set_short("the storage vault of the crimson tower of High Sorcery");
   set_long("You stand in the storage vault of the crimson tower of " +
       "High Sorcery, where all the most valuable magical items and " +
       "equipment are usually kept. Right now it is largely bare, with " +
       "its contents being evacuated to the Tower of Wayreth. A shadowy " +
       "portal leads out of the vault.\n");

   add_item(({"vault","storage vault"}), "You stand in the storage " +
       "vault of the Daltigoth Tower of High Sorcery. It is largely " +
       "empty, with its contents evacuated to the Tower of Wayreth.\n");
   add_item(({"magical items"}),"The room is bare of magical items, " +
       "having been evacuated to the safer location in the forest of " +
       "Wayreth. However you do wonder what once resided here.\n");
   add_item(({"shadowy portal","portal"}),"A portal leads out of the " +
       "vault here, its exit shadowed to the point where you can't " +
       "tell where it leads.\n");

   add_exit(WOHS_TEST + "room/shadow_hall", "out", 0);

   reset_tower_room();

}
