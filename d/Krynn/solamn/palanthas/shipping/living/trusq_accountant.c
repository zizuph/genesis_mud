/* 
 * Mortis 03.2006
 *
 * Merchant house Trusq accountant/office worker.
 *
 * Call constable when attacked?
 */

#include "../../local.h"
#include <macros.h>
#include <money.h>
#include <ss_types.h>
#include <wa_types.h>
#include <formulas.h>
#include <language.h>

inherit M_FILE

/*prototype*/
int my_gender();
string my_short();
string adj1();
string adj2();
void arm_me();

int gender;
string adj1, adj2, myshort, profession;

void
create_krynn_monster()
{
    seteuid(getuid(TO));

	my_gender();
	adj1();
	adj2();
	my_short();

	set_name("accountant");
	add_name("worker");
	set_adj(adj1);
	add_adj(({adj2, "office"}));
	set_gender(gender);
	set_short(myshort);
	set_long("Nicely robed and groomed, this " + profession + " is busy "
	+ "at work keeping the affairs of merchant house Trusq in order.  "
	+ C(HE(TO)) + " is certified by the bureaumancy to perform " + profession
	+ " duties.\n");
	set_race_name("human");
	
	set_skill(SS_AWARENESS, 20);

	set_stats((({35, 40, 35, 50, 45, 40})), 10);

	set_alignment(300);
	set_knight_prestige(-20);

	add_ask(({"work", "accounting", "merchant", "house", "trusq"}), "say "
	+ "Merchant house Trusq is one of the oldest, most successful merchant "
	+ "houses in Palanthas.  I help keep their affairs in order.", 1);
	add_ask("palanthas", "say Palanthas is the busiest trade city in the "
	+ "realms.  Anyone with a nose for business is assured of wealth here.",
	1);

    set_default_answer("@@def_answer");

	set_alarm(1.0,0.0,"arm_me");
}

string
adj1()
{
	adj1 = one_of_list(({"harried", "expressionless", "busy", "joyous",
	"frazzled"}));
	return adj1;
}

string
adj2()
{
	adj2 = one_of_list(({"blond-haired", "black-haired", "bushy-haired",
	"brown-haired", "thick-robed", "short-haired", "old", "middle-aged"}));
	return adj2;
}

int
my_gender()
{
	gender = one_of_list(({G_MALE, G_MALE, G_FEMALE}));
	return gender;
}

string
my_short()
{
	string gend = "male";
	profession = one_of_list(({"office worker", "accountant"}));

	if (gender == G_FEMALE)
		gend = "female";

	myshort = adj1 + " " + adj2 + " " + gend + " " + profession;
	return myshort;
}

string
def_answer()
{
    command("say I am much too busy keeping the affairs of merchant house "
	+ "Trusq in order to attend to that.");
    return "";
}

void
arm_me()
{
	MONEY_MAKE_GC(3 + random(3))->move(TO);
	MONEY_MAKE_SC(9 + random(6))->move(TO);
}

void
attacked_by(object ob)
{
	ob->add_prop(LIVE_I_ATTACKED_TRUSQ, 1);

	if (random(7) == 1)
		command("emote hands a missive to a young boy and says:  Let the "
		+ "constabulary know of this attack!");
	else
		command("say Service and honour.");

    ::attacked_by(ob);
}
