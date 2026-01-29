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

	set_name("chug");
	add_name(({"_brix_ganger", "ganger", "gangster", "hoodlum"}));
	set_adj("huge");
	add_adj("large-mouthed");
	set_gender(G_MALE);
	set_short("huge large-mouthed male hoodlum");
	set_long("Hulking at close to seven feet tall, this oversized man has "
	+ "the largest mouth and biggest, blocky teeth you've ever seen on a "
	+ "human.  " + one_of_list(({"Green", "Brown", "Blackish"})) + " goo "
	+ "drips from his lips, and his bulging, round eyes stare through you, "
	+ "ignorant of the embarassment.  His powerfully muscled arms are "
	+ "covered in scraggly, black hair and a loose layer of fat just like "
	+ "his scalp.\nHe has a tattoo of a giant ogre breaking the back of a "
	+ "bull with its hands and teeth on his right arm and a tattoo of a "
	+ "crude red brick below that.\nHe has numerous scars on the left side "
	+ "of his neck, left ear, and right forearm.\n");
	set_race_name("human");
	set_living_name("chug");
	set_title("the Brick Wall and Mouth of the Brix");
	
	set_size_descs("extremely tall", "fat");
	set_appearance(-5);

	set_stats((({155, 100, 160, 30, 70, 105})), 3);

	set_all_attack_unarmed(15, 31);
	set_all_hitloc_unarmed(7);

	set_skill(SS_DEFENCE,      57);
	set_skill(SS_PARRY,        35);
	set_skill(SS_UNARM_COMBAT, 58);
	set_skill(SS_AWARENESS,    36);
	set_skill(SS_WEP_CLUB,     65);
    set_skill(SS_BLIND_COMBAT, 30);

	set_alignment(-400);
	set_knight_prestige(10);

	set_introduce(1);

    set_default_answer("@@def_answer");

	add_ask(({"palanthas", "city"}), "asay deris Palanthas great?  "
	+ "Palanthas safe?  Who look out for little man?  Hagen?  "
	+ "Who look out for hood?  The Brix.  Brix smash!", 1);
	add_ask(({"chief", "constable", "hagen"}), "asay aci Hagen?  Ol'red "
	+ "not show face 'round here.  He knows don't mess with Brix.", 1);
	add_ask(({"brix", "gang", "gangs", "hoodlum", "hoodlums", "ganger",
		"gangers"}), "asay proud Kirk and The Brix, we own Jems court, "
	+ "see?  We look out for our own and provide protection.  You tread "
	+ "on our turf or cross us?  Brix smash!  BRIX SMASH!!!", 1);
	add_ask(({"brick", "bricks"}), "asay know The bricks were Kirk's idea.  "
	+ "We started with nothin', see?  Now we got all, but we don't forget "
	+ "roots.  Brix smash!", 1);
	add_ask(({"leader", "kirk"}), "asay quiet Kirk is head man here.  "
	+ "Not even Hagen want piece of him.", 1);
	add_ask(({"gamble", "gambling", "dice", "onjat", "game"}), "asay secret "
	+ "Yeah, we run a little game of onjat downstairs through the tunnel, "
	+ "but you better not try your hand there if you want fight.  You not "
	+ "-walk- back out.", 1);
	add_ask(({"monk", "monks", "aesthetic", "aesthetics"}), "asay amus Yeah, "
	+ "scroll heads come down here for a game every once in a while.  "
	+ "Kirk not mind.  They don't cause trouble.  They smart like "
	+ "that.", 1);

	set_act_time(45);
	add_act("get it");
	add_act("ffinger ganger");
	add_act("smile blank");
	add_act("asay inq Anyone up for a game later?");
	add_act("asay gre Yeah, well I won fifty in last night's onjat.");
	add_act("asay grave Last time I saw someone pull that, they dragged "
	+ "him out of the tunnel...  one sackfull at a time.");
	add_act("fart");
	add_act("spit");
	add_act("emote scratches his ass voraciously.");
	add_act("emote smashes what used to be a bug into goo with an old red "
	+ "brick.");
	add_act("emote smiles widely to reveal his big, blocky teeth.");
	add_act("asay menac What you are doing now here?");
	add_act("asay ang Gambling?  Who in frung say anything 'bout "
	+ "gambling?");

	set_cact_time(40);
	add_cact("@@bite_it");
	add_cact("command unwield all");
	add_cact("command wield all");

	set_alarm(1.0,0.0,"arm_me");
}

