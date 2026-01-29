#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>
#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include <wa_types.h>

#define WEP1 WEP + "iron_axe"
#define ARM1 ARMOUR + "chainmail"
#define ARM2 ARMOUR + "leggings"
#define ARM3 ARMOUR + "i_gauntlets"
#define ARM6 ARMOUR + "i_boots"
#define ARM4 ARMOUR + "shield"
#define ARM5 ARMOUR + "horned_helmet"

inherit AM_FILE
inherit AUTO_TEAM

string *gAdj1 = ({"grumpy","gruff","scarred","jovial",
  "stout","old","young","gnarled"});
string *gAdj2 = ({"black-bearded","fork-bearded","red-bearded",
  "brown-bearded","long-bearded","grey-bearded"});

#ifndef ONE_OF
#define ONE_OF(x) (x[random(sizeof(x))])
#endif

void arm_me();

void
create_krynn_monster()
{
    if(!IS_CLONE)
	return;

    set_pick_up_team(({"dwarf"}));
    set_max_team_size_auto_join(3);
    set_race_name("dwarf");
    set_name("clan_guard");
    set_adj(ONE_OF(gAdj1));
    add_adj(ONE_OF(gAdj2));
    set_gender("G_MALE");
    set_long("This is a short, nuggety hill dwarf. What " +
      "part of his face you see through his beard is darkly " +
      "tanned and weathered from exposure to the elements, and he " +
      "looks like he is prepared for anything. He does not " +
      "look like the type of person to shy away from a fight either.\n");

    set_stats(({120,90,130,89,89,110}));
    set_hp(query_max_hp());
    set_skill(SS_WEP_AXE, 100);
    set_skill(SS_DEFENCE, 100);
    set_skill(SS_PARRY, 100);
    set_skill(SS_AWARENESS, 80);
    set_skill(SS_BLIND_COMBAT, 100);

    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(LIVE_I_SEE_DARK, 1);
    add_prop(OBJ_I_RES_MAGIC, 50);
    add_prop(OBJ_I_RES_POISON, 70);

    set_alignment(100);
    set_knight_prestige(-1);

    set_default_answer("The dwarf looks at you funnily, as if " +
      "you should already know the answer to that.\n");

    set_act_time(5);
    add_act("emote stretches his gnarled hands before him.");
    add_act("emote curses the Mountain dwarves to eternal rust " +
      "and corrosion.");
    add_act("emote grumbles about the weather.");
    add_act("emote strokes his greying beard lovingly.");

    set_cact_time(0);
    add_cact("assist");
    add_cact("assist dwarf");
    add_cact("emote roars 'Great Reorx!' in astonishment!");
    add_cact("say curse yas to eternal rust and corrosion!");
    add_cact("emote roars: You doorknob! What ye think yur do'en?");

    if (IS_CLONE)
        set_alarm(1.0, 0.0, &arm_me());

}

void
arm_me()
{
    seteuid(getuid(TO));
    clone_object(WEP1)->move(TO,1);
    clone_object(ARM1)->move(TO);
    clone_object(ARM2)->move(TO,1);
    clone_object(ARM3)->move(TO,1);
    clone_object(ARM4)->move(TO,1);
    clone_object(ARM5)->move(TO,1);
    clone_object(ARM6)->move(TO,1);
    command("wield all");
    command("wear all");
}

