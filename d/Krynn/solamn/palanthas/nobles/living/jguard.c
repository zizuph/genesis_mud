/* 
 * Jeweler guard, outside Harnencourt's.
 * 
 * Mortis 10.2006
 */

#include "../../local.h"
#include <ss_types.h>
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <filter_funs.h>

inherit M_FILE
inherit "/std/act/domove";
inherit "/std/act/action";

void arm_me();
string vigrato();
string vigrato2();

void
create_krynn_monster()
{
	seteuid(getuid(TO));

	set_name("phyllis");
	set_living_name("phyllis");
	set_race_name("human");
	add_name(({"phyllis", "human", "guard"}));
	set_gender(G_FEMALE);
	set_adj("lean");
	add_adj(({"blond-haired", "blond"}));
	set_title("the Renowned Mercenary and Balladeer of Prestige");
	set_short("lean blond-haired female human");
	set_long("She is a lean blond-haired female human.\n"
	+ "Her voice is dedicated to Calliope, Muse of Vocas.\n"
	+ "She is wearing a black shield holster on her back.\n"
	+ "She has scars on her right thigh and right shoulder.\n"
	+ "Her hair is long, blond, and tied back in a pony tail.\n"
	+ "She has appraising dark-brown eyes.\n");

	set_size_descs("tall", "lean");
	set_appearance(7);
	
	set_stats(({95, 130, 110, 90, 105, 95}));
	set_alignment(400);
	set_knight_prestige(-10);
	set_introduce(1);

	set_skill(SS_DEFENCE,      80);
	set_skill(SS_PARRY,        55);
	set_skill(SS_WEP_SWORD,    80);
	set_skill(SS_UNARM_COMBAT, 30);
	set_skill(SS_AWARENESS,    40);
	set_skill(SS_BLIND_COMBAT, 35);

	set_all_attack_unarmed(20, 30);
	set_all_hitloc_unarmed(40);
	
	add_prop(NPC_I_NO_RUN_AWAY, 1);

	add_ask(({"vibrato", "vigrato"}), "asay friend you know, vibrato?  my "
	+ "muse can focus her power through me.", 1);
	add_ask(({"entry", "jeweler", "jewels", "jewelers", "jewelry", "jewel",
	"harnoncourt", "harnoncourts", "lapidary", "lapidarian", "pennington",
	"shop", "store"}), "say the harnoncourt's jewelry pays me to keep an "
	+ "eye out for thieves and when I'm not soloing dragons and all this "
	+ "place is safe as an eagle's eyrie.", 1);
	add_ask(({"yeti", "yetis", "yeties", "dragon", "dragons", "giant",
	"giants", "troll", "trolls"}), "say yeah I can solo that.  I just "
	+ "need a good shield and lots of herbs.", 1);
	add_ask(({"palanthas", "city"}), "asay excit this place is pretty "
	+ "incredible.  I love living here!", 1);
	add_ask(({"team", "want to team", "wantto team", "want to team?",
	"wantto team?", "teaming", "teams"}), "say yeah, I'd love to, but "
	+ "this shield sucks.  I have to stick around here anyway for a "
	+ "bit.", 1);
	add_ask(({"shield", "shields"}), "say this one's ok, but I need an "
	+ "uber shield.", 1);
	
    set_default_answer("@@def_answer");

	set_act_time(17);
	add_act("smell");
	add_act("say hi");
	add_act("say need a merc?");
	add_act("say wantto team?");
	add_act("say can we be frends?");
	add_act("emote clears her throat for attention.");
	add_act("emote places a polished ivory-nailed finger to her lips "
	+ "in contemplation.");
	add_act("@@vigrato");

	set_cact_time(4);
	add_cact("emote blocks your attack with her steel-centered wooden "
	+ "shield.");

	set_alarm(1.0, 0.0, arm_me);
}

string
def_answer()
{
	command("say yeah, I don't know.  sorry.");

	if (random(3) == 1)
		command("say ever solo " + one_of_list(({"the yeti", "the "
		+ "deep dragon", "a giant", "a dragon"})) + "?");
	return "";
}

