/* Creative rights reserved to Mecien(Jeff Babcock) and team. */
/* Mystic Chariot */
/* Sorgum 940909 */

inherit "/std/object";

#include <ss_types.h>
#include <macros.h>
#include <wa_types.h>
#include <stdproperties.h>
#include "/d/Terel/mecien/valley/guild/mystic_defs.h"

#define BS(xx)    break_string(xx, 72)
#define TO        this_object()
#define TP        this_player()
#define NF(xx)    notify_fail(xx)
#define ETO       environment(TO)
#define EN environment

#define SPELLDIR "/d/Terel/mecien/valley/guild/spells/"
int duration = 0;
int iter = 0;
int d_iter = 0;
int start_id;
int depart_id = 0;
object chariot_room;
object cast_room;
object dest_room;

init()
{
   ::init();
   add_action("do_enter", "enter");
}

int
do_enter(string str)
{
   if (!strlen(str) || ((str != "chariot") )) {
      NF("Enter what?\n");
      return 0;
   }
   
   if (!chariot_room) {
      NF("That is not possible at the moment.\n");
      return 0;
   }
   
   if (!TP->query_prop("blessed"))  {
      NF("Mystic forces prevent you from entering.\n");
      return 0;
   }
   
   TP->move_living("into the mystic chariot", chariot_room);
   return 1;
}

create_object()
{
   set_name("mystic_chariot");
   add_name("chariot");
   set_short("mystic chariot");
  set_long(
    "An altogether strange sight, this vehicle appears to be something from " +
"some other world. More of a coach than a chariot, but still, resting " +
"upon two large silvery wheels, it is an ancient black covered chariot of some kind. " +
  "Two black harnesses seem to float out in front of it, as if holding " +
"something unseen before the chariot. A small perch juts from the " +
"front of the chariot, where a lonely gray figure sits."
+"\n");

add_item("harness", "It is a black harness, perhaps made of leather, rising out before the chariot, suspended in the air.\n");
   add_item("harnesses", "They are black harnesses, perhaps made of leather. They are attached to the forward of the chariot and stand suspended in the air, as if holding something unseen.\n");
   add_cmd_item("harness", "get", "You are knocked back by some mysterious force!\n");
   add_cmd_item(({"driver", "figure", "spirit"}), "kill", "@@kill_driver");
  add_item(({"figure", "driver", "spirit"}), "It is a cowled and robed figure, all in gray. It seems to be the driver of the chariot.\n");
   add_prop(OBJ_I_WEIGHT,1000);
   add_prop(OBJ_I_VOLUME,10000);
   add_prop(OBJ_I_VALUE,0);
   add_prop(OBJ_M_NO_GET,"You are knocked back by some unseen power.\n");
   add_prop(MAGIC_AM_MAGIC,({90,"summoning"}));
}

kill_driver(){
   TP->heal_hp(-1000);
   TP->catch_msg("The cowled figure turns to you, points a finger at you and your heart is gripped with an intense pain! You fall backwards.\n");
  tell_room(EN(TP), QCTNAME(TP) + " makes an offensive move at the cowled figgure at the front of the chariot, "
+ "who turns to " +QTNAME(TP) + " and points a finger at " + TP->query_objective() + 
", seemingly striking " + TP->query_objective() + " down with pain!\n", TP);
  return 1;
}

void
do_depart()
{
   depart_id = set_alarm(3.0, 4.0, "depart_seq");
}

set_chariot_room(object room)
{
   chariot_room = room;
}

set_cast_room(object room)
{
   cast_room = room;
}

set_dest_room(object room)
{
   dest_room = room;
}

start_chariot()
{
   start_id = set_alarm(1.0, 4.0, "start_seq");
}

chariot_at_destination()
{
   int i;
   object *pl;
   
   pl = all_inventory(chariot_room);
   for (i = 0; i < sizeof(pl); i++) {
      if (interactive(pl[i])) {
         tell_room(dest_room, QCTNAME(pl[i]) +
  " comes out of the ancient chariot.\n", pl[i]);
         pl[i]->move_living("M", dest_room);
        }
   }
   remove_alarm(start_id);
   start_id = 0;
   tell_room(dest_room, "The ancient chariot departs into the sky.\n");
   remove_object();
}

void
start_seq()
{
   switch(iter) {
      case 0:
      tell_room(cast_room, "You sense a change in the environment.\n");
      break;
      case 1:
      tell_room(cast_room, "The winds begin to pick up.\n");
      break;
      case 2:
      tell_room(cast_room, "Off in the distance you see a chariot " +
         "in the sky.\n");
      break;
      case 3:
      case 4:
      tell_room(cast_room, "The chariot draws closer.\n");
      break;
      case 5:
      tell_room(cast_room, "A glorious ancient chariot decsends " +
         "from the sky!\n");
      TO->move(cast_room);
      break;
      default:
      remove_alarm(start_id);
      start_id = 0;
   }
   iter++;
}

void
depart_seq()
{
  object storm;
  storm = present("mystic_storm", EN(TO));
   switch(d_iter) {
      case 0:
      tell_room(chariot_room, "The chariot prepares for departure.\n");
      tell_room(dest_room, "You sense a change in the environment.\n");
      break;
      case 1:
      tell_room(chariot_room, "The winds begin to pick up.\n");
      tell_room(dest_room, "The winds begin to pick up.\n");
      break;
      case 2:
      tell_room(cast_room, "The winds begin to pick up again.\n");
      tell_room(chariot_room, "The chariot departs.\n");
      TO->move("/d/Terel/mecien/hill");
      tell_room(dest_room, "Off in the distance you see a chariot " +
         "in the sky.\n");
   if(storm) storm->move(dest_room);
      break;
      case 3:
      
  tell_room(dest_room, "Streaks of lightning erupt from the darkened sky!.\n");
      case 4:
      tell_room(cast_room, "The winds get stronger.\n");
      tell_room(dest_room, "The chariot draws closer.\n");
      tell_room(chariot_room, "The chariot draws closer to the " +
         "destination.\n");
      break;
      case 5:
      tell_room(chariot_room, "The chariot has arrived at the " +
         "destination.\n");
      tell_room(dest_room, "A glorious ancient chariot decsends " +
         "from the sky!\n");
      TO->move(dest_room);
      TO->chariot_at_destination();
      break;
  default:
   remove_alarm(depart_id);
   depart_id = 0;
   }
   d_iter++;
}

