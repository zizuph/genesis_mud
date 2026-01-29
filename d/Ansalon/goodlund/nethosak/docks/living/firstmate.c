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

void create_krynn_monster()
{
   if(!IS_CLONE)
      return;

   set_name("korhil");
   set_living_name("korhil");
   set_title("the Firstmate of Stormseeker");
   set_race_name("minotaur");
   set_adj("one-eyed");
   add_adj("cranky");
   set_gender("G_MALE");
   set_long("This cranky minotaur glares around the ship from it's one eye.  It " +
      "appears the other one was in a nasty accident and is now covered " +
      "by an eyepatch.  From the way he carries himself on the ship you " +
      "would guess he is a veteran to the ways of the seas, and wants " +
      "to make sure that everyone knows it.\n");

   set_stats(({120,120,120,60,60,140}));
   set_hp(query_max_hp());

   set_alignment(-100);
   set_knight_prestige(1);
   add_prop(CONT_I_HEIGHT, 260);
   add_prop(CONT_I_WEIGHT, 89700 + random(23000));
   set_skill(SS_WEP_AXE, 100);
   set_skill(SS_UNARM_COMBAT, 70);
   set_skill(SS_2H_COMBAT, 80);
   set_skill(SS_DEFENCE, 70);
   set_skill(SS_PARRY, 70);
   set_skill(SS_BLIND_COMBAT, 100);
   set_skill(SS_AWARENESS, 60);

   set_act_time(25);
   add_act("emote growls at you.");
   add_act("yawns.");
   add_act("emote looks over the ship making sure " +
      "everything is secured.");
   add_act("say The dragonarmy diplomats are lucky they " +
      "made it in one piece.  We were ready to feed " +
      "their corpses the sea, instead of listening to " +
      "their incessant whining and bitching for " +
      "another day.");

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
