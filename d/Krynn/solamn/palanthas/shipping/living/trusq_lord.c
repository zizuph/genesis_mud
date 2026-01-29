/* 
 * Mortis 03.2006
 *
 * Merchant house Trusq Lord.
 *
 * Defended by bodyguard, but calls high guard when attacked.
 */

#include "../../local.h"
#include <macros.h>
#include <money.h>
#include <ss_types.h>
#include <wa_types.h>
#include <formulas.h>
#include <language.h>

#define HIGH_GUARDROOM				(SHIP + "trusq_priv_guardroom")

inherit M_FILE
inherit AUTO_TEAM

object guardhome;

/*prototype*/
void arm_me();
string my_cact();

void
create_krynn_monster()
{
    seteuid(getuid(TO));

	set_name("bojksla");
	set_living_name("bojksla");
	add_name(({"trusq", "lord", "merchant"}));
	set_adj("balding");
	add_adj(({"trimly-bearded"}));
	set_gender(G_MALE);
	set_short("balding trimly-bearded male merchant");
	set_long("Youthful and in fair shape for a man in his late sixties, "
	+ "the lord of merchant house Trusq has a ring of white hair around "
	+ "his balding scalp and a well groomed and neatly trimmed white "
	+ "beard.  He has a thin nose, high eyebrows, and bright green eyes "
	+ "that don't miss a trick.\n"
	+ "He is wearing the thick, gold-chained medallion of merchant "
	+ "house Trusq.\n"
	+ "He is wearing a gold ring encircled by diamonds on his left finger "
	+ "and a pair of ornate gold bracelets.\n");
	set_race_name("human");
	set_title("Trusq, Lord of Merchant House Trusq");
	
	set_size_descs("of normal length", "of normal width");
	set_appearance(4);
	set_introduce(1);

	set_skill(SS_DEFENCE,      60);
	set_skill(SS_PARRY,        45);
	set_skill(SS_UNARM_COMBAT, 50);
	set_skill(SS_WEP_SWORD,    50);
	set_skill(SS_AWARENESS,    50);

	set_stats((({65, 50, 65, 130, 145, 100})), 4);
	set_all_attack_unarmed(50, 10);
	set_all_hitloc_unarmed(50);

	set_alignment(500);
	set_knight_prestige(-150);

    set_pick_up_team("guard");
    set_max_team_size_auto_join(5);

	add_ask(({"work", "accounting", "merchant", "house", "trusq"}), "say "
	+ "Merchant house Trusq is one of the oldest, most successful merchant "
	+ "houses in Palanthas.  My family keeps it that way.", 1);
	add_ask("palanthas", "say Palanthas is the busiest trade city in the "
	+ "realms.  Anyone willing to work for a living is assured of wealth "
	+ "here.", 1);
	add_ask("talk", "say What would you like to talk about?  The weather?",
	1);
	add_ask("weather", "say The weather bores me.  Why don't we talk about "
	+ "business?", 1);
	add_ask("business", "say Ahh, yes.  Direct and to the point.  I like "
	+ "that in a visitor.  I may have a proposition for a good businessman.",
	1);
	add_ask("proposition", "@@proposition");

	set_cact_time(5);
	add_cact("@@my_cact");

    set_default_answer("@@def_answer");

	set_alarm(1.0,0.0,"arm_me");
}

string
def_answer()
{
    command("say A visitor come to talk?  I don't recall allowing for any.  "
	+ "Who let you in here?");
    return "";
}

string
proposition()
{
	if (TP->query_prop(LIVE_I_ATTACKED_TRUSQ) == 1)
	{
		command("say I propose having you thrown in jail for murder!");
		return "";
	}

	command("say I propose having you thrown in jail for thievery!  How's "
	+ "that for a proposition?");
	return "";
}

void
arm_me()
{
	object tbelt = clone_object(MERCH + "arms/larmour");
	tbelt->set_armour_data("noble" + "&&" + "yellow" + "&&" + "hard" + "&&"
							+ "belt");
	tbelt->move(TO);

	clone_object(SHIP + "arms/trusq_robe_lord")->move(TO);

	command("wear all");

	// Routine to make sure door is closed and locked on reset.
	object lkey = clone_object(SHIP + "obj/trusq_lord_key");
	lkey->move(TO);
	
	command("close door");
	command("lock door with key");

	lkey->remove_object();
}

void
init_living()
{
    init_team_pickup();
    ::init_living();
}

string
my_cact()
{
	object bedroom = E(TO);
	object *ene = TO->query_enemy(-1);

	if (!sizeof(ene))
		return "";

	HIGH_GUARDROOM->help_i_need_help(ene[0], bedroom);
	bedroom->rescue_lord_room(ene[0]);
	return "";
}

void
attacked_by(object ob)
{
	object bedroom = E(TO);

	ob->add_prop(LIVE_I_ATTACKED_TRUSQ, 1);

	if (!(guardhome = find_object(HIGH_GUARDROOM)))
		HIGH_GUARDROOM->load();

	HIGH_GUARDROOM->help_i_need_help(ob, bedroom);
	command("say What did you think?  That a Lord of a prominent merchant "
	+ "house cannot afford adequate protection?  What gall.  What laughable "
	+ "gall!");

	bedroom->rescue_lord_room(ob);

    ::attacked_by(ob);
}
