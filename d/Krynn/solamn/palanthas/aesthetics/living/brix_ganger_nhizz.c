/* 
 * Mid level member of the Brix gang in the back
 * alleys of Jems Court in the Aesthetics quarter
 * of Palanthas.  Guards basement entrance to Onjat.
 *
 * Mortis 05.2006
 *
 */

#include "../../local.h"
#include <money.h>
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>

inherit BRIX_GANGER;

/*prototype*/
void arm_me();

void
create_brix_ganger()
{
    seteuid(getuid(TO));

	set_name("nhizz");
	add_name(({"_brix_ganger", "ganger", "gangster", "hoodlum", "lizard"}));
	set_adj("hooded");
	add_adj("hunched");
	set_gender(G_MALE);
	set_short("hooded hunched hoodlum");
	set_long("Dressed in a long, light brown robe, you can't see much of "
	+ "this hunched guard.  Its face is hidden beneath the robe's hood, and "
	+ "its hands withdrawn into its sleeves.  Its three-toed, green feet "
	+ "poking out from beneath the robe remind you of a lizard's with their "
	+ "thick, rough bumps and long claws.  The back of its robe occasionally "
	+ "moves unexpectedly as well.\n");
	set_race_name("lizardman");
	
	set_size_descs("short", "of normal width");
	set_appearance(-5);

	set_stats((({105, 145, 125, 45, 75, 105})), 3);

	set_all_attack_unarmed(14, 12);
	set_all_hitloc_unarmed(8);

	set_skill(SS_DEFENCE,      57);
	set_skill(SS_PARRY,        35);
	set_skill(SS_UNARM_COMBAT, 58);
	set_skill(SS_AWARENESS,    36);
	set_skill(SS_WEP_CLUB,     65);
    set_skill(SS_BLIND_COMBAT, 30);

	set_alignment(-400);
	set_knight_prestige(10);

    set_default_answer("@@def_answer");

	set_act_time(45);
	add_act("get it");
	add_act("emote twitches its head back and forth and... what's that?\n"
	+ "Did you just see a tail flick out briefly?");
	add_act("emote mutters slitheringly beneath its hood.");
	add_act("growl acid");
	add_act("spit");
	add_act("emote smashes what used to be a bug into goo with a clawed, "
	+ "green hand.");
	add_act("emote hisses:  Chug, what you sssay?");

	set_cact_time(40);
	add_cact("@@bite_it");

	set_alarm(1.0,0.0,"arm_me");
}

string
def_answer()
{
	command("emote hisses:  Nhizz sssay you to sssease!");
    return "";
}

string
bite_it()
{
	string biteloc = one_of_list(({"face", "neck", "right shoulder", "left "
	+ "shoulder", "stomach", "right arm", "left arm", "right hand", "left "
	+ "hand", "right leg", "left leg", "right ear", "left ear"}));
	object enemy = TO->query_enemy();

	enemy->catch_msg(QCTNAME(TO) + " spits a glob of saliva on your "
	+ "your " + biteloc + " leaving you gooey and woozy.\n");
	tell_room(E(TO), QCTNAME(TO) + " spits a glob of salive on "
	+ QTNAME(enemy) + "'s " + biteloc + ".\n", ({enemy, TO}));

	enemy->command("asay disgust No, sick... oh no... yech!");
	enemy->command("puke");
	return "";
}

void
arm_me()
{
	object wrobe;

	wrobe = clone_object(MERCH + "arms/daiv_robe");
	wrobe->set_armour_data("light" + "&&"
							+ "brown" + "&&"
							+ "cotton" + "&&"
							+ "robe" + "&&"
							+ "on" + "&&"
							+ "strips of an unknown " + "&&"
							+ "brownish-green" + "&&"
							+ "reptilian hide");
	wrobe->set_condition(1);
	wrobe->move(TO);

	MONEY_MAKE_GC(random(8))->move(TO);
	MONEY_MAKE_SC(10 + random(10))->move(TO);

	command("wear all");
}

void
attacked_by(object ob)
{
	command("emote hisses angrily, its forked red tongue flitting out from "
	+ "beneath its hood briefly!");

    ::attacked_by(ob);
}

int
special_attack(object enemy)
{
    int pen, att, wloc, weptype, damtype;
    string hitloc, attack, how, how2, weapon;
    mixed hitres;

	weapon = "dripping lizard maw";
	attack = "bite";
	damtype = W_IMPALE;

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
		pen = 44 + random(55);
		hitres = enemy->hit_me(pen, damtype, TO, -1, wloc);

		switch (hitres[0])
		{
			case -1..0:
				how = "but misses";
				how2 = how;
				break;

			case 1..6:
				how = "barely landing";
				how2 = how;
				break;

			case 7..14:
				how = "with cheap, underhanded moves";
				how2 = how;
				break;

			case 15..30:
				how = "in a display of backstreet cunning";
				how2 = how;
				break;

			case 31..49:
				how = "maiming you visibly";
				how2 = "maiming " + HIM(enemy) + " slightly";
				break;

			default:
				how = "maiming you greatly";
				how2 = "maiming " + HIM(enemy) + " greatly";
				break;
		}

		enemy->catch_msg(QCTNAME(TO) + " attempts to " + attack + " your "
		+ hitloc + " with " + HIS(TO) + " " + weapon + " " + how + ".\n");

		tell_room(E(TO), QCTNAME(TO) + " attempts to " + attack + " "
		+ QTNAME(enemy) + "'s " + hitloc + " with " + HIS(TO) + " " + weapon
		+ " " + how2 + ".\n", ({enemy, TO}));

		if (enemy->query_hp() <= 0)
		{
			enemy->do_die(TO);
			return 1;
		}

		if (hitres[0] > 0 && random(3) == 1)
		{
			enemy->catch_msg(QCTNAME(TO) + "'s saliva-dripping teeth burn "
			+ "as they sink into your " + hitloc + ".\n");
			object lizpoison = clone_object(MONKS + "obj/brix_lizard_poison");
			lizpoison->move(enemy);
			lizpoison->start_poison(TO);
		}

		return 1;
    }

    return 0;
}

