inherit "/std/weapon";
#include "/sys/wa_types.h"
#include "/sys/formulas.h"
#include "/sys/macros.h"
#include "/sys/stdproperties.h"
#include <ss_types.h>
#include "/d/Rhovanion/defs.h"
static int counter=0;
string enemy_name;
mixed enemy = this_player()->query_enemy();
mixed pskill = this_player()->query_skill(SS_WEP_SWORD);
mixed eskill = enemy->query_skill(SS_DEFENCE);
mixed pdex = this_player()->query_stat(SS_DEX);
mixed edex = enemy->query_stat(SS_DEX);
void
create_weapon() {
   set_name("swords");
   set_short("pair of chain-linked, wyrm swords");
   set_pshort("pairs of chain-linked, wyrm swords");
   set_adj(({"chain-linked","wyrm"}));
   set_long("These swords, linked together by a strong, " +
      "steel chain, offer an effective fighting system. " +
      "The blades themselves are less blades then they " +
      "are impaling objects.  The blades are basically " +
      "twisted steel wyrms, sharp on certain edges, and " +
      "come to a very sharp point at their tip.  The " +
      "scales of the wyrm on the blades are each etched " +
      "around their edges with gold making their appearance " +
      "spectacular!  As for the chain linking the two " +
      "weapons together by their pommels, it appears to " +
      "be able to strangle a Foe quite well if it were " +
      "applied correctly.\n");
   set_hit(31);
   set_pen(26);
   set_wt(W_SWORD);
   set_dt(W_IMPALE);
   set_hands(W_BOTH);
}
string
query_recover() {
   return MASTER + ":" + query_wep_recover();
}
void
init_recover(string arg) {
   init_wep_recover(arg);
}
void
init()
{
   ::init();
   add_action("try_strangle","strangle");
}
try_strangle(string str) {
   enemy = this_player()->query_enemy();
   enemy_name = enemy->query_name();
   notify_fail("Strangle who?  You're monkey?\n");
   if (!str)
      return 0;
   if (str != "foe")
      return 0;
   if (this_player()->query_enemy())
      {
      enemy = this_player()->query_enemy();
      enemy_name = enemy->query_name();
      write("You try to get yourself into position to " +
         "strangle " + enemy_name + ".\n");
      say(QCTNAME(TP) + " is taking a strange position.\n");
      set_alarm(5.0,0.0,"part_strangle");
      return 1;
   }
   write("What enemy?\n");
   say(QCTNAME(TP) + " wraps his chain around his monkey.\n");
   return 1;
}
part_strangle() {
   if (counter > 0)
      {
      write("You'll have to get your chains untangled first.\n");
      return 1;
   }
   if ((pskill + pdex) > (eskill + edex +(ONE_OF_LIST(({ -10, -3,
                     -2,-1,0,0,0,0,0,0,0,0,0,0,0,0,1,2,3,10 })))))
   {
      write("You leap at " + enemy + " wrapping your chains " +
         "around " + enemy + "'s neck!\n");
      say(QCTNAME(TP) + " leaps at " + enemy + " wrapping " +
         QCTNAME(this_player())+"'s chains around " +
         enemy + "'s neck!\n");
      enemy->write(QCTNAME(this_player()) + " leaps at you with " +
         this_player()+"'s chains and wraps them around your neck!\n");
      enemy->heal_hp(-10);
      counter++;
      set_alarm(3.0,0.0,"part_strangle2");
      return 1;
   }
   write("You leap at " + enemy + " only to fall flat on " +
      "your face.\n");
   say(QCTNAME(this_player()) + " leaps at " + enemy + " only to " +
      "fall humiliatingly to the ground.\n");
   counter++;
   set_alarm(30.0,0.0,"miss_strangle");
   return 1;
}
miss_strangle() {
   TP->write("You get your chain untangled.\n");
   counter--;
   return 1;
}
part_strangle2() {
   write("You continue to strangle " + enemy+".\n");
   say(QCTNAME(this_player()) + " continues to strangle " + enemy+".\n");
   enemy->write("You're choking!\n");
   enemy->command("cough");
   enemy->heal_hp(-15);
   set_alarm(5.0,0.0,"part_strangle3");
   return 1;
}
part_strangle3() {
   TP->write("You continue to strangle " + enemy+".\n");
   say(QCTNAME(this_player()) + " continues to strangle " + enemy+".\n");
   enemy->write("You're choking to death!\n");
   enemy->command("cough");
   enemy->heal_hp(-20);
   set_alarm(9.0,0.0,"part_strangle4");
   return 1;
}
part_strangle4() {
   write("You continue to strangle " + enemy+".\n");
   say(QCTNAME(this_player()) + " continues to strangle " + enemy+".\n");
   enemy->write("Your face is turning blue!\n");
   enemy->command("choke");
   enemy->heal_hp(-25);
   set_alarm(5.0,0.0,"part_strangle5");
   return 1;
}
part_strangle5() {
   write("You strangle the hell out of " + enemy+"!\n");
   say(QCTNAME(this_player()) + " strangles the hell out of " + enemy+"!\n");
   enemy->write("You think you're going to die!\n");
   enemy->command("choke");
   enemy->heal_hp(-30);
   set_alarm(3.0,0.0,"part_strangle6");
   return 1;
}
part_strangle6() {
   write(enemy + " breaks out of your chains.\n");
   say(QCTNAME(this_player()) + " breaks free of the chains.\n");
   enemy->write("You gasp as you take in much needed air!\n");
   enemy->command("cough");
   enemy->command("cough");
   counter--;
   return 1;
}