string
def_answer()
{
	command("emote drools with a blank stare on his face.");
    command("say How the frung should I know?  " + one_of_list(({"The Brix "
	+ "don't give shit for that.", "Now get lost.  This is our street.",
	  "Don't mess with the Brix unless you like getting smashed.", "You ask "
	+ "too many questions."})));
    return "";
}

string
bite_it()
{
	string biteloc = one_of_list(({"face", "neck", "right shoulder", "left "
	+ "shoulder", "stomach", "right arm", "left arm", "right hand", "left "
	+ "hand", "right leg", "left leg", "right ear", "left ear"}));
	object enemy = TO->query_enemy();

	command("shout Raaaaah!!!\n");

	enemy->catch_msg(QCTNAME(TO) + " opens wide his large mouth and bites "
	+ "your " + biteloc + " with his big, blocky teeth leaving sickly goo "
	+ "behind.\n");
	tell_room(E(TO), QCTNAME(TO) + " opens wide his large mouth and bites "
	+ QTNAME(enemy) + "'s " + biteloc + " with his big, blocky teeth "
	+ "leaving sickly goo behind.\n", enemy, TO);

	enemy->command("asay fran Oh, gods!  Get him off me!");
	return "";
}

void
arm_me()
{
	object wshirt, wcuir, wshoes;

	wshirt = clone_object(NOBLE + "arms/parmour");
	wshirt->set_armour_data("the Brix" + "&&"
							+ "thick" + "&&"
							+ "black" + "&&"
							+ "hemp" + "&&"
							+ "sleeveless-shirt");
	wshirt->set_condition(1);
	wshirt->move(TO);

	wcuir = clone_object(MERCH + "arms/larmour");
	wcuir->set_armour_data("heavy" + "&&"
							+ "brown" + "&&"
							+ "studded" + "&&"
							+ "armet");
	wcuir->move(TO);

	wshoes = clone_object(MONKS + "arms/lurr_shoes");
	wshoes->set_footwear_data("heavy" + "&&" + "dark-orange" + "&&"
							  + "studded" + "&&" + "boots");
	wshoes->move(TO);

	clone_object(MONKS + "arms/brix_pants_mid")->move(TO);
	clone_object(MONKS + "arms/brix_club_mid")->move(TO);

	MONEY_MAKE_GC(random(4))->move(TO);
	MONEY_MAKE_SC(15 + random(15))->move(TO);

	command("wear all");
	command("wield all");
}

void
attacked_by(object ob)
{
	switch (random(5))
	{
		case 0:
			command("asay lau Better check this one's loincloth.  I think "
			+ HE(ob) + " just dropped a brick.");
			break;
		case 1:
			command("asay stup No one mess with Brix.  Smash, SMASH!");
			break;
		case 2:
			command("shout Hey, this \"" + ob->query_adj() + "\" "
			+ ob->query_race_name() + " wants to kiss me!  Get off me, pig!");
			break;
		case 3:
			command("asay thirst Hunger strike!");
			set_alarm(1.0, 0.0, "bite_it");
			break;
		case 4:
			command("Brix gonna make bread from your bones and make you eat "
			+ "it!");
			break;
		default:
			command("say Brix bite!");
			break;
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
		weapon = "large, block-toothed mouth";

	else
	    weapon = wep[0]->query_short();

	weptype = wep[0]->query_wt();

	switch (weptype)
	{
		case W_KNIFE:
			attack = "stick";
			damtype = W_IMPALE;
			break;
		case W_CLUB:
			attack = "clobber";
			damtype = W_BLUDGEON;
			break;
		default:
			attack = "bite";
			damtype = W_BLUDGEON;
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
		pen = 48 + random(55);
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
			enemy->do_die(TO);

		return 1;
    }

    return 0;
}

