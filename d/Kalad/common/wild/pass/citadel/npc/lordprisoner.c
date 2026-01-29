/* By Korat
 * Sept. 1996
 * A prisoner placed in the citadel. This prisoner is a part
 * of a quest. Goliath wants a sword as ransom for this npc.
 * The sword is the High Lords - a neat but not magical one.
 * If the quest is done, Goliath with friends will attack
 * the city, by walking through the sewers. His goal is
 * his old employer - a merchant in kabal.
 * This npc does not really do anything except ask for help.
 * It will ofcourse not be removed when the ransom is given out.
 * Goliath is not that kind of a nice and trustworthy guy.
 * Goliath will kill him before going to the city.
 * (sends some of his minions to do it)
*/
inherit "/d/Kalad/std/monster";
#include "/d/Kalad/defs.h"

void
create_monster()
{
   ::create_monster();
   set_name("lord");
   add_name("prisoner");
   set_race_name("human");
   set_adj("skinny");
   add_adj("suffering");
   set_long("Shackled up to the wall, this suffering human seems "+
      "to have been inflicted much pain from the hands of his capturers. "+
      "Judging from the rags he wears, he must once have been a "+
      "a man of high position, belonging maybe to the upper strata of "+
      "Kabal's society.\n");
   set_stats(({20,10,15,50,50,40}));
   set_alignment(400);
   set_knight_prestige(-10);
   set_act_time(20);
   add_act("emote tries to stretch out his hand, but the weight "+
      "of the chain stoppes his movements.");
   add_act("emote whimpers in pain.");
   add_act("emote moans weakly.");
   add_act("emote stares at you without focusing his eyes.");
   add_act("emote tries to speak but fails.");
   add_act("emote whimpers: Plea .. help mm ...e");
   add_speak("... hee lp ... mm ...\n");
   add_prop(NPC_M_NO_ACCEPT_GIVE,0);
}
