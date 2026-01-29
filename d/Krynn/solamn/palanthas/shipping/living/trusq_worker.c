/* 
 * Mortis 03.2006
 *
 * Merchant house Trusq warehouse worker.
 *
 * EDITED:  The chance for a worker to grab a crowbar to fight with
 * were so low that it was possible for several refreshes of the
 * warehouse to fail to yield one.  As these are required for
 * breaking into places, I increased the chance of crowbars slightly.
 *
 * Mortis 01.2008
 *
 * Mortis 09.2014 - Changed attacked by messages.
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

/*prototype*/
int my_gender();
string my_short();
string adj1();
string adj2();
void arm_me();

int gender;
string adj1, adj2, myshort;
object mywep;

void
create_krynn_monster()
{
    seteuid(getuid(TO));

	my_gender();
	adj1();
	adj2();
	my_short();

	set_name("worker");
	set_adj(adj1);
	add_adj(({adj2, "warehouse"}));
	set_gender(gender);
	set_short(myshort);
	set_long("Sweating from hours of carrying crates, boxes, chests, and "
	+ "bags, this dock worker is stout, well-fed, and industrious.\n");
	set_race_name("human");
	
	set_skill(SS_DEFENCE,      40);
	set_skill(SS_UNARM_COMBAT, 30);
	set_skill(SS_AWARENESS,    25);
	set_skill(SS_WEP_CLUB,     45);
	set_skill(SS_WEP_KNIFE,    50);
    set_skill(SS_BLIND_COMBAT, 20);

	set_stats((({80, 60, 80, 40, 45, 75})), 8);

	set_alignment(225);
	set_knight_prestige(-5);

    set_pick_up_team("worker");
    set_max_team_size_auto_join(3);

    set_default_answer("@@def_answer");

	set_alarm(1.0,0.0,"arm_me");
}

string
adj1()
{
	adj1 = one_of_list(({"stout", "burly", "swarthy", "sweaty", "strong",
		"hard-working", "nasal-dripping"}));
	return adj1;
}

string
adj2()
{
	adj2 = one_of_list(({"bearded", "side-burned", "bushy-haired",
		"pony-tailed", "long-haired", "thick-jawed", "large-nosed",
		"brown-skinned", "tanned"}));
	return adj2;
}

int
my_gender()
{
	gender = G_MALE;

	if (random(6) == 1)
	{ gender = G_FEMALE; }

	return gender;
}

string
my_short()
{
	string gend = "male";

	if (gender == G_FEMALE)
	{ gend = "female"; }

	myshort = adj1 + " " + adj2 + " " + gend + " warehouse worker";
	return myshort;
}

string
def_answer()
{
	command("emote pauses briefly to wipe " + HIS(TO) + " brow.");
    command("say I don't have time to chat.  Talk to the supervisor if "
	+ "you're looking for work.");
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
							+ "sleeveless-shirt");
	wshirt->move(TO);

	wpants = clone_object(NOBLE + "arms/parmour");
	wpants->set_armour_data("Trusq warehouse workers" + "&&"
							+ "rugged" + "&&"
							+ "pale-blue" + "&&"
							+ "hemp" + "&&"
							+ "pantaloons");
	wpants->move(TO);

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
	int attby = random(10);

	ob->add_prop(LIVE_I_ATTACKED_TRUSQ, 1);

	switch(attby)
	{
		case 0:
			command("shout Gods damn you, scag!");
			break;
		case 1:
			command("shout Guard!  Where's those bloody Jents?");
			break;
		default:
			break;
	}

if (!mywep)
	{
	switch (random(6))
		{
			case 0:
			case 1:
				mywep = clone_object(SHIP + "arms/trusq_gaff");
				break;
			case 2:
			case 3:
				mywep = clone_object(SHIP + "arms/trusq_knife");
				break;
			default:
				mywep = clone_object(SHIP + "arms/trusq_crowbar");
				break;
		}
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
	{ return 0; }

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

    if (random(8) == 1)
    {
		pen = 45 + random(55);
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
		{ enemy->do_die(TO); }

		return 1;
    }

    return 0;
}

