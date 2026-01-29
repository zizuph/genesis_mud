/* Spirit sword found on the wraith in Telberin castle. It is magical
 * and has no special properties.
 * 
 * 17/4/94 added the emotes 'indicate' and 'cover' to make the sword
 * more interesting and better. Mylos
 *
 */
inherit "/std/weapon";

#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>
#include "default.h"
#include <cmdparse.h>   /* For FIND_STR_IN_OBJECT */

void summon_mist(mixed args);

void
create_weapon()
{
   set_name("sword");
   set_short("spirit sword");
   set_long(break_string("This sword is old even for swords, the gleam "+
         "on it's blade just showing traces of ancient runes.\n", 76));
   set_adj("spirit");
   
   set_default_weapon(42, 40, W_SWORD, W_SLASH | W_IMPALE,  
      W_ANYH,  0);
   add_prop(OBJ_I_WEIGHT, 2390); 
   add_prop(OBJ_I_VOLUME,  790); 
   add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
   add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(42, 40) + random(114) + 27);

   add_prop(MAGIC_AM_MAGIC, ({ 30, "enchantment" }));
   add_prop(MAGIC_AM_ID_INFO, ({ ({ 20,40,60,80,100 }), break_string("This "+
        "sword was once carried by the worst evil of all, a wraith. It's "+
        "spirit is still sligtly imbued in the blade which you can feel "+
        "emanating into the hilt and into you.\n", 76)}));
   add_prop(OBJ_S_WIZINFO, break_string("This spirit sword is found on "+
        "the wraiths in the castle of Telberin. They are powerful becuase "+
        "of the nature of the wriaths that carry them, pouring their "+
        "power into them over the years (/d/Emerald/room/keep/3k5).\n", 76));
}

void
init()
{
   ::init();
   add_action("do_trace","trace");
   add_action("do_cover","cover");
   add_action("do_indicate","indicate");
}

int
do_trace(string str)
{
   NF("Trace what?\n");
   if(!strlen(str))
        return 0;

   NF("Trace what?\n");
   if(str != "runes")
        return 0;

   if(TP->resolve_task(TASK_SIMPLE, ({ TS_INT, SS_LANGUAGE })) > 0) {
      write("You easily decipher the runes out and you may do the following:-\n"+
        "\tcover <name>\n\tindicate <name>\n");
      say(QCTNAME(TP)+" peers closely at "+POS(TP)+" spirit sword.\n", TP);
      return 1;
   }
   NF("It's no good, you can't figure the runes out.\n");
   return 0;
}

int
do_indicate(string str)
{
   object *targets, target;
   int i;

   if(!strlen(str)) {
      NF("Indicate whom?\n");
      return 0;
   }

   targets = FIND_STR_IN_OBJECT(str, ENV(TP));

   if(!sizeof(targets)) {
      NF("Indicate whom? The air?\n");
      return 0;
   }
   if(sizeof(targets) > 1) {
      NF("Could you be more specific?\n");
      return 0;
   }

   target = targets[0];
 
   if(!CAN_SEE(TP, targets[0])) {
      NF("It's too dark in here.\n");
      return 0;
   }

   if(TO->query_wielded()) {
      write("You extend your arm and the spirit sword and indicate "+
        str+".\n");
      target->catch_msg(QCTNAME(TP)+" extends "+POS(TP)+" arm and "+POS(TP)+
        " spirit sword and points at you.\n");
      tell_room(ENV(TP), QCTNAME(TP)+" extends "+POS(TP)+" arm and "+POS(TP)+
        " spirit sword and points at "+str+".\n", ({target, TP}));
      return 1;
   }
   NF("You aren't wielding the sword.\n");
   return 0;
}

int
do_cover(string str)
{
   mixed *calls = get_all_alarms();
   object *targets, target;
   int i;

   if(!strlen(str)) {
      NF("Cover whom?\n");
      return 0;
   }

   targets = FIND_STR_IN_OBJECT(str, ENV(TP));

   if(!sizeof(targets)) {
      NF("That player is not here at the moment.\n");
      return 0;
   }

   if (sizeof(targets) > 1) {
      NF("Could you be more specific?\n");
      return 0;
   }

   target = targets[0];
 
   if(!CAN_SEE(TP, targets[0])) {
      NF("It's dark in here!\n");
      return 0;
   }

   if(TO->query_wielded()) {
     for(i=0; i<sizeof(calls); ++i)
       if(calls[i][1] == "summon_mist") {
         NF("You are already performing 'cover'.\n");
         return 0;
     }
     write("You summon the power of the sword.\n");
     set_alarm(2.0, 0.0, "summon_mist", ({ TP, target }));
     say(QCTNAME(TP)+" grips tightly onto "+POS(TP)+" spirit sword.\n", TP);
     return 1;
   }
   NF("You aren't wielding the spirit sword.\n");
   return 0;
}

void
summon_mist(mixed args)
{
   object player, target;
   string colour;
   
   if (sizeof(args) != 2)
      return;
   player = args[0];
   target = args[1];

   if(player->query_alignment() >= 0)
        colour = "white";
   else
        colour = "green";

   target->catch_msg("A strange "+colour+" mist seems to spring from "+
        "nowhere and swirl around you.\n");
   write(CAP(colour)+" mist swirls around "+target+", and you nearly "+
        "lose sight of "+target->query_objective()+".\n");
   say("A "+colour+" mist swirls around "+QTNAME(target)+
        " and you nearly lose sight of "+target->query_objective()+".\n",
        ({ player, target }));
   return;
}
