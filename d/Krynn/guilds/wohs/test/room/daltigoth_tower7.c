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

#define GRANTED_ACCESS     "_wohs_test_given_fourth_task"
#define HEARTROOM_ACTIVATED  "_wohs_test_heartroom_activated"

void
create_tower_room()
{
   set_short("upper level of the crimson tower of High Sorcery");
   set_long("You stand in a hallway on the upper level of the crimson " +
       "tower of High Sorcery. The hallway continues south, while to " +
       "your east is the entry to a large, shadowy chamber.\n");

   add_item(({"upper level"}), "You stand on the upper level of the " +
       "crimson tower of High Sorcery. A staircase leads down from " +
       "here to the hall below.\n");

   add_item(({"hallway"}),"The hallway continues to your south, while " +
       "to your east is the entry to a large, shadowy chamber.\n");

   add_item(({"shadowy chamber","chamber"}),"To your east is the entry " +
       "to a large, shadowy chamber. You can't make out much of the " +
       "room from the hallway... you'll need to enter it.\n");

   add_item(({"staircases","stairs","broad staircases"}), "A staircase " +
       "leads down from here to the hall below.\n");

   set_tell_time(15);
   add_tell("The walls of the tower vibrate furiously!\n");
   add_tell("The tower rocks violently, as if it had been struck by a " +
       "wave of force!\n");
   add_tell("The stones of the tower begin to crack as spiderwebs of " +
       "energy spread across them.\n");
   add_tell("The tower begins to shake and rumble ominously!\n");
   add_tell("The walls of the tower groan, as if they were being " +
       "constricted by a powerful coil of force.\n");

   add_exit(WOHS_TEST + "room/daltigoth_tower8", "south", 0);
   add_exit(WOHS_TEST + "room/shadow_hall", "east", "@@granted_access");
   add_exit(WOHS_TEST + "room/daltigoth_tower5", "down", 0);

}

int
granted_access()
{
      if(TP->query_prop(GRANTED_ACCESS) || TP->query_wiz_level())
      {
         return 0;
      }

      write("The Tower does not allow you access to the Hall of " +
          "Shifting Shadows. You would need permission from the Master " +
          "of the Tower to enter this chamber.\n");
      return 1;          

}

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
 
    if (interactive(ob) && TP->query_prop(HEARTROOM_ACTIVATED))
       start_room_tells();
}