/* 
 * Entry level member of the Brix gang in the back
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

/*prototype*/
int my_gender();
string my_short();
string adj1();
string adj2();
string my_tattoos();
void arm_me();

int gender;
string adj1, adj2, myshort, gendstr, tattoos;
string scars = one_of_list(({}));

public void
create_brix_ganger()
{
    seteuid(getuid(TO));

	my_gender();
	adj1();
	adj2();
	my_short();

	set_name("hoodlum");
	add_name(({"_brix_ganger", "ganger", "gangster"}));
	set_adj(adj1);
	add_adj(({adj2}));
	set_gender(gender);
	set_short(myshort);
	set_long("@@my_long");
	set_race_name("human");
	
	set_skill(SS_DEFENCE,      36 + random(10));
	set_skill(SS_UNARM_COMBAT, 41 + random(10));
	set_skill(SS_AWARENESS,    26 + random(10));
	set_skill(SS_WEP_CLUB,     45 + random(9));
	set_skill(SS_WEP_KNIFE,    50 + random(4));
    set_skill(SS_BLIND_COMBAT, 20 + random(4));

	set_stats((({75, 65, 90, 35, 60, 60})), 21);

	set_alignment(10 - random(400));
	set_knight_prestige(0);

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

	set_act_time(45);
	add_act("get it");
	add_act("ffinger ganger");
	add_act("smile elv");
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

	tattoos = my_tattoos();

	set_alarm(1.0, 0.0, arm_me);
}

string
adj1()
{
	adj1 = one_of_list(({"unkempt", "menacing", "wiry", "scarred", "tattooed",
		"wary-eyed", "one-eyed", "slovenly", "rough", "sneering"}));
	return adj1;
}

string
adj2()
{
	adj2 = one_of_list(({"wild-haired", "pony-tailed", "long-haired",
		"jut-jawed", "bent-nosed", "dirty-faced", "tanned", "pale-faced"}));
	return adj2;
}

int
my_gender()
{
	gender = G_MALE;

	if (random(10) == 1)
		gender = G_FEMALE;

	return gender;
}

string
my_short()
{
	gendstr = "male";

	if (gender == G_FEMALE)
		gendstr = "female";

	myshort = adj1 + " " + adj2 + " " + gendstr + " hoodlum";
	return myshort;
}

string
my_long()
{
	string boygirl = "fellow";

	if (gendstr == "female")
		boygirl = "girl";

	return "Poorly dressed in rough and tumble street clothes, this "
	+ boygirl + " grimaces at you, " + HIS(TO) + " eyes narrowed menacingly "
	+ "and chest puffed up in a display of strength.  " + C(HE(TO)) + " has "
	+ tattoos + " and numerous scars.\n";
}

string
tatt_items()
{
	return one_of_list(({"wild boars", "heavily clawed bears",
		"black panthers", "axes", "chains", "thorns", "knives", "hammers",
		"ghoulish faces", "large-fanged snakes", "scorpions"}));
}

string
my_tattoos()
{
	string tatt, item1, item2, loc;

	if (random(2) == 1)
	{
		item1 = tatt_items();
		item2 = tatt_items();

		loc = one_of_list(({"up and down " + HIS(TO) + " arms", "covering "
		+ HIS(TO) + " left arm", "covering " + HIS(TO) + " right arm", "over "
		+ "the backs of both hands", "circling " + HIS(TO) + " neck"}));

		if (item1 == item2)
			return "tattoos of " + item1 + " " + loc;

		else
			return "tattoos of " + item1 + " and " + item2 + " " + loc;
	}

	item1 = one_of_list(({"a scandalously alluring mermaid bent "
	+ "back over a rock", "a crudely drawn dagger", "a blood-dripping dagger",
	  "a pair of onjat dice", "a skull with a rusted spike through it",
	  "a blood-red brick", "a pair of crudely drawn, topless women", "a tear",
	  "two pairs of claws reaching from within a cloud of black", "a crude "
	+ "anchor", "a rusty, iron fist", "an executioner's axe"}));

	loc = one_of_list(({"left hand", "right hand", "left forearm", "right "
	+ "forearm", "left bicep", "right bicep", "neck", "upper chest", "left "
	+ "cheek", "right cheek", "forehead"}));

	return "a tattoo of " + item1 + " on " + HIS(TO) + " " + loc;
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

void
arm_me()
{
	object wpants, wshirt;

	wshirt = clone_object(NOBLE + "arms/parmour");
	wshirt->set_armour_data("the Brix" + "&&"
							+ "thin" + "&&"
							+ "black" + "&&"
							+ "hemp" + "&&"
							+ "sleeveless-shirt");
	wshirt->set_condition(1);
	wshirt->move(TO);

	clone_object(MONKS + "arms/brix_pants_low")->move(TO);
	command("wear all");

	switch (random(6))
	{
		case 0..1:
			clone_object(MONKS + "arms/brix_brick")->move(TO);
			break;
		case 2..4:
			clone_object(MONKS + "arms/brix_knife_low")->move(TO);
			break;
		default:
			clone_object(MONKS + "arms/brix_brass_knuckles")->move(TO);
			command("wear knuckles");
			break;
	}

	MONEY_MAKE_SC(random(13))->move(TO);
	MONEY_MAKE_CC(10 + random(10))->move(TO);
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
        if (!objectp(ob) || !ob->query_adj() || !ob->query_race_name())
        {
            command("shout Hey, this thing wants to kiss me!  Get off me, pig!");
        }
        else
        {
            command("shout Hey, this \"" + ob->query_adj() + "\" "
                    + ob->query_race_name() + " wants to kiss me!  Get off me, pig!");
        }
		break;
	case 3:
		command("say Take this, fool!");
		write("The " + short() + " smashes a brick over your head!\n");
		say("The " + short() + " smashes a brick over " + QCTNAME(ob)
		+ "'s head!\n");
		break;
	case 4:
		command("Brix gonna make bread from your bones and make you eat it!");
		break;
	default:
		command("say Wha happen, guys?!?");
		break;
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
		case W_KNIFE:
			attack = "stick";
			damtype = W_IMPALE;
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
			how = "with cheap, underhanded moves";
			how2 = how;
		}
		if(hitres[0] > 20)
		{
			how = "in a display of backstreet cunning";
			how2 = how;
		}
		if (hitres[0] > 40)
		{
			how = "maiming you visibly";
			how2 = "maiming " + HIM(enemy) + " slightly";
		}
		if (hitres[0] > 60)
		{
			how = "maiming you greatly";
			how2 = "maiming " + HIM(enemy) + " greatly";
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

