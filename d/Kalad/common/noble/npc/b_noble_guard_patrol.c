/* 
 * /d/Kalad/common/noble/npc/b_noble_guard_patrol.c
 * Purpose    : This is a brutal guard that wanders the streets of the noble district, looking for trouble
 * Located    : /d/Kalad/common/noble/
 * Created By : Sarr ??.??.96
 * Modified By: Toby 970725,
 *              Fysix, 02-98, recoded
 */ 

inherit "/d/Kalad/std/monster";
inherit "/d/Kalad/lib/special";

#include "default.h"

void
create_kalad_monster()
{
    set_name("guard");
    set_adj("brutal");
    add_adj("noble-district");
    set_race_name("human");
    set_short("brutal noble-district guard");
    set_long("This is a high-priced elite guard hired by the various "+
      "nobles of this district to keep the place clean and crime-free. "+
      "The nobles hire only the best, and you can be sure this one "+
      "knows how to do his job and do it well. This one looks like "+
      "he enjoys pounding the dirt out of trouble makers. His "+
      "cold eyes stare at you without expression, but his mouth "+
      "is shaped into a slight, twisted smile of cruelty...almost "+
      "inviting you to cause trouble.\n");

    set_alignment(-10);
    set_knight_prestige(-1);

    add_speak("Things are pretty quiet now in the Noble district.\n");

    set_stats(({140,150,140,100,100,120}));

    set_skill(SS_WEP_SWORD,120);
    set_skill(SS_PARRY,120);
    set_skill(SS_DEFENSE,100);
    set_skill(SS_WEP_POLEARM,120);
    set_skill(SS_WEP_CLUB,120);
    set_skill(SS_AWARENESS,70);
    set_skill(SS_2H_COMBAT,100);
    set_skill(SS_BLIND_COMBAT,100);

    set_random_move(1);
    set_act_time(4);
    add_act("emote adjusts his armour.");
    add_act("emote kicks at you with his foot, saying: Go on!");
    add_act("say Watch yourself, punk, or I'll mess you up.");
    add_act("spit");
    add_act("grin sadistic");
    set_cact_time(4);
    add_cact("shout Now you die, punk!");
    add_cact("shout I'll throw your head into the gutters where the dogs "+
      "can eat it!");
    add_cact("say I'm going to break every bone in your body, one "+
      "by one....");
    add_act("say I'll rip out your skull and use it to clean my "+
      "horse's dung!");
    add_cact("say You've asked for it now, pea-brain!");

    add_prop(LIVE_I_NEVERKNOWN,1);

    add_equipment(({
	NOBLE + "wep/" + ({"great_halberd",
	  "two-handed_longsword"})[random(2)],
	NOBLE + "arm/fs_chainmail",
	NOBLE + "arm/fs_bracers",
	NOBLE + "arm/fs_helm",
	NOBLE + "arm/fs_greaves",
	NOBLE + "arm/fw_cloak"
      }));

    // Configure our special attack
    set_default_special(25, W_BLUDGEON, 100, 300, A_BODY);
}

void
attacked_by(object enemy)
{
    command("grin sad");
    command("say You wanna play, "+enemy->query_name()+
      "? Let's play...");
}

// Execute a special attack only if we have a weapon
int special_attack(object enemy)
{
    // This special requires having a weapon
    if (!sizeof(query_weapon(-1)))
	return 0;

    return ::special_attack(enemy);
}

// Aim for head or body randomly, body with 66% chance
int
query_special_hitloc_id()
{
    return ({A_BODY, A_HEAD})[random(3) ? 0 : 1];
}

// Give messages
void
special_did_hit(object enemy, string hdesc, int hitloc_id, int phurt,
  int damage_type, int damage)
{
    string how;

    if (phurt <= 0)
	how = " with hardly any effect";
    else
	switch(phurt)
    {
    case 1..10:
	how = "";
	break;
    case 11..20:
	how = " with a thud";
	break;
    case 21..40:
	how = " with a loud thud";
	break;
    case 41..70:
	how = " with a loud crack";
	break;
    default:
	how = " with a bone crushing sound";
    }

    if (hitloc_id == A_BODY)
    {
	enemy->catch_msg(QCTNAME(TO) + " parries your blow with his "+
	  query_weapon(-1)[0]->short() +
	  ", then slams his shoulder into your " +
	  "side" + how + ".\n"); 
	tell_room(ENV(enemy), QCTNAME(TO) + " parries " + QTNAME(enemy) +
	  "'s blow " + "with his " + query_weapon(-1)[0]->short() +
	  ", then slams his shoulder " +
	  "into " + HIS(enemy) + " side" + how + ".\n", enemy);
    }
    else
    {
	enemy->catch_msg(QCTNAME(TO) + " dodges your swing, then brings " +
	  "up the hilt of his " + query_weapon(-1)[0]->short() +
	  " across your face" + how + ".\n");
	tell_room(ENV(enemy), QCTNAME(TO) + " dodges " + QTNAME(enemy) +
	  "'s swing, " + "then brings up the hilt of his " +
	  query_weapon(-1)[0]->short() + " across " +
	  HIS(enemy) + " face" + how + ".\n", enemy);
    }
}
