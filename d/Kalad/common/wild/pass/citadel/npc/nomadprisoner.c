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
   set_name("nomad");
   add_name("prisoner");
   set_race_name("human");
   set_adj("weak");
   add_adj("pale");
   set_long("The chains that holds this prisoner locked down, "+
      "seems to have no function except to remind this prisoner "+
      "of his fate. The strenght has left this human a long time "+
      "ago. His originally dark, sunburned skin, enhances "+
      "the sickly pale tone it has now. Studying the rags he wears, "+
      "you decide that he must once have been a nomad merchant.\n");
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
