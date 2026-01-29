/*
   Test of High Sorcery room
*/

#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/wayreth/local.h"
#include "/d/Krynn/guilds/wohs/defs.h"
#include <ss_types.h>
#include <stdproperties.h>
#include <language.h>
#include <macros.h>

inherit WOHS_TEST_BASE;

int in_well = 0;
int well_message = 0;

void
create_tower_room()
{
   set_short("circular chamber before a shallow well");
   set_long("@@long_desc");

   add_item(({"circular chamber","chamber","room"}),
       "You stand within a circular chamber of dark obsidian, bare except " +
       "for a shallow well in the centre of the room.\n");
   add_item(({"dark obsidian","obsidian"}),
       "The chamber here is of dark obsidian, much like the rest of the " +
       "Tower of High Sorcery.\n");
   add_item(({"passage","shadowy passage","passageway"}),
       "A shadowy passage leads up towards " +
       "the surface and eventually back to the Hall of Mages.\n");
   add_item(({"well","shallow well"}),
       "The waters of the well sparkle with a prismatic radiance, " +
       "revealing teasing glimpses of scenes from the past, present and " +
       "future. Steps at the edge of the well allow you to wade into " +
       "the waters if you choose to.\n");
   add_item(({"waters","water","scenes"}),
       "Looking into the water, scenes from the past, present and future " +
       "twinkle before you, teasing you with glimpses without providing " +
       "much insight. One moment you see a knight of Solamnia fighting " +
       "back-to-back with a red-robed wizard against hordes of dread " +
       "beasts; then it ripples to a magical battle before a fortress " +
       "located on a small island in the Turbidus Ocean, where a " +
       "coterie of High Wizards furiously battle against renegades " +
       "garbed in gray. And then the scenes are gone.\n");  
   add_item(({"steps","edge of the well"}),"Steps on the edge of the " +
       "well lead into the shallow water. You can wade into the water " +
       "here if you so desire.\n");
   add_item(({"knight","knight of solamnia","red-robed wizard","wizards",
       "hordes","beasts","dread beasts","battle","magical battle",
       "fortress","island","small island","turbidus ocean","ocean",
       "coterie","high wizards","wizard","renegades"}),
       "That scene is now gone from the waters of the well, leaving you " +
       "with the impression you saw something of import from times long " +
       "past or perhaps something in your distant future?\n");

   INSIDE;

   add_cmd_item(({"into well","into water","well","water","into the waters",
       "into the water","into the well"}), ({"wade","enter"}),
       "@@enter_well");

   add_exit(WOHS_TEST + "room/passage1", "southeast", "@@check_well");

}

string
long_desc()
{
   if(well_message)
   {
      return "You are submerged in the River of Time, being carried " +
          "along with its radiant current!\n";
   }

   return "The passage has brought you down deep under the Tower of " +
       "High Sorcery to a circular chamber of dark obsidian. It is bare " +
       "except for a shallow well in the centre of the room.\n";
}

int
check_well()
{
   if(in_well)
   {
      write("You are trapped in the Rivers of Time, and cannot move in " +
          "that direction!\n");
      return 1;
   }
   return 0;
}

void
move_to_daltigoth_test(object player)
{

   if(player->query_prop(MAGIC_I_BREATHE_WATER))
       player->catch_msg("\nPondering what to do while magically " +
           "protected from drowning, you suddenly find yourself " +
           "elsewhere...\n");
   else
       player->catch_msg("\nAs your breath is about to explode from " +
           "your chest, you suddenly find yourself elsewhere...\n");
   player->move_living("vanishes into the well of time", WOHS_TEST + 
       "room/kadothan_grove1", 1, 0);
   in_well = 0;
   well_message = 0;
}

void
message1(object player)
{
   player->catch_msg("\nThe ripples caused by your entry cause the " +
       "sparkling water to flash with a dazzling radiance. You lose " +
       "your balance and fall backwards into the water!\n");
}

void
message2(object player)
{
   player->catch_msg("\nFully submerged, you cannot find your way to " +
       "the surface!\n");
}

void
message3(object player)
{
   player->catch_msg("\nThere is no surface! You are no longer in the " +
       "well under the Tower of High Sorcery, but travelling the " +
       "Rivers of Time!\n");
   well_message = 1;
}

string
enter_well()
{
   in_well = 1;
   write("You step into the shallow well, its prismatic waters " +
       "sparkling brightly around you...\n");
   set_alarm(4.0, 0.0, &message1(TP));
   set_alarm(7.0, 0.0, &message2(TP));
   set_alarm(12.0, 0.0, &message3(TP));
   set_alarm(20.0, 0.0, &move_to_daltigoth_test(TP));

   return "";
}

