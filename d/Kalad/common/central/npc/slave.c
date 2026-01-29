/*
Different humans in the Citadel.
   MADE BY: Korat
DATE: Feb 14 1995
*/

inherit "/d/Kalad/std/monster";
#include "/d/Kalad/defs.h"
#include "/sys/macros.h"
#include "/sys/ss_types.h"
#include "/sys/money.h"
#include <stdproperties.h>

void
create_monster()
{
   ::create_monster();
   switch (random(4))
   {
      case 0: set_race_name("dwarf"); break;
      case 1: set_race_name("goblin"); break;
      case 2: set_race_name("hobbit"); break;
      case 3: set_race_name("gnome"); break;
      default: break;
   }
   switch(random(16))
   {
      case 0: set_adj("bored"); break;
      case 1: set_adj("hungry"); break;
      case 2: set_adj("tired"); break;
      case 3: set_adj("exhausted"); break;
      case 4: set_adj("thin"); break;
      case 5: set_adj("yawning"); break;
      case 6: set_adj("devastated"); break;
      case 7: set_adj("quiet"); break;
      case 8: set_adj("muscleous"); break;
      case 9: set_adj("rugged"); break;
      case 10: set_adj("weary"); break;
      case 11: set_adj("skinny"); break;
      case 12: set_adj("lanky"); break;
      case 13: set_adj("scrawny"); break;
      case 14: set_adj("weak"); break;
      case 15: set_adj("feeble"); break;
      default: break;
   }
   set_name("slave");
   set_alignment(100);
   set_knight_prestige(-1);
   set_long("This is a slave used for forced labour. Without these "+
      "creatures, Kabal wouldn't have become such a beautiful "+
      "city; The fundamentals of this city is based on the lives and deaths "+
      "of them.\n");
   set_stats(({20,35,25,38,30,10}));
   set_skill(SS_UNARM_COMBAT, 30);
   set_skill(SS_WEP_CLUB, 40);
   set_skill(SS_DEFENCE, 30);
   set_skill(SS_PARRY,10);
   set_act_time(3);
   add_act("emote hits some rocks with his sledgehammer.");
   add_act("emote chisels on a stone.");
   add_act("emote sharpens his chisel.");
   add_act("emote lifts a heavy stone, but looses the grip and drops it.");
   add_act("emote yanks on his chains to get himself towards a puddle. He drinks.");
   add_act("emote shovels some sand with slow motions.");
   add_act("emote stares at the hot sun with an empty look.");
   add_act("emote digs.");
   add_act("emote collapses.");
   add_act("emote wipes the sweat from his brow with the left hand.");
   add_act("emote pushes a stone away.");
   add_act("emote hammers on a pole, pushing it into the ground.");
   add_act("emote hits a rock with a sledge, hard.");
   add_prop(NPC_M_NO_ACCEPT_GIVE,1);
}
void
arm_me()
{
   object arm, wep;
   seteuid(getuid(TO));
   arm = clone_object("/d/Kalad/common/central/arm/cit_human_sandal");
   arm -> move(TO);
   command("wear all");
   if (random(2)==0)
      {
      wep = clone_object("/d/Kalad/common/central/wep/slave_tool");
      wep -> move(TO);
      command("wield all");
   }
}   

void
help_friend(object ob)
{
   if (ob && !query_attack() && present(ob, environment()))
      {
      switch (random(5))
      {
         case 0: command("gasp"); break;
         case 1: command("emote keeps on working."); break;
         case 2: command("emote stops working in astonishment."); break;
         default: break;
       }
   }
}
