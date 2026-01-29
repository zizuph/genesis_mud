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

string *bronze_str = ({"You notice Nuitari is waning, while Solinari " +
    "and Lunitari are at high sanction", "You notice Nuitari is " +
    "waning, while Solinari and Lunitari are waxing", "You notice " +
    "Nuitari is waxing, while Solinari and Lunitari are at high sanction"});

string *silver_str = ({"You notice Nuitari is at low sanction, while " +
    "Solinari and Lunitari are waxing", "You notice Solinari and " +
    "Nuitari are waxing, while Lunitari is at high sanction",    
     "You notice Solinari is waxing, Nuitari at low sanction, and " +
     "Lunitari at high sanction"});

string *copper_str = ({"You notice Nuitari is at low sanction, " +
    "Solinari waxing, and Lunitari at high sanction", "You notice " +
    "Nuitari is at low sanction, while Solinari and Lunitari are waxing",    
    "You notice Nuitari is at waning, while Solinari and Lunitari are " +
    "waxing"});

#define WOHS_MIRROR_PORTAL_PROP    "_wohs_mirror_portal_prop"
#define WOHS_MIRROR_MOON_SEQUENCE  "_wohs_test_mirror_moon_sequence_prop"
#define WOHS_MIRROR_NUMBER_FAILED  "_wohs_test_mirror_number_failed_attempts"

void
reset_tower_room()
{
    return;
}

void
create_tower_room()
{
   set_short("Shadowy room of mirrors");
   set_long("You stand in triangular room of ever-shifting shadows, " +
       "swirling through the room like a dark fog. There are no obvious " +
       "exits here, however three tall mirrors hang on each wall.\n");

   add_item(({"triangular room","room"}),
       "You are really stretching the definition of 'room' by " +
       "describing this space as such. It is more a space with " +
       "boundaries of shadows.\n");
   add_item(({"shadows","ever-shifting shadows","dark fog","fog"}),
       "This room seems to consist entirely shadows, with the exception " +
       "of three mirrors the hang on the shadowy walls here.\n");
   add_item(({"tall mirrors","mirrors","wall","walls","shadowy walls",
       "three tall mirrors","three mirrors"}),
       "Three tall mirrors hang on each of the three walls here - a " +
       "bronze mirror, a silver mirror, and a copper mirror.\n");
   add_item("mirror","Which mirror did you want to examine? The bronze " +
       "mirror, silver mirror or the copper mirror?\n");

   add_item("bronze mirror","@@exa_bronze_mirror");
   add_item("silver mirror","@@exa_silver_mirror");
   add_item("copper mirror","@@exa_copper_mirror");

   add_cmd_item("mirror",({"enter"}),"Enter which mirror?\n");
   add_cmd_item("bronze mirror",({"enter"}), "@@enter_bronze_mirror");
   add_cmd_item("silver mirror",({"enter"}), "@@enter_silver_mirror");
   add_cmd_item("copper mirror",({"enter"}), "@@enter_copper_mirror");

   reset_tower_room();
}

string
exa_bronze_mirror()
{
   int mirror_setting = TP->query_prop(WOHS_MIRROR_MOON_SEQUENCE);

   return "Staring into the bronze mirror you notice no reflection " +
       "of yourself looks back at you! Instead you see the night's sky " +
       "above the Tower of High Sorcery in Daltigoth and the three " +
       "moons of magic - Solinari, Lunitari and even the black moon " +
       "Nuitari! " +bronze_str[mirror_setting]+ ".\n";
}

string
exa_silver_mirror()
{
   int mirror_setting = TP->query_prop(WOHS_MIRROR_MOON_SEQUENCE);

   return "Staring into the silver mirror you notice no reflection " +
       "looks back at you! Instead you see the night's sky above the " +
       "Tower of High Sorcery in Daltigoth and the three moons of " +
       "magic - Solinari, Lunitari and even the black moon Nuitari! " +
       silver_str[mirror_setting]+ ".\n";
}

string
exa_copper_mirror()
{
   int mirror_setting = TP->query_prop(WOHS_MIRROR_MOON_SEQUENCE);

   return "Staring into the copper mirror you notice no reflection " +
       "looks back at you! Instead you see the night's sky above the " +
       "Tower of High Sorcery in Daltigoth and the three moons of " +
       "magic - Solinari, Lunitari and even the black moon Nuitari! " +
       copper_str[mirror_setting]+ ".\n";
}

