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

#define HEARTROOM_ACTIVATED  "_wohs_test_heartroom_activated"

object door;

void
create_tower_room()
{
   set_short("upper level of the crimson tower of High Sorcery");
   set_long("You stand in a hallway on the upper level of the crimson " +
       "tower of High Sorcery. The hallway continues to your north and " +
       "south, while to your east is the entry to the tower's library.\n");

   add_item(({"upper level"}),"You stand on the upper level of the " +
       "crimson tower of High Sorcery.\n");
   add_item(({"hallway"}),"The hallway continues to your north and " +
       "south, while to your east is the entry to the tower's library.\n");
   add_item(({"staircases","stairs","broad staircases"}),"A staircase " +
       "leads down from here to the hall below.\n");
   add_item(({"tower's library","library"}),"To your east is the entry " +
       "to the tower's library.\n");

   set_tell_time(15);
   add_tell("The walls of the tower vibrate furiously!\n");
   add_tell("The tower rocks violently, as if it had been struck by a " +
       "wave of force!\n");
   add_tell("The stones of the tower begin to crack as spiderwebs of " +
       "energy spread across them.\n");
   add_tell("The tower begins to shake and rumble ominously!\n");
   add_tell("The walls of the tower groan, as if they were being " +
       "constricted by a powerful coil of force.\n");

   add_exit(WOHS_TEST + "room/daltigoth_tower7", "north", 0);
   add_exit(WOHS_TEST + "room/library", "east", 0);
   add_exit(WOHS_TEST + "room/daltigoth_tower6", "south", 0);

   door = clone_object(WOHS_TEST + "obj/heartroom_doora");
   door->move(this_object());

}

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
 
    if (interactive(ob) && TP->query_prop(HEARTROOM_ACTIVATED))
       start_room_tells();
}
