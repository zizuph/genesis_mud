#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include <wa_types.h>
#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/goodlund/nethosak/local.h"

inherit AM_FILE

#define WEP1 DOBJ + "weapon/mace.c"
#define ARM1 DOBJ + "armour/belt.c"
#define ARM2 DOBJ + "armour/kilt.c"

void create_krynn_monster()
{
   if(!IS_CLONE)
      return;

   set_name("ganth");
   set_living_name("ganth");
   set_title("the Captain of Stormseeker");
   set_race_name("minotaur");
   set_adj("scarred");
   add_adj("old");
   set_gender("G_MALE");
   set_long("The old age of this minotaur can be seen in the streaks " +
      "of grey mingled in with his dark coat of fur.  His horns " +
      "are close to two feet long and curl up making him nine feet " +
      "tall from horn to hoove.  The old scars that cover his " +
      "body and the nicks and dings on his horns are testaments to " +
      "the numerous fights this old minotaur has participated in.\n");

   set_stats(({160,140,160,100,100,170}));
   set_hp(query_max_hp());

   set_alignment(0);
   set_knight_prestige(0);
   add_prop(CONT_I_HEIGHT, 300);
   add_prop(CONT_I_WEIGHT, 117000);
   set_skill(SS_WEP_CLUB, 100);
   set_skill(SS_UNARM_COMBAT, 80);
   set_skill(SS_DEFENCE, 80);
   set_skill(SS_PARRY, 80);
   set_skill(SS_BLIND_COMBAT, 100);
   set_skill(SS_AWARENESS, 80);

   set_act_time(7);
   add_act("say Leave this ship while you still have the " +
      "legs to do it with.");
   add_act("emote growls at you.");
   add_act("say Bah! This waiting is for gully dwarves, we are " +
      "warriors.");
   add_act("say The dragonarmies have no honor, it amazes me the " +
      "council would stoop so low as to join with the honorless " +
      "dogs.");
   add_act("emote yawns.");
   add_act("say What do they think we are?  A bunch of maids? I " +
      "say we conquer them as we will the rest of Ansalon.");
   add_act("shout Who let these stinky beasts on board my ship?");

   trig_new("%w 'introduces' %s","react_to_intro");
}

void arm_me()
{
   seteuid(getuid(TO));
   clone_object(WEP1)->move(TO, 1);
   command("wield all");
   clone_object(ARM1)->move(TO, 1);
   clone_object(ARM2)->move(TO, 1);
   command("wear all");
}

void react_to_intro(string who,string garbage)
{
    set_alarm(2.0,0.0,"return_intro",who);
}

void return_intro(string who)
{
    who = L(who);
    if (P(who,E(TO)))
    {
        command("introduce myself");
    }
}       