string
enter_bronze_mirror()
{
   int mirror_setting = TP->query_prop(WOHS_MIRROR_MOON_SEQUENCE);
   int failed_attempt;

   if(!TP->query_prop(WOHS_MIRROR_NUMBER_FAILED))
      failed_attempt = 0;
   else
      failed_attempt = TP->query_prop(WOHS_MIRROR_NUMBER_FAILED);

   if(mirror_setting == 2)
   {
      write("You step through the mirror and in to another room...\n");
      say(QCTNAME(TP)+ " walks into the mirror and vanishes! " +C(HIS(TP))+
          " image appears in the reflection of the mirror briefly, " +
          "before returning to normal.\n");
      TP->move_living("M", "/d/Krynn/guilds/wohs/test/room/shadows5", 1, 0);
      return "";
   }
   else
   {
      write("You step through the mirror and find yourself back in the " +
          "Hall of Shadows.\n");
      say(QCTNAME(TP)+ " walks into the mirror and vanishes! " +C(HIS(TP))+
          " image appears in the reflection of the mirror briefly, " +
          "before returning to normal.\n");
      TP->add_prop(WOHS_MIRROR_NUMBER_FAILED, failed_attempt + 1);
      TP->move_living("M", "/d/Krynn/guilds/wohs/test/room/shadow_hall", 
          1, 0);
      return "";
   }   
}

string
enter_silver_mirror()
{
   int mirror_setting = TP->query_prop(WOHS_MIRROR_MOON_SEQUENCE);
   int failed_attempt;

   if(!TP->query_prop(WOHS_MIRROR_NUMBER_FAILED))
      failed_attempt = 0;
   else
      failed_attempt = TP->query_prop(WOHS_MIRROR_NUMBER_FAILED);

   if(mirror_setting == 1)
   {
      write("You step through the mirror and in to another room...\n");
      say(QCTNAME(TP)+ " walks into the mirror and vanishes! " +C(HIS(TP))+
          " image appears in the reflection of the mirror briefly, " +
          "before returning to normal.\n");
      TP->move_living("M", "/d/Krynn/guilds/wohs/test/room/shadows5", 1, 0);
      return "";
   }
   else
   {
      write("You step through the mirror and find yourself back in the " +
          "Hall of Shadows.\n");
      say(QCTNAME(TP)+ " walks into the mirror and vanishes! " +C(HIS(TP))+
          " image appears in the reflection of the mirror briefly, " +
          "before returning to normal.\n");
      TP->add_prop(WOHS_MIRROR_NUMBER_FAILED, failed_attempt + 1);
      TP->move_living("M", "/d/Krynn/guilds/wohs/test/room/shadow_hall", 
          1, 0);
      return "";
   }   
}

string
enter_copper_mirror()
{
   int mirror_setting = TP->query_prop(WOHS_MIRROR_MOON_SEQUENCE);
   int failed_attempt;

   if(!TP->query_prop(WOHS_MIRROR_NUMBER_FAILED))
      failed_attempt = 0;
   else
      failed_attempt = TP->query_prop(WOHS_MIRROR_NUMBER_FAILED);

   if(mirror_setting == 0)
   {
      write("You step through the mirror and in to another room...\n");
      say(QCTNAME(TP)+ " walks into the mirror and vanishes! " +C(HIS(TP))+
          " image appears in the reflection of the mirror briefly, " +
          "before returning to normal.\n");
      TP->move_living("M", "/d/Krynn/guilds/wohs/test/room/shadows5", 1, 0);
      return "";
   }
   else
   {
      write("You step through the mirror and find yourself back in the " +
          "Hall of Shadows.\n");
      say(QCTNAME(TP)+ " walks into the mirror and vanishes! " +C(HIS(TP))+
          " image appears in the reflection of the mirror briefly, " +
          "before returning to normal.\n");
      TP->add_prop(WOHS_MIRROR_NUMBER_FAILED, failed_attempt + 1);
      TP->move_living("M", "/d/Krynn/guilds/wohs/test/room/shadow_hall", 
          1, 0);
      return "";
   }   
}