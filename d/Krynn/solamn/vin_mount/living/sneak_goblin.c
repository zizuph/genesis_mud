/* 
 * Sneaky goblin guard in a cave along the road
 * south of Palanthas.
 *
 * Mortis 11.2006
 *
 */

#include "../local.h";
#include <macros.h>
#include <money.h>
#include <ss_types.h>
#include <wa_types.h>
#include <formulas.h>
#include <language.h>

#define SGHOME						CAVE + "cave04"

inherit M_FILE

// Prototypes
string def_answer();
string return_home();

object myhome = find_object(SGHOME);

void
create_krynn_monster()
{
    seteuid(getuid(TO));

	set_name("goblin");
	set_adj("wiry");
	add_adj(({"hunched"}));
	set_gender(G_MALE);
	set_short("wiry hunched male goblin");
	set_long("Well armed for a goblin, he is hunched over almost into a "
	+ "crouch.  His flat, blackish-green face is split by a wide, needle "
	+ "toothed grin.  His eyes flash too knowingly for his kind as he "
	+ "peers about deviously.\n");
	set_race_name("goblin");
	
	set_skill(SS_DEFENCE,      55 + random(16));
	set_skill(SS_AWARENESS,    31 + random(10));
	set_skill(SS_WEP_CLUB,     35 + random(16));
	set_skill(SS_WEP_SWORD,    35 + random(16));
	set_skill(SS_WEP_KNIFE,    40 + random(10));
	set_skill(SS_2H_COMBAT,    45);
    set_skill(SS_BLIND_COMBAT, 30 + random(10));
	set_skill(SS_BACKSTAB,     35);
	set_skill(SS_SNEAK,        45 + random(16));
	set_skill(SS_HIDE,         40 + random(16));

	set_stats((({50, 80, 55, 35, 50, 55})), 16);

	set_alignment(0 - random(350));
	set_knight_prestige(5);

    set_default_answer("@@def_answer");

	add_ask(({"palanthas", "city"}), "grin sly", 1);
	add_ask(({"hobgoblin", "hobgoblins", "cave", "caves", "roadway caver",
	  "roadway cavers"}), "asay rough Invaders of our home will be "
	+ "executed.", 1);

	set_act_time(10);
	add_act(return_home);

	set_cact_time(45);
	add_cact("get all");
	add_cact("chuckle evil");
	add_cact("asay acid The time for dying for you is now.");
	add_cact("asay quiet The roadway cavers have paid well for your death.");
	add_cact("emote backhands you sneakily!");
	add_cact("emote stomps on you with an unexpected display of speed!\n"
	+ "You feel weakened!");

	set_alarm(1.0, 0.0, "arm_me");
}

string
def_answer()
{
    command("smile myst");
    return "";
}

void
arm_me()
{
	if (random(2) == 1)
		clone_object(OBJ + "hob_sword")->move(TO);
	else
		clone_object(OBJ + "hob_hammer")->move(TO);

	clone_object(HOBGOBLIN_KNIFE)->move(TO);
	clone_object(OBJ + "sgoblin_coat")->move(TO);
	clone_object(PARENT + "palanthas/obj/garmour_boots")->move(TO);

	command("wield all");
	command("wear coat");
	set_alarm(1.0, 0.0, "arm_me2");
}

void
arm_me2()
{
	command("wear boots");
}

void
attacked_by(object ob)
{
	ob->add_prop(LIVE_I_ATTACKED_SOL_HOBS, 1);

    ::attacked_by(ob);
}

string
return_home()
{
	if (E(TO) != myhome)
		move_living("slipping behind a crack in the wall", myhome, 1, 0);

	command("hide");
	return "";
}

void
go_on_attack()
{
	command("backstab it with dagger");
	set_alarm(1.5, 0.0, "go_on_attack2");
}

void
go_on_attack2()
{
	command("sneak east");
}
