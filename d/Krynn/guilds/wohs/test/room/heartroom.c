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
#define HEARTROOM_ATTEMPTS   "_wohs_test_heartroom_activation_attempts"

object door;
string tower_dir = "east";
int tower_locked = 0;

void
reset_tower_room()
{
    return;
}

void
create_tower_room()
{
   set_short("heartroom of the crimson tower of High Sorcery");
   set_long("You stand in the heartroom on the upper level of the " +
            "crimson tower of High Sorcery. The room is bare with " +
            "the exception of a rune-covered stone table that stands " +
            "in the center of the room, displaying a miniature replica " +
            "of the Tower of Daltigoth.\n");

   add_item(({"rune-covered stone table","stone table","table"}),
            "In the center of the heartroom stands a rune-covered " +
            "stone table. Atop of it is a detailed miniature replica " +
            "of the Tower of Daltigoth, create in the most exquisite " +
            "of detail.\n");
   add_item(({"replica","miniature replica","miniature"}),
            "@@miniature_desc");
   add_item(({"model","model of the red tower","red tower","tower"}), 
            "@@tower_desc");
   add_item(({"magical energy","energy","flow of energy","flow","force"}), 
            "You cannot see the magical energy, however " +
            "can certainly feel it thrumming through the room... the " +
            "force holding the Tower of High Sorcery together.\n");

   door = clone_object(WOHS_TEST + "obj/heartroom_doorb");
   door->move(this_object());

   set_tell_time(25);
   add_tell("The walls of the tower vibrate furiously!\n");
   add_tell("The tower rocks violently, as if it had been struck by " +
            "a wave of force!\n");
   add_tell("The stones of the tower begin to crack as spiderwebs of " +
            "energy spread across them.\n");
   add_tell("The tower begins to shake and rumble ominously!\n");
   add_tell("The walls of the tower groan, as if they were being " +
            "constricted by a powerful coil of force.\n");

   reset_tower_room();
}

string
miniature_desc()
{
     if(TP->query_skill(SS_SPELLCRAFT) < 70)
           return "Atop the rune-covered table in the middle of the " +
               "room is a miniature replica of the Tower of Daltigoth, " +
               "created down to the finest of detail.\n";
     else
           return "Atop the rune-covered table in the middle of the " +
               "room is a miniature replica of the Tower of Daltigoth, " +
               "created down to the finest of detail. Your sensitivity " +
               "to magic recognises a powerful flow of energy passing " +
               "through the model of the red tower. You think if you " +
               "turn it to face a certain direction, it should disrupt " +
               "the flow of energy.\n";
}

void
set_red_tower_direction(string str)
{
     tower_dir = str;     
}

string
query_red_tower_direction()
{
     return tower_dir;
}

void
set_red_tower_locked(int locked)
{
     tower_locked = locked;     
}

int
query_red_tower_locked()
{
     return tower_locked;
}

string
tower_desc()
{
     return "In the center of the miniature replica of the Tower of " +
          "Daltigoth is a small model of a red tower, facing " +
          query_red_tower_direction()+ ".\n";
}

void
farewell_message(object player)
{
   TP->catch_msg("A gust of wind whispers past you, followed by a " +
          "message from Iriale: Just in time! The Ergothian legions " +
          "have breached the walls. Escape if you can before the Tower " +
          "destructs, Aspirant. I will hold the doors to the Tower " +
          "until then. Fare thee well, " +C(TP->query_real_name())+ "!\n");
   return;
}

string
turn_tower(string str)
{
   int attempts = 0;

   if(!stringp(str) || !strlen(str))
   {
      write("Turn what?\n");
      return "";
   }

   if(str == "tower" || str == "miniature tower" || str == "red tower" ||
      str == "the tower" || str == "the miniature tower" || 
      str == "the red tower")
   {
      write("Turn <the miniature tower to face> what direction?\n");
      return "";
   }

   if (sscanf(str, "the miniature tower to face %s", str) != 1)
   {
      write("Turn the miniature tower to face what direction?\n");
      return "";
   }

   if(query_red_tower_locked())
   {
      write("The miniature tower is locked in place facing west, with " +
         "magical energies banking up in this room. It won't be long " +
         "before there will be a catastrophic explosion!\n");
      return "";
   }

   if(str == "east" || str == "north" || str == "south" ||
      str == "northeast" || str == "southeast" || str == "northwest" ||
      str == "southwest")
   {
      if(str == query_red_tower_direction())
      {
         write("The miniature tower is already facing that direction.\n");
         return "";
      }

      write("You turn the miniature tower to face the " +str+ ".\n");
      set_red_tower_direction(str);

      attempts = TP->query_prop(HEARTROOM_ATTEMPTS);
      TP->add_prop(HEARTROOM_ATTEMPTS, attempts + 1);
      return "";
   }

   if(str == "west")
   {
      if(str == query_red_tower_direction())
      {
         write("The miniature tower is already facing that direction.\n");
         return "";
      }

      write("You turn the miniature tower to face the " +str+ ". With " +
          "a 'click' it locks in place, and the room begins to hum as " +
          "magical energies begin to back up in this room. It won't be " +
          "long before there is a catastrophic explosion!\n");
      set_red_tower_locked(1);
      set_red_tower_direction(str);
      start_room_tells();
      TP->add_prop(HEARTROOM_ACTIVATED, 1);
      WOHS_MANAGER->add_wohs_test_props(TP, HEARTROOM_ACTIVATED, 1);
      WOHS_MANAGER->add_wohs_test_props(TP, HEARTROOM_ATTEMPTS, 
                                            attempts + 1);
      set_alarm(6.0, 0.0, &farewell_message(TP));
      return "";
   }

    write("Turn the miniature tower to face where?\n");
    return "";
}


/* 
 * Function name:        init
 * Description  :        add some actions to the player
 */
public void
init()
{
    ::init();
    add_action(turn_tower, "turn");

} /* init */


void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
 
    if (interactive(ob) && TP->query_prop(HEARTROOM_ACTIVATED))
       start_room_tells();
}
