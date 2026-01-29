/* 
 * Mortis 03.2006
 *
 * Merchant house Trusq warehouse warehouse manager.
 *
 */

#include "../../local.h"
#include <macros.h>
#include <money.h>
#include <ss_types.h>
#include <wa_types.h>
#include <formulas.h>
#include <language.h>

inherit M_FILE
inherit AUTO_TEAM

object mywep;

/*prototype*/
void arm_me();

void
create_krynn_monster()
{
    seteuid(getuid(TO));

	set_name("manager");
	set_adj("warehouse");
	add_adj(({"double-chinned", "eyebrow-raising"}));
	set_gender(G_MALE);
	set_short("double-chinned eyebrow-raising male warehouse manager");
	set_long("With a stout double chin, half smile, and curiously raised "
	+ "eyebrow, this warehouse manager is ruggedly good-looking.  For "
	+ "working in an oft-times hot and dirty warehouse, he dresses well "
	+ "and stays clean.\nHe has smooth, black hair combed over to the "
	+ "right.\nHe has dark brown alluring eyes.\n");
	set_race_name("human");
	
	set_size_descs("of normal length", "of normal width");
	set_appearance(6);

	set_skill(SS_DEFENCE,      45);
	set_skill(SS_PARRY,        40);
	set_skill(SS_UNARM_COMBAT, 40);
	set_skill(SS_AWARENESS,    30);
	set_skill(SS_WEP_KNIFE,    60);
    set_skill(SS_BLIND_COMBAT, 30);

	set_stats((({90, 75, 95, 70, 75, 125})), 6);

    set_pick_up_team("guard");
    set_max_team_size_auto_join(5);

	set_alignment(665);
	set_knight_prestige(-30);

    set_default_answer("@@def_answer");

	set_alarm(1.0,0.0,"arm_me");
}

string
def_answer()
{
	command("emote dabs at " + HIS(TO) + " brow with a handkerchief.");
    command("say If you're looking for work, come back in the Maygr season.");
    return "";
}

void
arm_me()
{
	object wpants, wshirt;

	wshirt = clone_object(NOBLE + "arms/parmour");
	wshirt->set_armour_data("Trusq warehouse workers" + "&&"
							+ "heavy" + "&&"
							+ "yellow" + "&&"
							+ "cotton" + "&&"
							+ "shirt");
	wshirt->move(TO);

	wpants = clone_object(NOBLE + "arms/parmour");
	wpants->set_armour_data("Trusq warehouse workers" + "&&"
							+ "rugged" + "&&"
							+ "pale-blue" + "&&"
							+ "linen" + "&&"
							+ "pantaloons");
	wpants->move(TO);

	MONEY_MAKE_GC(3 + random(4))->move(TO);
	MONEY_MAKE_SC(24 + random(20))->move(TO);

	command("wear all");
}

void
init_living()
{
    init_team_pickup();
    ::init_living();
}

void
attacked_by(object ob)
{
	ob->add_prop(LIVE_I_ATTACKED_TRUSQ, 1);

	if (random(7) == 1)
		command("shout Gods damn you, scag!");
	else
		command("shout Guards!  Escort this bilge to Lars.");

	if (!mywep)
	{
		mywep = clone_object(SHIP + "arms/trusq_knife");
		mywep->move(TO);
	}

	command("wield all");

    ::attacked_by(ob);
}

int
special_attack(object enemy)
{
    int pen, att, wloc, weptype, damtype;
    string hitloc, attack, how, how2, weapon;
    mixed hitres;
	object *wep = query_weapon(-1);

    if (!sizeof(wep))
		return 0;

    weapon = wep[0]->query_short();
	weptype = wep[0]->query_wt();

	switch (weptype)
	{
		case W_AXE:
			attack = "hack apart";
			damtype = W_SLASH;
			break;
		case W_CLUB:
			attack = "bash";
			damtype = W_BLUDGEON;
			break;
		default:
			attack = "strike";
			damtype = W_IMPALE;
			break;
	}

	switch (random(4))
	{
		case 0:
			hitloc = "head";
			wloc = A_HEAD;
			break;
		case 1:
			hitloc = "body";
			wloc = A_TORSO;
			break;
		case 2:
			hitloc = one_of_list(({"right arm", "left arm"}));
			wloc = A_ARMS;
			break;
		case 3:
			hitloc = "legs";
			wloc = A_LEGS;
			break;
		default:
			hitloc = "nuglek";
			wloc = A_TORSO;
			break;
	}

    if (random(7) == 1)
    {
		pen = 50 + random(60);
		hitres = enemy->hit_me(pen, damtype, TO, -1, wloc);

		if (hitres[0] <= 0)
		{
			how = "but misses";
			how2 = how;
		}
		if(hitres[0] > 0)
		{
			how = "barely landing";
			how2 = how;
		}
		if(hitres[0] > 10)
		{
			how = "debilitating you slightly";
			how2 = "debilitating " + HIM(enemy) + " slightly";
		}
		if(hitres[0] > 20)
		{
			how = "debilitating you greatly";
			how2 = "debilitating " + HIM(enemy) + " greatly";
		}
		if (hitres[0] > 40)
		{
			how = "with untrained power";
			how2 = how;
		}
		if (hitres[0] > 60)
		{
			how = "with haymaker like moves";
			how2 = how;
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

