/* 
 * Internal armoured guard of Harnencourt jewelers.
 * Protects jeweler, rescues him, blocks criminals.
 * 
 * Mortis 10.2006
 */

#include "../../local.h"
#include <ss_types.h>
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <filter_funs.h>

#define LIVE_I_ATTACKED_PAL_JEWELER		"_live_i_attacked_palanthas_jeweler"

inherit M_FILE

void arm_me();

void
create_krynn_monster()
{
	seteuid(getuid(TO));

	set_name("guard");
	set_race_name("human");
	add_name(({"human", "guard"}));
	set_gender(G_MALE);
	set_adj("solemn");
	add_adj(({"armoured"}));
	set_short("solemn armoured male guard");
	set_long("Solemn and unyielding as a gravestone, this guard stands "
	+ "watch over the jeweler and his precious inventory.  His left sleeve "
	+ "is adorned with a red and white checkered band bearing the golden "
	+ "embroidered symbol of Palanthian Armour, two rampant lions with "
	+ "three golden balls between them beneath a flourished crown over "
	+ "the outline of a sharp-edged shield.  Guards of the Palanthian "
	+ "Armour service have a reputation for tough, no nonsense protection"
	+ ".\n");

	set_size_descs("tall", "of normal width");
	set_appearance(2);
	
	set_stats(({100, 100, 150, 80, 110, 140}));
	set_alignment(450);
	set_knight_prestige(-11);

	set_skill(SS_DEFENCE,      80);
	set_skill(SS_PARRY,        55);
	set_skill(SS_WEP_SWORD,    80);
	set_skill(SS_UNARM_COMBAT, 30);
	set_skill(SS_AWARENESS,    58);
	set_skill(SS_BLIND_COMBAT, 35);

	set_all_attack_unarmed(24, 21);
	set_all_hitloc_unarmed(30);
	
	add_prop(NPC_I_NO_RUN_AWAY, 1);

	set_act_time(35);
	add_act("dsheathe sword in scabbard");

	set_cact_time(20);
	add_cact("emote blocks your attack with her steel-centered wooden "
	+ "shield.");

	set_alarm(1.0, 0.0, arm_me);
}

void
arm_me()
{
	object ghauberk, gskirt, ghelm, pgloves, pboots, pscab, pbelt, psword;

	ghauberk = clone_object(NOBLE + "arms/pa_phauberk");
	ghauberk->move(TO);

	gskirt = clone_object(NOBLE + "arms/pa_skirt");
	gskirt->move(TO);

	ghelm = clone_object(NOBLE + "arms/pa_helm");
	ghelm->move(TO);

	pgloves = clone_object(NOBLE + "arms/parmour");
	pgloves->set_armour_data("Palanthian Armour" + "&&" + "heavy" + "&&"
	+ "black" + "&&" + "leather" + "&&" + "gloves");
	pgloves->move(TO);

	pboots = clone_object(MONKS + "arms/lurr_shoes");
	pboots->set_footwear_data("heavy" + "&&"
	+ "grey" + "&&" + "hard" + "&&" + "boots");
	pboots->move(TO);

	pscab = clone_object(MERCH + "obj/lgeneral");
	pscab->set_general_data("noble" + "&&" + "black" + "&&" + "leather"
	+ "&&" + "scabbard");
	pscab->move(TO);

	pbelt = clone_object(MERCH + "arms/larmour");
	pbelt->set_armour_data("heavy" + "&&" + "black" + "&&" + "leather"
	+ "&&" + "belt");
	pbelt->move(TO);

	psword = clone_object(MERCH + "arms/smith_sword");
	psword->set_weapon_data("polished" + "&&" + "long" + "&&" + "sword");
	psword->move(TO);

	command("wear all");
	command("wield all");
	command("dsheathe sword in scabbard");
}

void
attacked_by(object ob)
{
	command("ddraw from scabbard");
	if (random(3) == 1)
		command("asay confid Palanthian Armour:  Pride, Solemnity, "
		+ "Aggression.");
	
	ob->add_prop(LIVE_I_ATTACKED_PAL_JEWELER, 1);

    ::attacked_by(ob);
}

void
attack_func(object enemy)
{
    if (!CAN_SEE(TO, enemy))
        return;
    
	string obrace = QRACE(enemy);
    
	switch (random(3))
	{
		case 0:
			command("shout Stupid " + obrace + ".  Taste folded-steel!");
			break;
		case 1:
			command("asay confid Palanthian Armour:  Pride, Solemnity, "
			+ "Aggression.  You will learn... eventually.");
			break;
		default:
			command("shout The last time I fought a " + obrace + " this "
			+ "feeble, he fled with drawers full of his own excrement!");
			break;		
	}

	action_attack(enemy);
}

void
init_living()
{
    ::init_living();

	if (TP->query_prop(LIVE_I_ATTACKED_PAL_JEWELER) == 1)
    {
        set_alarm(0.5, 0.0, &attack_func(TP));
        return;
    }

}

void
rescue_employer(object who)
{
    object *ene;

	if (E(who) != E(TO))
      return;

    ene = who->query_enemy(-1);
    who->stop_fight(ene);
    ene->stop_fight(who);
    attack_object(who);
    command("emote waves the jeweler to the rear blocking him from harm.\n");
	command("ddraw from scabbard");
    who->attack_object(TO);
}

int
special_attack(object enemy)
{
    int pen, att, pmana = TO->query_mana();
    string how, how2;
    mixed hitres;

	if (random(5) == 1)
	{
		int wloc, damtype = W_IMPALE;
		string weapon, attack, hitloc;
		object *wep = query_weapon(-1);

		if (!sizeof(wep))
			return 0;

		weapon = wep[0]->query_short();
		attack = one_of_list(({"pierce", "slash"}));
		if (attack == "slash")
			damtype = W_SLASH;
		hitloc = "body";
		wloc = A_TORSO;

		pen = 250 + random(111);
		hitres = enemy->hit_me(pen, damtype, TO, -1, wloc);

		switch (hitres[0])
		{
			case -2..0:
				how = "but misses";
				how2 = how;
				break;
			case 1..5:
				how = "grazing dangerously";
				how2 = how;
				break;
			case 6..14:
				how = "hurting you skillfully";
				how2 = "hurting " + HIM(enemy) + " skillfully";
				break;
			case 15..22:
				how = "cutting into you deeply";
				how2 = "cutting into " + HIM(enemy) + " deeply";
				break;
			case 23..52:
				how = "stepping through your defenses and landing "
				+ "powerfully";
				how2 = "stepping through " + HIS(enemy) + " defenses and "
				+ "landing powerfully";
				break;
			default:
				how = "with a lethal flurry of blows";
				how2 = how;
				break;
		}

		enemy->catch_msg(QCTNAME(TO) + " attempts to " + attack + " your "
		+ hitloc + " with " + HIS(TO) + " " + weapon + " " + how + ".\n");

		tell_room(E(TO), QCTNAME(TO) + " attempts to " + attack + " "
		+ QTNAME(enemy) + "'s " + hitloc + " with " + HIS(TO) + " " + weapon
		+ " " + how2 + ".\n", ({enemy, TO}));

		if (enemy->query_hp() <= 0)
			enemy->do_die(TO);

		return 1;
	}

    return 0;
}
