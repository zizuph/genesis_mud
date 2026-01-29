/* 
 * Mortis 03.2006
 *
 * Merchant house Trusq high guard.
 *
 */

#include "../../local.h"
#include <macros.h>
#include <money.h>
#include <ss_types.h>
#include <wa_types.h>
#include <formulas.h>
#include <language.h>

#define HGHOME						SHIP + "trusq_priv_guardroom"

inherit M_FILE
inherit "/lib/unique";

int attacked = 0;
object myhome = find_object(HGHOME);
object lord_attacker;

/*prototype*/
void arm_me();
string return_home();

void
create_krynn_monster()
{
    seteuid(getuid(TO));

	set_name("giae");
	set_living_name("giae");
	add_name("guard");
	set_adj("black-skinned");
	add_adj(({"muscular", "high"}));
	set_gender(G_FEMALE);
	set_short("black-skinned muscular female guard");
	set_long("It's hard to estimate this guard's age, but judging by her "
	+ "curves, she's not old.  Her skin is a rich brown appearing almost "
	+ "black in this dimly lit room, and her flowing black hair is tied "
	+ "back in a bun behind her head.  Though well-muscled, her eyes are "
	+ "deceptively soft and introspective.\n");
	set_race_name("human");
	set_title("the High Guard of Merchant House Trusq");
	
	set_size_descs("tall", "of normal width");
	set_appearance(6);
	set_introduce(1);

	set_skill(SS_DEFENCE,      80);
    set_skill(SS_PARRY,        50);
	set_skill(SS_UNARM_COMBAT, 45);
	set_skill(SS_AWARENESS,    40);
	set_skill(SS_WEP_SWORD,    70);
	set_skill(SS_WEP_KNIFE,    70);
	set_skill(SS_2H_COMBAT,    60);
    set_skill(SS_BLIND_COMBAT, 65);
	set_skill(SS_BACKSTAB,     70);
	set_skill(SS_SNEAK,        70);
	set_skill(SS_HIDE,         70);

	set_stats((({110, 140, 120, 75, 100, 150})), 3);

	set_all_attack_unarmed(35, 25);
	set_all_hitloc_unarmed(5);

	set_alignment(0);
	set_knight_prestige(-10);

    set_default_answer("@@def_answer");

    set_act_time(50);
	add_act("@@return_home");

	set_alarm(1.0,0.0,"arm_me");
}

string
def_answer()
{
    command("say Your words are meaningless.  How did you get in here?");
    return "";
}

void
arm_me()
{
	clone_unique(SHIP + "arms/trusq_slippers", 5, SHIP + "arms/trusq_boots",
		1, 100)->move(TO);
	clone_object(SHIP + "arms/trusq_headband")->move(TO);
	clone_object(SHIP + "arms/trusq_bp_high")->move(TO);
	clone_object(SHIP + "arms/trusq_pants_high")->move(TO);
	clone_object(SHIP + "arms/trusq_belt_high")->move(TO);
	clone_object(SHIP + "arms/trusq_ssword")->move(TO);
	
	object hpouch = clone_object(MERCH + "obj/lgeneral");
	hpouch->set_general_data("plain" + "&&" + "brown" + "&&" + "leather"
							 + "&&" + "belt-pouch");
	hpouch->move(TO);


	command("wield all");
	command("wear all");

	object hdag = clone_object(MERCH + "arms/smith_knife");
	hdag->set_weapon_data("long" + "&&" + "thin" + "&&" + "shiv");
	hdag->move(TO);

	MONEY_MAKE_GC(10 + random(10))->move(TO);
	MONEY_MAKE_SC(28 + random(23))->move(TO);

	command("put shiv in pouch");
	command("put coins in pouch");
	command("close pouch");
	command("wear pouch");

	// Routine to make sure door is closed and locked on reset.
	object hgkey = clone_object(SHIP + "obj/trusq_highguard_key");
	hgkey->move(TO);
	
	command("close door");
	command("lock door with key");

	hgkey->remove_object();
}

void
attacked_by(object ob)
{
	ob->add_prop(LIVE_I_ATTACKED_TRUSQ, 1);

	if (attacked == 0)
	{
		command("open pouch");
		command("get shiv from pouch");
		command("wield shiv");
		command("emote grasps her long thin shiv lightly with the "
		+ "fingers of her left hand.");

		attacked = 1;
	}

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
		pen = 210 + random(250);
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

void
save_my_lord(object who)
{
	string attacker;
	object *ene;

	if (E(who) != E(TO))
		return;

	attacker = who->query_real_name();

    command("backstab " + attacker + " with shiv");
}

void
assist_lord(mixed who, object where)
{
	if (stringp(who))
		lord_attacker = find_living(who);
	else if (objectp(who))
		lord_attacker = who;
	else
		return;

	if (E(lord_attacker) != where)
		return;

	command("open pouch");
	command("get shiv from pouch");
	command("wield shiv");
	command("hide");
    move(where); 
    save_my_lord(who);
}

string
return_home()
{
	if (E(TO) != myhome)
	{
		command("say I'll be in my room.");
		command("bow trusq");
		move_living("disappearing into the shadows", myhome, 1, 0);
		return "";
	}
	return "";
}

void
do_die(object killer)
{
	command("remove slippers");
    ::do_die(killer);
}
