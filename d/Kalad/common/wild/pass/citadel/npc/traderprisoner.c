/* By Korat
 * Sept. 1996
 * A prisoner placed in the citadel
 *
*/
inherit "/d/Kalad/std/monster";
#include "/d/Kalad/defs.h"

void
create_monster()
{
   ::create_monster();
   set_name("trader");
   add_name("prisoner");
   set_race_name("human");
   set_adj("thin");
   add_adj("suffering");
   set_long("Shackled up to the wall, this poor human seems "+
      "to have suffered much pain from the hands of his capturers. "+
      "Judging from the rags he wears, he must once have been a "+
      "trader, belonging to one of Kabals trading companies.\n");
   set_stats(({20,10,15,50,50,40}));
   set_alignment(0);
   set_knight_prestige(-10);
   set_act_time(20);
   add_act("emote tries to stretch out his hand, but the weight "+
      "of the chain stoppes his movements.");
   add_act("emote whimpers in pain.");
   add_act("emote moans weakly.");
   add_act("emote stares at you without focusing his eyes.");
   add_act("emote tries to speak but fails.");
   add_prop(NPC_M_NO_ACCEPT_GIVE,0);
}
