inherit "/std/monster";
#include <stdproperties.h>
#include <ss_types.h>
#include "/d/Rhovanion/defs.h"
#include <money.h>
static int chained=1;
void
create_monster() {
   int i;
   set_name(ONE_OF_LIST(({"rufus","melqor","rayma",
               "phuselaatamus","thomas","rodaando","helmsic" })));
   set_race_name(ONE_OF_LIST(({"human","elf","dwarf",
               "hobbit","gnome","half-elf" })));
   set_adj(ONE_OF_LIST(({"hearty","barrel-chested",
               "thin","lanky","old","young","bony","strapping",
               "cantankerous","friendly","helpful" })));
   set_adj(ONE_OF_LIST(({ "bald","hairy","one-eyed",
               "tortured","maimed","one-legged","blue-eyed",
               "long-haired","scraggly-haired" })));
   set_long("@@my_desc");
   set_whimpy(45);
   set_gender(0);
   set_aggressive(0);
   set_alignment(250);
   set_stats(({ 35, 60, 25, 50, 50, 30 }));
   set_hp(100);
   set_skill(SS_DEFENCE, 25);
   set_skill(SS_WEP_SWORD, 35);
   set_skill(SS_WEP_CLUB, 35);
   set_skill(SS_WEP_POLEARM, 35);
   set_skill(SS_WEP_AXE, 40);
   set_skill(SS_WEP_KNIFE, 37);
   set_act_time(1);
   add_act("say Please help me!");
   add_act("say By the gods, save me!");
   add_act("say If you rescue me, I will serve you " +
      "till the day I die.");
}
my_desc() {
   if (chained==1)
      return "This fellow looks like he's been tortured " +
   "extensively.  He has been shackled to the east wall.\n";
   else
      return "This fellow looks like he's been tortured " +
   "extensively.\n";
   return 1;
}
public void
run_away() {
   set_alarm(0.0,0.0,"run_away2");
}
run_away2() {
   if (chained==1)
      {
      command("emote frantically struggles to free himself " +
         "from his chains.");
      return 1;
   }
   command("say I shall never flee your side!");
   return 1;
}
