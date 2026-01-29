/* 
 * Mortis 03.2006
 *
 * Grade three merchant house Trusq security guard.
 * Bodyguard of Trusq lord.
 *
 */

#include "../../local.h"
#include <macros.h>
#include <money.h>
#include <ss_types.h>
#include <wa_types.h>
#include <formulas.h>
#include <language.h>

#define LIVE_I_ATTACKED_TRUSQ		"_i_attacked_house_trusq"
#define ALT_WEP1					SHIP + "arms/trusq_hmace"
#define ALT_WEP2					SHIP + "arms/trusq_mace"
#define HIGH_GUARDROOM				SHIP + "trusq_priv_guardroom"

inherit M_FILE
inherit AUTO_TEAM
inherit "/lib/unique";

object guardhome = find_object(HIGH_GUARDROOM);

/*prototype*/
int my_gender();
string my_short();
string adj1();
string adj2();
void arm_me();

int gender;
string adj1, adj2, myshort;

void
create_krynn_monster()
{
    seteuid(getuid(TO));

	my_gender();
	adj1();
	adj2();
	my_short();

	set_name("guard");
	set_adj(adj1);
	add_adj(({adj2, "estate"}));
	set_gender(gender);
	set_short(myshort);
	set_long("Judging by this guard's posture and armaments, " + HE(TO)
	+ " is professionally trained to provide a very high level of service.\n"
	+ C(HE(TO)) + " is wearing a silver crescent necklace with two silver "
	+ "chevrons.\n");
	set_race_name("human");
	
	set_skill(SS_DEFENCE,      85);
    set_skill(SS_PARRY,        65);
	set_skill(SS_UNARM_COMBAT, 55);
	set_skill(SS_AWARENESS,    45);
	set_skill(SS_WEP_CLUB,     80);
	set_skill(SS_WEP_AXE,      85);
    set_skill(SS_BLIND_COMBAT, 60);

	set_stats((({125, 125, 140, 80, 90, 125})), 11);

	set_alignment(400);
	set_knight_prestige(-50);

    set_pick_up_team("trusq");
    set_max_team_size_auto_join(5);

	add_ask(({"guard", "guards", "guardsman", "jent", "jent port"}), "say "
	+ "The Jent Port Security Force provides the highest level of security "
	+ "to its clients anywhere in Palanthas.", 1);

    set_default_answer("@@def_answer");

	set_alarm(1.0,0.0,"arm_me");
}

string
adj1()
{
	adj1 = one_of_list(({"highly-professional", "perfectly-groomed",
		"razor-sharp"}));
	return adj1;
}

string
adj2()
{
	adj2 = one_of_list(({"blond-haired", "black-haired", "buzz-cut",
	"brown-haired", "side-burned", "bald", "seasoned"}));
	return adj2;
}

int
my_gender()
{
	gender = one_of_list(({G_MALE, G_MALE, G_MALE, G_MALE, G_FEMALE}));
	return gender;
}

string
my_short()
{
	string gend = "male";

	if (gender == G_FEMALE)
		gend = "female";

	myshort = adj1 + " " + adj2 + " " + gend + " estate guard";
	return myshort;
}

string
def_answer()
{
	command("say I am not here for your inquiries.  I am a professional "
	+ "in the service of the Jent Port Security Force.");
	command("emote clicks " + HIS(TO) + " heels together crisply.");
    return "";
}

void
arm_me()
{
	clone_object(SHIP + "arms/trusq_boots")->move(TO);
	clone_object(SHIP + "arms/trusq_greaves")->move(TO);
	clone_object(SHIP + "arms/trusq_bp")->move(TO);
	clone_object(SHIP + "arms/trusq_helm")->move(TO);
	clone_object(SHIP + "arms/trusq_robe")->move(TO);

	clone_unique(SHIP + "arms/trusq_axe_blue", 3,
		({ALT_WEP1, ALT_WEP2}), 1, 100)->move(TO);

	command("wield all");
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
	object bedroom = E(TO);

	ob->add_prop(LIVE_I_ATTACKED_TRUSQ, 1);

	guardhome->help_i_need_help(ob, bedroom);

	if (random(7) == 1)
		command("emote hands a missive to a young boy and says:  Let the "
		+ "constabulary know of this attack!");
	else
		command("say Service and honour.");

    ::attacked_by(ob);
}

void
rescue_lord(object who)
{
    object *ene;

	if (E(who) != E(TO))
      return;

    ene = who->query_enemy(-1);
    who->stop_fight(ene);
    ene->stop_fight(who);
    attack_object(who);
    command("emote steps in front of the merchant to defend him.\n");
    who->attack_object(TO);
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

    if (random(6) == 1)
    {
		pen = 325 + random(275);
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
			how = "with well-trained power";
			how2 = how;
		}
		if (hitres[0] > 60)
		{
			how = "with professionally lethal force";
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

