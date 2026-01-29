#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include <wa_types.h>
#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/goodlund/nethosak/local.h"

inherit AM_FILE

#define WEP1 DOBJ + "/d/Ansalon/goodlund/nethosak/docks/obj/weapon/battle_axe.c"
#define WEP2 DOBJ + "/d/Ansalon/goodlund/nethosak/docks/obj/weapon/sailor_axe.c"
#define ARM1 DOBJ + "/d/Ansalon/goodlund/nethosak/docks/obj/armour/belt.c"
#define ARM2 DOBJ + "/d/Ansalon/goodlund/nethosak/docks/obj/armour/kilt.c"

void create_krynn_monster()
{
   if(!IS_CLONE)
      return;

   set_name("daggoth");
   set_living_name("daggoth");
   set_title("the Navigator of Stormseeker");
   set_race_name("minotaur");
   set_adj("sharp-eyed");
   add_adj("young");
   set_gender("G_MALE");
   set_long("This young minotaur has learned the ways and procedures " +
      "of navigating a ship through the Blood Sea.  His small horns " +
      "and unscarred body mark him as young of age and, compared to " +
      "the other minotaurs on board, inexperienced in the ways of " +
      "combat.\n");

   set_stats(({100,80,100,120,120,120}));
   set_hp(query_max_hp());

   set_alignment(-100);
   set_knight_prestige(1);
   add_prop(CONT_I_HEIGHT, 230);
   add_prop(CONT_I_WEIGHT, 89700);
   set_skill(SS_WEP_AXE, 80);
   set_skill(SS_UNARM_COMBAT, 50);
   set_skill(SS_2H_COMBAT, 60);
   set_skill(SS_DEFENCE, 60);
   set_skill(SS_PARRY, 60);
   set_skill(SS_BLIND_COMBAT, 70);
   set_skill(SS_AWARENESS, 100);

   set_act_time(7);
   add_act("emote yawns.");
   add_act("shout Who let these stinky beasts on board?");
   add_act("emote peers out into the bay.");
   add_act("emote glances at a ship as it sails by.");
   add_act("emote sighs deeply.");

   trig_new("%w 'introduces' %s","react_to_intro");
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