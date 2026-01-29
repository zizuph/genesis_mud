#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include <money.h>
#include <wa_types.h>
#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/goodlund/nethosak/local.h"

inherit AM_FILE

#define WEP1 DOBJ + "weapon/battle_axe.c"
#define WEP2 DOBJ + "weapon/sailor_axe.c"
#define ARM1 DOBJ + "armour/belt.c"
#define ARM2 DOBJ + "armour/kilt.c"

int gender;

string *gAdj1 = ({"young","tall","old","cranky","grim",
   "one-eyed","burly","muscular","sullen","excited","short",
   "fat","dirty","scarred"});

string *gAdj2 = ({"blond-furred","dark-furred","red-furred",
   "long-furred","short-furred","long-horned","short-horned",
   "one-horned","white-furred","grey-furred"});

#ifndef ONE_OF
#define ONE_OF(x) (x[random(sizeof(x))])
#endif

void create_krynn_monster()
{
   if(!IS_CLONE)
      return;

   if (random(2) == 1)
      gender = 1;
   else
      gender = 0;

   set_name("minotaur");
   if (gender == 1)
      set_adj("male");
   else
      set_adj("female");
   set_adj(ONE_OF(gAdj1));
   set_adj(ONE_OF(gAdj2));
   set_short(implode(query_adjs()," ") + " minotaur");
   set_race_name("minotaur");
   if (gender == 1)
      set_gender("G_MALE");
   else
      set_gender(1);
   set_long("This is one of the many minotaurs who make " +
      "up the crew aboard this sailing ship.\n");

   set_stats(({100 + random(20),
      80 + random(40),
      100 + random(20),
      50 + random(10), 50 + random(10), 100 + random(40)}));
   set_hp(query_max_hp());

   set_alignment(-100);
   set_knight_prestige(1);
   add_prop(CONT_I_HEIGHT, 230 + random(30));
   add_prop(CONT_I_WEIGHT, 89700 + random(23000));
   set_skill(SS_WEP_AXE, 80 + random(20));
   set_skill(SS_UNARM_COMBAT, 50 + random(20));
   set_skill(SS_2H_COMBAT, 60 + random(20));
   set_skill(SS_DEFENCE, 60 + random(10));
   set_skill(SS_PARRY, 60 + random(10));
   set_skill(SS_BLIND_COMBAT, 70 + random(30));
   set_skill(SS_AWARENESS, 30 + random(30));
   add_prop(LIVE_I_NEVERKNOWN, 1);

   set_act_time(25);
   add_act("say Leave this ship while you still have the " +
      "legs to do it with.");
   add_act("emote growls at you.");
   add_act("yawns.");
   add_act("emote looks over the ship making sure " +
      "everything is secured.");
   add_act("shout Who let these stinky beasts on board?");
   add_act("say Where is that brainless gully dwarf, look " +
      "at this mess.");
   add_act("say The captain has been raising a fit " +
      "ever since we docked.  He is as tired of waiting " +
      "as the rest of us.");
   add_act("say The dragonarmy diplomats are lucky they " +
      "made it in one piece.  We were ready to feed " +
      "their corpses the sea, instead of listening to " +
      "their incessant whining and bitching for " +
      "another day.);
   add_act("say If negotians are successful we will have " +
      "complete control over the Blood Sea.  Just think " +
      "of where we can go from there.");

}

void arm_me()
{
   seteuid(getuid(TO));
   clone_object(WEP1)->move(TO, 1);
   clone_object(WEP2)->move(TO, 1);
   command("wield all");
   clone_object(ARM1)->move(TO, 1);
   clone_object(ARM2)->move(TO, 1);
   command("wear all");
}
