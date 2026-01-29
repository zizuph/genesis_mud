/* 
 * Low hobgoblin in caves along road south of Palanthas.
 *
 * Mortis 10.2006
 *
 */

#include "../local.h";
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>

inherit HOB;

// Prototype
int my_gender();
string my_short();
string adj1();
string adj2();
void arm_me();

int gender;
string adj1, adj2, myshort, gendstr;

public void
create_vin_hobgoblin()
{
    seteuid(getuid(TO));

	my_gender();
	adj1();
	adj2();
	my_short();

	set_name("hobgoblin");
	add_name(({"hob", "hobgob"}));
	set_adj(adj1);
	add_adj(({adj2}));
	set_gender(gender);
	set_short(myshort);
	set_long("@@my_long");
	set_race_name("hobgoblin");
	
	set_skill(SS_DEFENCE,      15 + random(16));
	set_skill(SS_UNARM_COMBAT, 35 + random(16));
	set_skill(SS_AWARENESS,    16 + random(10));
	set_skill(SS_WEP_CLUB,     35 + random(16));
	set_skill(SS_WEP_SWORD,    40 + random(16));
    set_skill(SS_BLIND_COMBAT, 30 + random(10));

	set_stats((({60, 45, 65, 25, 45, 60})), 16);

	set_alignment(100 - random(350));
	set_knight_prestige(5);

    set_default_answer("@@def_answer");

	add_ask(({"palanthas", "city"}), "grin hungr", 1);
	add_ask(({"hobgoblin", "hobgoblins", "cave", "caves", "roadway caver",
	  "roadway cavers"}), "asay rough Invaders of our home will be "
	+ "executed.", 1);

	set_act_time(45);
	add_act("get all");
	add_act("grin vicious");
	add_act("emote rolls a pair of crud-encrusted dice.");
	add_act("emote scratches its bristly beard.");
	add_act("asay excit A three!  Mine!");
	add_act("asay excit Damn, not another twelve!");

	set_cact_time(30);
	add_cact("get all");
	add_cact("laugh vicious");
	add_cact("asay rough The time for dying for you has come.");
	add_cact("asay rough The roadway cavers will roll over you like a well-"
	+ "oiled gnome-crakka!");
	add_cact("emote backhands you wickedly!");
	add_cact("emote stomps on you with an unexpectedly disciplined attack!\n"
	+ "You feel crushed!");

	set_alarm(1.0, 0.0, "arm_me");
}

string
adj1()
{
	adj1 = one_of_list(({"bristly-bearded", "bristle-bearded",
		"large-mouthed", "hulking", "straight-backed", "barrel-chested",
		"rough", "rope-muscled", "musclebound"}));
	return adj1;
}

string
adj2()
{
	adj2 = one_of_list(({"sneering", "skulking", "bushy-haired",
		"large-jawed", "smash-nosed", "potato-faced", "dark",
		"dark-skinned"}));
	return adj2;
}

int
my_gender()
{
	gender = G_MALE;

	if (random(9) == 1 && adj1 != "bristly-bearded" && adj1 != "bristle-bearded")
		gender = G_FEMALE;

	return gender;
}

string
my_short()
{
	gendstr = "male";

	if (gender == G_FEMALE)
		gendstr = "female";

	myshort = adj1 + " " + adj2 + " " + gendstr + " hobgoblin";
	return myshort;
}

string
my_long()
{
	string beard = "thick, bristly black beard";

	if (gendstr == "female")
		beard = "flat, lumpy face";

	return "With vividly dark forest-green skin and a " + beard + ", this "
	+ "hobgoblin marches about with an unexpected discipline.  Standing "
	+ "nearly a foot above the average human, " + HIS(TO) + " thick, ropey "
	+ "muscles bunch up and flex occasionally as " + HE(TO) + " moves.\n";
}

string
def_answer()
{
    command("shout Get off me, weakling!");
    return "";
}

void
arm_me()
{
	if (gender == G_FEMALE)
		return;

	string mywep = "hob_" + one_of_list(({"hammer", "sword"}));

	clone_object(OBJ + mywep)->move(TO);

	command("wield all");
}

int
special_attack(object enemy)
{
    int pen, att, wloc, damtype = W_BLUDGEON;
    string hitloc, how, how2, weapon;
    mixed hitres;
	object *wep = query_weapon(-1);

	// Requires weapon.  Only goes off 10%.
    if (!sizeof(wep) || random(9) != 1)
		return 0;

    weapon = wep[0]->query_short();

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
		default:
			hitloc = "legs";
			wloc = A_LEGS;
			break;
	}

	pen = 30 + random(50);
	hitres = enemy->hit_me(pen, damtype, TO, -1, wloc);

	if (hitres[0] <= 0)
	{
		how = "but misses";
		how2 = how;
	}
	if(hitres[0] > 0)
	{
		how = "barely clunking";
		how2 = how;
	}
	if(hitres[0] > 10)
	{
		how = "with a clunk";
		how2 = how;
	}
	if(hitres[0] > 20)
	{
		how = "with a thudding clunk";
		how2 = how;
	}
	if (hitres[0] > 40)
	{
		how = "battering you resoundingly";
		how2 = "battering " + HIM(enemy) + " resoundingly";
	}
	if (hitres[0] > 60)
	{
		how = "battering you devastatingly";
		how2 = "battering " + HIM(enemy) + " devastatingly";
	}

	enemy->catch_msg(QCTNAME(TO) + " attempts to crush your "
	+ hitloc + " with " + HIS(TO) + " " + weapon + " " + how + ".\n");

	tell_room(E(TO), QCTNAME(TO) + " attempts to crush "
	+ QTNAME(enemy) + "'s " + hitloc + " with " + HIS(TO) + " " + weapon
	+ " " + how2 + ".\n", ({enemy, TO}));

	if (enemy->query_hp() <= 0)
		enemy->do_die(TO);

	return 1;
}

