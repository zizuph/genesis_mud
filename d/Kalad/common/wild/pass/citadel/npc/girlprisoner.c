/* By Korat
* Sept. 1996
* A prisoner placed in the citadel. It does nothing than moan.
*
*/
inherit "/d/Kalad/std/monster";
#include "/d/Kalad/defs.h"

void
create_monster()
{
   ::create_monster();
   set_name("citizen");
   add_name("prisoner");
   set_race_name("human");
   set_adj("weak");
   add_adj("hungry");
   set_long("No chains holds this prisoner locked down, "+
      "but this small haven in an alien world is all "+
      "that this human can be in. No outlaws dares for "+
      "some reason to enter it, leaving this poor wreck "+
      "to her fate of starving to death. From the rags "+
      "she wears, you gather that she must have been "+
      "an unfortunate passenger to one of the caravans "+
      "the outlaws raided.\n");
   set_stats(({10,10,15,50,50,10}));
   set_alignment(500);
   set_knight_prestige(-10);
   set_act_time(20);
   add_act("emote looks at you with hunger and fright "+
      "clearly visible in her eyes.");
   add_act("emote whimpers in pain.");
   add_act("emote moans weakly.");
   add_act("emote stares at you without focusing his eyes.");
   add_act("emote tries to speak but fails.");
   add_prop(NPC_M_NO_ACCEPT_GIVE,0);
}

public void
enter_inv(object what, object from)
{
   ::enter_inv(what, from);
   if(function_exists("create_food",what))
      {
      command("smile hungrily");
      command("emote throws down the food with quick "+
         "and greedy motions.");
      command("eat all");
      set_alarm(3.0,0.0,command("puke"));
      set_alarm(5.0,0.0,command("emote whimpers in pain."));
      set_alarm(6.0,0.0,command("emote moans."));
      return;
   }
   command("emote looks at the item with disinterested eyes.");
   set_alarm(3.0,0.0,command("drop all"));
   return;
}

void
init_living()
{
   ::init_living();
   command("emote crawls in fright closer to a large stone-block.");
}