void
arm_me()
{
	object ppants, pvest, pshirt, pgloves, pslippers, pshield, psword;

	ppants = clone_object(NOBLE + "arms/parmour");
	ppants->set_armour_data("Phyllis" + "&&" + "loose" + "&&" + "white" + "&&"
		+ "cotton" + "&&" + "baggy-pants");
	ppants->move(TO);

	pvest = clone_object(NOBLE + "arms/parmour");
	pvest->set_armour_data("Phyllis" + "&&" + "double-breasted" + "&&"
	+ "beige" + "&&" + "leather" + "&&" + "vest");
	pvest->move(TO);

	pshirt = clone_object(NOBLE + "arms/parmour");
	pshirt->set_armour_data("Phyllis" + "&&" + "thin" + "&&"
	+ "grey" + "&&" + "silk" + "&&" + "sleeveless-shirt");
	pshirt->move(TO);

	pgloves = clone_object(NOBLE + "arms/parmour");
	pgloves->set_armour_data("Phyllis" + "&&" + "rugged" + "&&"
	+ "dark-brown" + "&&" + "leather" + "&&" + "long-gloves");
	pgloves->move(TO);

	pslippers = clone_object(MONKS + "arms/lurr_shoes");
	pslippers->set_footwear_data("soft" + "&&"
	+ "pale-blue" + "&&" + "deer" + "&&" + "slippers");
	pslippers->move(TO);

	pshield = clone_object(NOBLE + "arms/jguard_shield");
	pshield->move(TO);

	psword = clone_object(MERCH + "arms/smith_sword");
	psword->set_weapon_data("polished" + "&&" + "long" + "&&" + "sword");
	psword->move(TO);

	command("wield all");
	command("wear all");
}

string
vigrato()
{
	command("say with vigrato, i've got enough herbs to kill the yeti");
	set_alarm(3.0, 0.0, "vigrato2");
	return "";
}

string
vigrato2()
{
	command("say errr vibrato");
	command("oops");
	return "";
}

void
attacked_by(object ob)
{
	command("say it's going to be hard being friends when you're dead");

    ::attacked_by(ob);
}

int
special_attack(object enemy)
{
    int pen, att, pmana = TO->query_mana();
    string how, how2;
    mixed hitres;

	// "Vigrato" attack:
    if (random(6) == 1 && pmana > 99)
    {
		pen = 225 + random(125);

		hitres = enemy->hit_me(pen, MAGIC_DT, TO, -1);

		command("emote raises her voice to Calliope, Muse of Vocas!");
		TO->add_mana(-100);

		switch (hitres[0])
		{
			case -1..0:
				enemy->catch_msg(QCTNAME(TO) + " directs waves of sound at "
				+ "you vibrating the air in a low thrum as she misses.\n");
				tell_room(E(TO), QCTNAME(TO) + " directs waves of sound at "
				+ QTNAME(enemy) + " vibrating the air in a low thrum as she "
				+ "misses.\n", ({enemy, TO}));
				break;
			case 1..9:
				enemy->catch_msg(QCTNAME(TO) + " focuses waves of sound at "
				+ "you buffeting your body.\n");
				tell_room(E(TO), QCTNAME(TO) + " focuses waves of sound at "
				+ QTNAME(enemy) + " buffeting " + HIS(enemy) + " body.\n",
				({enemy, TO}));
				break;
			case 10..30:
				enemy->catch_msg(QCTNAME(TO) + " forces you to the ground "
				+ "with the power of her voice.\n");
				tell_room(E(TO), QCTNAME(TO) + " forces " + QTNAME(enemy)
				+ "to the ground with the power of her voice.\n",
				({enemy, TO}));
				break;
			case 31..66:
				enemy->catch_msg(QCTNAME(TO) + " blasts you back with a "
				+ "stunning oratorio of concordant sound.\n");
				tell_room(E(TO), QCTNAME(TO) + " blasts " + QTNAME(enemy)
				+ " with a stunning oratorio of concordant sound.\n",
				({enemy, TO}));
				break;
			default:
				enemy->catch_msg(QCTNAME(TO) + " nearly ruptures your "
				+ "internal organs with wave after wave of concordant "
				+ "blasts of sound.\n");
				tell_room(E(TO), QCTNAME(TO) + " nearly ruptures the "
				+ "internal organs of " + QTNAME(enemy) + " with wave "
				+ "after wave of concordant blasts of sound.\n", ({enemy, TO}));
				break;
		}

		if (enemy->query_hp() <= 0)
			enemy->do_die(TO);

		return 1;
    }

	// Merc styled attack.  These could be more accurate.
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

		pen = 25 + random(100);
		hitres = enemy->hit_me(pen, damtype, TO, -1, wloc);

		switch (hitres[0])
		{
			case -2..0:
				how = "but misses";
				how2 = how;
				break;
			case 1..10:
				how = "grazing dangerously";
				how2 = how;
				break;
			case 11..20:
				how = "hurting you skillfully";
				how2 = "hurting " + HIM(enemy) + " skillfully";
				break;
			case 21..30:
				how = "cutting into you deeply";
				how2 = "cutting into " + HIM(enemy) + " deeply";
				break;
			case 31..40:
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
