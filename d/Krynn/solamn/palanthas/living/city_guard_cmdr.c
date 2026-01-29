/* 
 * Mortis 02.2006
 *
 * Standard city guard commanders found in the guard
 * towers in each district of Palanthas.
 *
 * If players can become Constable, these will change
 * to match their guild, but this is the default guard
 * commander.
 *
 */

#include "../local.h"
#include <macros.h>
#include <money.h>
#include <ss_types.h>
#include <wa_types.h>
#include <formulas.h>
#include <language.h>

#define MY_KNIFE		MERCH + "arms/smith_knife"
#define MY_SWORD		MERCH + "arms/smith_sword"
#define MY_POLEARM		MERCH + "arms/smith_polearm"
#define MY_CLUB			MERCH + "arms/smith_club"
#define MY_AXE			MERCH + "arms/smith_axe"
#define MY_CLOTHING		NOBLE + "arms/parmour"
#define MY_ARMOUR		MERCH + "arms/larmour"
#define MY_GENERAL		MERCH + "obj/lgeneral"

inherit M_FILE
inherit AUTO_TEAM
inherit "/d/Krynn/std/act/actions";

/*prototype*/
void adjects();
void arm_me();
void arm_me2();

int gender;
string adjstr1, adjstr2;

void
create_krynn_monster()
{
    seteuid(getuid(TO));

	set_name("guard");
	add_name(({"guardsman", "commander"}));

	adjects();
	
	set_short("@@my_short");
	set_long("A steady-nerved guardsman of the city of Palanthas sworn "
	+ "to uphold the laws and treat the citizenry with respect, this guard "
	+ "bears the tunic of a guard commander and has a calm, unflinching "
	+ "gaze.  The commander's open white tunic bears " + "@@constable_symbol@@"
	+ " above its left breast.\n");
	set_race_name("human");
	
	set_size_descs(one_of_list(({"tall", "of normal length"})),
		one_of_list(({"of normal width", "lean"})));
	set_appearance(3 + random(3));
	
	set_skill(SS_DEFENCE,      70);
    set_skill(SS_PARRY,        30);
	set_skill(SS_UNARM_COMBAT, 30);
	set_skill(SS_AWARENESS,    40);
    set_skill(SS_WEP_SWORD,    65);
	set_skill(SS_WEP_CLUB,     65);
	set_skill(SS_WEP_POLEARM,  60);
    set_skill(SS_BLIND_COMBAT, 30);

	set_stats((({85, 55, 65, 40, 45, 70})), 7);
	set_all_attack_unarmed(13, 10);
	set_all_hitloc_unarmed(6);

	set_alignment(550);
	set_knight_prestige(-80);

    set_pick_up_team("guard");
    set_max_team_size_auto_join(5);

	set_act_time(50);
	add_act("emote straightens an open white commander's tunic.");
	add_act("time");
	add_act("smell");
	add_act("emote ponders visiting the Plaisir district when the shift "
	+ "ends.");
	add_act("emote contemplates doing some reading in the Great Library "
	+ "when the shift ends.");
	add_act("say I heard Chief Constable Hagen jailed another thief.  The "
	+ "man is relentless.");
	add_act("say Miscreants in the marble city do not prosper, not with "
	+ "Hagen around.");
	add_act("emote gazes about the city serenely.");

	set_cact_time(36);
	add_cact("shout Violent offender!  Prepare the shackles!");
	add_cact("emote blocks the exit decrying:  It's jail or Lars for you, "
	+ "miscreant.");
	add_cact("emote pulls a pair of iron shackles from his belt.");
	add_cact("emote attempts to shackle you with a pair of iron shackles.");
	add_cact("say I command you to drop your weapons, miscreant, or you "
	+ "will not be allowed to leave this room alive.");

	add_ask(({"hagen", "chief", "constable"}), "say Hagen is the Chief "
	+ "Constable of Palanthas.  He's unstoppable, and will throw any "
	+ "miscreants in jail without a moment's hesitation.  They either "
	+ "<surrender> or die, and that's always been the case.", 1);
	add_ask("jail", "say The jail is still in the Palace, but they're "
	+ "building a newer, larger jail off the Palatial plaza.  I don't "
	+ "think Lord Amothus appreciates using the palace as a jail.", 1);
	add_ask(({"city", "palanthas"}), "say Palanthas' majesty is unrivaled!  "
	+ "The marble city is the best place to live in all the realms, and we "
	+ "keep it completely safe.  The city has never been compromised.", 1);
	add_ask(({"guard", "guards", "guardsman"}), "say The city guard is well-"
	+ "trained, competent, and motivated to keep Palanthas completely safe.  "
	+ "That's our promise.", 1);
	add_ask(({"library", "great library"}), "say The Great Library of "
	+ "Palanthas is the finest anywhere.  It is located in the inner "
	+ "city on the Aesthetics quarter side.", 1);

    set_default_answer("@@def_answer");

	set_alarm(1.0, 0.0, "arm_me");
	set_alarm(2.0, 0.0, "arm_me2");
}

