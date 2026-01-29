/* 
 * Mid level member of the Brix gang in the back
 * alleys of Jems Court in the Aesthetics quarter
 * of Palanthas.
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
inherit "/lib/unique";

/*prototype*/
void arm_me();
string whip_it();

void
create_brix_ganger()
{
    seteuid(getuid(TO));

	set_name("aysha");
	add_name(({"_brix_ganger", "ganger", "gangster", "hoodlum"}));
	set_adj("pug-nosed");
	add_adj("forehead-scarred");
	set_gender(G_FEMALE);
	set_short("pug-nosed forehead-scarred female hoodlum");
	set_long("With her long, light brown hair tied back in a bun you have a "
	+ "plain view of the mass of scars primarily in the center of this "
	+ "woman's forehead.  Her pug nose and curled lips seem to sneer "
	+ "derisively at you.\n"
	+ "She is wearing a black handkerchief over her hair.\n"
	+ "She has strips of black hemp cloth wrapped around her palms.\n"
	+ "She has a tattoo of an executioner's axe wrapped in bloody chains "
	+ "on her left bicep.\n");
	set_race_name("human");
	set_living_name("aysha");
	set_title("the Pig Sticker of the Brix");
	
	set_size_descs("of normal length", "lean");
	set_appearance(2);

	set_all_hitloc_unarmed(5);

	set_skill(SS_DEFENCE,      60);
	set_skill(SS_PARRY,        47);
	set_skill(SS_2H_COMBAT,    50);
	set_skill(SS_UNARM_COMBAT, 52);
	set_skill(SS_AWARENESS,    37);
	set_skill(SS_WEP_CLUB,     60);
	set_skill(SS_WEP_KNIFE,    60);
    set_skill(SS_BLIND_COMBAT, 32);

	set_stats((({97, 115, 110, 37, 75, 82})), 4);

	set_alignment(-375);
	set_knight_prestige(1);

	set_introduce(1);

    set_default_answer("@@def_answer");

	add_ask(({"palanthas", "city"}), "asay deris Palanthas is great?  "
	+ "Palanthas is safe?  Who's looking out for the little man?  Hagen?  "
	+ "Who's looking out for the hood?  The Brix.  That's who.", 1);
	add_ask(({"chief", "constable", "hagen"}), "asay aci Hagen?  Ol'red "
	+ "better not show his face 'round here.  Course he knows already "
	+ "not to mess with Brix.", 1);
	add_ask(({"brix", "gang", "gangs", "hoodlum", "hoodlums", "ganger",
		"gangers"}), "asay proud Kirk and The Brix, we own Jems court, "
	+ "see?  We look out for our own and provide protection.  You tread "
	+ "on our turf or cross us?  You get smashed?  Samma wagga kan?  "
	+ "That's elf for \"Get it, hoser?\"", 1);
	add_ask(({"brick", "bricks"}), "asay know The bricks were Kirk's idea.  "
	+ "We started with nothin', see?  Now we got it all, but we don't forget "
	+ "our roots.  The Brix smash!", 1);
	add_ask(({"leader", "kirk"}), "asay quiet Kirk's head man around here.  "
	+ "Not even Hagen wants a piece of him.", 1);
	add_ask(({"gamble", "gambling", "dice", "onjat", "game"}), "asay secret "
	+ "Yeah, we run a little game of onjat downstairs through the tunnel, "
	+ "but you better not try your hand there if you're spoiling for "
	+ "trouble.  You won't -walk- back out.", 1);
	add_ask(({"monk", "monks", "aesthetic", "aesthetics"}), "asay amus Yeah, "
	+ "the scroll heads come down here for a game every once in a while.  "
	+ "Kirk doesn't mind.  They don't cause trouble.  They're smart like "
	+ "that, see?", 1);
	add_ask(({"forehead", "scar", "scars"}), "asay distant I wore a mark "
	+ "long ago, but I've put that behind me.", 1);
	add_ask("mark", "asay viol Mind your own business!  You're nothing, you "
	+ "hear me?  Nothing!", 1);

	set_act_time(45);
	add_act("get it");
	add_act("ffinger ganger");
	add_act("smile devious");
	add_act("asay inq Anyone up for a game later?");
	add_act("asay gre Yeah, well I won fifty in last night's onjat.");
	add_act("asay grave Last time I saw someone pull that, they dragged "
	+ "him out of the tunnel...  one sackfull at a time.");
	add_act("fart");
	add_act("emote smashes what used to be a bug into goo with an old red "
	+ "brick.");
	add_act("emote smiles widely to reveal several broken teeth.");
	add_act("asay menac What are you doing in the court?");
	add_act("asay angr Gambling?  Who the frung said anything about "
	+ "gambling?");

	set_cact_time(40);
	add_cact("@@whip_it");

	set_alarm(1.0,0.0,"arm_me");
}

string
def_answer()
{
    command("say How the frung should I know?  " + one_of_list(({"The Brix "
	+ "don't give shit for that.", "Now get lost.  This is our street.",
	  "Don't mess with the Brix unless you like getting smashed.", "You ask "
	+ "too many questions."})));
    return "";
}

string
whip_it()
{
	object myenemy = TO->query_enemy();

	if (!myenemy)
		command("say Huh?");

	string whipwho = L((myenemy)->query_name());

	command("asay angr Take this, pud!");
	myenemy->command("shout Noooooooo!");
	command("whip " + whipwho);
	return "";
}

void
arm_me()
{
	object wpants, wshirt, wshoes;

	wshirt = clone_object(NOBLE + "arms/parmour");
	wshirt->set_armour_data("the Brix" + "&&"
							+ "tight" + "&&"
							+ "black" + "&&"
							+ "hemp" + "&&"
							+ "sleeveless-shirt");
	wshirt->set_condition(1);
	wshirt->move(TO);

	wshoes = clone_object(MONKS + "arms/lurr_shoes");
	wshoes->set_footwear_data("open-toed" + "&&" + "mottled-brown" + "&&"
							  + "leather" + "&&" + "slippers");
	wshoes->move(TO);

	clone_object(MONKS + "arms/brix_pants_mid")->move(TO);
	clone_unique(MONKS + "arms/brix_knife_aysha", 3,
		MONKS + "arms/brix_knife_low", 1, 80)->move(TO);
	clone_object(MONKS + "arms/brix_whip_mid")->move(TO);

	MONEY_MAKE_GC(random(6))->move(TO);
	MONEY_MAKE_SC(20 + random(20))->move(TO);

	command("wear all");
	command("wield all");
}

void
attacked_by(object ob)
{
	switch (random(5))
	{
		case 0:
			command("asay obn Better check this one's loincloth.  I think "
			+ HE(ob) + " just dropped a brick.");
			break;
		case 1:
			command("asay firm No one messes with the Brix.  Smash this ho!");
			break;
		case 2:
			command("say Guess where this goes!");
			command("show knife");
			break;
		case 3:
			string xname = L(ob->query_name());
			command("say Take this, fool!");
			command("whip " + xname);
			break;
		case 4:
			command("Brix gonna make bread from your bones and make you eat "
			+ "it!");
			break;
		default:
			command("shout Hey, this \"" + ob->query_adj() + "\" "
			+ ob->query_race_name() + " wants to kiss me!  Get off me, pig!");
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
		weapon = "fists";
	
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
			attack = "bash";
			damtype = W_BLUDGEON;
			break;
		default:
			attack = "slash";
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

