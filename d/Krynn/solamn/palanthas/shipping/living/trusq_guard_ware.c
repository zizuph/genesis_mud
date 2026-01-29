/* 
 * Mortis 02.2006
 *
 * Standard merchant house Trusq security guard.
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
inherit "/d/Krynn/std/act/actions";

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
	+ " is professionally trained to provide a high level of service.\n"
	+ C(HE(TO)) + " is wearing a silver crescent necklace.\n");
	set_race_name("human");
	
	set_skill(SS_DEFENCE,      75);
    set_skill(SS_PARRY,        45);
	set_skill(SS_UNARM_COMBAT, 30);
	set_skill(SS_AWARENESS,    30);
	set_skill(SS_WEP_CLUB,     65);
	set_skill(SS_WEP_AXE,      75);
    set_skill(SS_BLIND_COMBAT, 50);

	set_stats((({105, 95, 100, 45, 55, 85})), 4);

	set_alignment(375);
	set_knight_prestige(-10);

//	set_pick_up_team("guard");
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
	adj1 = one_of_list(({"professional", "curt", "well-groomed", "sharp"}));
	return adj1;
}

string
adj2()
{
	adj2 = one_of_list(({"blond-haired", "black-haired", "buzz-cut",
	"brown-haired", "side-burned", "short-haired",
	"seasoned", "young"}));
	return adj2;
}

int
my_gender()
{
	gender = one_of_list(({G_MALE, G_MALE, G_FEMALE}));
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
	int ranwep = random(3);

	clone_object(SHIP + "arms/trusq_boots")->move(TO);
	clone_object(SHIP + "arms/trusq_greaves")->move(TO);
	clone_object(SHIP + "arms/trusq_bp")->move(TO);
	clone_object(SHIP + "arms/trusq_helm")->move(TO);
	clone_object(SHIP + "arms/trusq_robe")->move(TO);

	if (ranwep == 0)
		clone_object(SHIP + "arms/trusq_mace")->move(TO);
	if (ranwep == 1)
		clone_object(SHIP + "arms/trusq_hmace")->move(TO);
	if (ranwep == 2)
		clone_object(SHIP + "arms/trusq_axe")->move(TO);

	command("wield all");
	command("wear all");
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
			command("shout This " + obrace + " has been murdering and "
			+ "pillaging in the house!  Death to the " + obrace + "!");
			break;
		case 1:
			command("shout Blasted " + obrace + "!  The Jent Port "
			+ "Security Force will teach you the meaning of "
			+ one_of_list(({"malnutrition", "dislike", "harum",
			"pain-grog", "dwarven shackle treatment", "Nixlar"}))
			+ "!");
			break;
		default:
			command("say Since when did Jent Port allow violators like "
			+ "this " + obrace + " to walk freely?");
			command("shout Die, " + obrace + " whose rear is soiled "
			+ "and foul!");
			break;		
	}

	action_attack(enemy);
}

void
init_living()
{
    init_team_pickup();
    ::init_living();

	if (TP->query_prop(LIVE_I_ATTACKED_TRUSQ) == 1)
    {
        set_alarm(0.5, 0.0, &attack_func(TP));
        return;
    }

}

void
attacked_by(object ob)
{
	ob->add_prop(LIVE_I_ATTACKED_TRUSQ, 1);

	if (random(7) == 1)
		command("emote hands a missive to a young boy and says:  Let the "
		+ "constabulary know of this attack!");
	else
		command("say Service and honour.");

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

    if (random(6) == 1)
    {
		pen = 60 + random(105);
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