void
adjects()
{
	adjstr1 = one_of_list(({"young", "cleanly", "well-groomed",
	"watchful-eyed", "middle-aged", "thin", "serene", "unflinching"}));

	adjstr2 = one_of_list(({"blond-haired", "black-haired", "buzz-cut",
	"brown-haired", "side-burned", "moustachioed", "short-haired",
	"seasoned", "imposing"}));

	gender = one_of_list(({G_MALE, G_FEMALE}));
	set_gender(gender);
}

string
my_short()
{
	string gend = "male";

	if (TO->query_gender() == G_FEMALE)
		gend = "female";

	return adjstr1 + " " + adjstr2 + " " + gend + " commander";
}

string
def_answer()
{
    command("say That's some question, citizen.  I wish you luck finding "
	+ "the answers.  Perhaps you could try the Great Library?");
    return "";
}

void
arm_me()
{
	string whichbody, whichwep;
	object gpants, gwep;

	if (random(5) == 1)
		whichbody = "shirt";
	else
		whichbody = one_of_list(({"coat", "vest"}));

	// Guard's standard weapon.
	whichwep = one_of_list(({"gwep_sword_cmdr", "gwep_club_cmdr"}));
	gwep = clone_object(OBJ + whichwep);
	gwep->move(TO);

	if (whichwep != "gwep_polearm")
		clone_object(OBJ + "garmour_shield")->move(TO);

	// Guard's custom legwear.
	gpants = clone_object(MY_CLOTHING);
    gpants->set_armour_data("the city guard" + "&&"
							+ "loose" + "&&"
							+ "white" + "&&"
							+ "linen" + "&&"
							+ "pants");
	gpants->move(TO);

	// Guard's standard issue boots.
	clone_object(OBJ + "garmour_boots")->move(TO);

	// Guard's custom body armour.
	clone_object(OBJ + "garmour_" + whichbody)->move(TO);

	command("wield all");
	command("wear all");
}

void
arm_me2()
{
	command("wield all");
	command("wear all");
}

string
constable_symbol()
{
	return "a symbol of an upturned sword over the white palatial tower";
}

void
attack_func(object enemy)
{
    if ( !CAN_SEE(TO, enemy) )
        return;
    
    command("shout Miscreant! Employ force!");
    action_attack(enemy);
}

void
init_living()
{
    init_team_pickup();
    ::init_living();

	if (TP->query_prop(LIVE_I_ATTACKED_PALANTHAS) == 1)
    {
        set_alarm(0.5, 0.0, &attack_func(TP));
        return;
    }

}

void
attacked_by(object ob)
{
	ob->add_prop(LIVE_I_ATTACKED_PALANTHAS, 1);
	command("close door");
	command("say You'll end this battle in jail or in a body bag.  Drop your "
	+ "weapons if you'd prefer a simpler solution.");

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
		case W_POLEARM:
			attack = "catch";
			damtype = W_IMPALE;
			hitloc = "body";
			wloc = A_TORSO;
			break;
		case W_SWORD:
			attack = "pierce";
			damtype = W_IMPALE;
			hitloc = "body";
			wloc = A_TORSO;
			break;
		case W_CLUB:
			attack = "clobber";
			damtype = W_BLUDGEON;
			hitloc = "head";
			wloc = A_HEAD;
			break;
		default:
			attack = "strike";
			damtype = W_SLASH;
			hitloc = "legs";
			wloc = A_LEGS;
			break;
	}

    if (random(6) == 1)
    {
		pen = 25 + random(100);
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
			how = "incapacitating you slightly";
			how2 = "incapacitating " + HIM(enemy) + " slightly";
		}
		if(hitres[0] > 20)
		{
			how = "incapacitating you greatly";
			how2 = "incapacitating " + HIM(enemy) + " greatly";
		}
		if (hitres[0] > 40)
		{
			how = "with well-trained power";
			how2 = how;
		}
		if (hitres[0] > 60)
		{
			how = "with deadening force";
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
