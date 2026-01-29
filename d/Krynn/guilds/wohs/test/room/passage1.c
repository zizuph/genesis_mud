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

void
create_tower_room()
{
   set_short("shadowy passage in the Tower of High Sorcery");
   set_long("You are walking along a shadowy passage leading " +
      "down under the Tower of High Sorcery. To your east " +
      "the passageway opens up into darkness, likely the " +
      "Hall of Mages, while the passageway bends sharply " +
      "downwards to your northwest.\n");

   add_item(({"shadowy passage","passage","passageway"}),
      "You are walking down a shadowy passage within the Tower of " +
      "High Sorcery. To your east the passageway opens up into " +
      "a vast dark chamber - the Hall of Mages - while it " +
      "bends sharply to your northwest, leading down under the " +
      "Tower.\n");
   add_item(({"tower","tower of high sorcery"}),
      "You stand in a passageway within the Tower of High Sorcery.\n");
   add_item(({"hall of mages","hall","chamber"}),
      "To your east is the Hall of Mages. Returning there now without " +
      "having completed the Test would not be a good idea.\n");

   INSIDE;

   add_exit(WTOWER + "hall_of_mages", "east", "@@cant_go_back");
   add_exit(WOHS_TEST + "room/passage2", "northwest", "@@go_northwest");

}

int
cant_go_back()
{
   write("Returning now to the Hall of Mages would result in you " +
         "failing the Test of High Sorcery... certain death! You " +
         "must continue on to your northwest.\n");
   return 1;
} 

int
go_northwest()
{
   write("You follow the shadowy passageway down under the Tower of " +
         "High Sorcery to a chamber below...\n");
   return 0;
} 