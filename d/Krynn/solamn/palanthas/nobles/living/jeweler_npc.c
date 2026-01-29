/*
 * I think this was an existing, non-descript jeweler.
 * I rewrote him.
 * 
 * Mortis 06.2005
 *
 * Updated along with jeweler guard system.
 *
 * Mortis 10.2006
 * (Try to remember who Enjasa is and what quest you had
 *  planned.  Wife?  Daughter?  She lives upstairs if I recall.
 *  Was she into the parfumist?)
 */
#include "../../local.h"
#include <macros.h>
#include <money.h>
#include <ss_types.h>
#include <wa_types.h>
#include <formulas.h>
#include <language.h>

#define LIVE_I_ATTACKED_PAL_JEWELER		"_live_i_attacked_palanthas_jeweler"

inherit CITIZEN;

// Prototypes
void arm_me();
int my_steal();
string my_cacts();

int alarm_id;

void
create_krynn_monster()
{
    seteuid(getuid(TO));

	set_name("pennington");
	set_living_name("pennington");
	add_name(({"harnoncourt", "human", "lapidary", "lapidarian",
			   "pennington"}));
	set_race_name("human");
	set_gender(G_MALE);
	set_title("Harnoncourt, Lord Lapidarian of the Nobility of Palanthas");
	set_introduce(1);
	set_adj("old");
	add_adj("bushy-eyebrowed");
	set_short("old bushy-eyebrowed male human");
	set_long("Though clean-shaven, the old man's chin is still rough and "
	+ "stubbly.  He has short, white hair, a lock of which is hanging "
	+ "in his eyes, and bushy, white eyebrows.  He wears a thin, dark "
	+ "leather apron over a pale green shirt and dark brown corduroys.  "
	+ "From his neck dangles a thick, monocle looking device.\n");

	set_size_descs("of normal length", "of normal width");
	set_appearance(1);

    set_default_answer("@@def_answer");

	set_act_time(7);
	add_act("emote pushes a lock of white hair from his eyes.");
	add_act("emote frowns perturbedly as he pushes a lock of white hair "
	+ "back out of his eyes.");
	add_act("emote exhales dejectedly as a lock of white hair falls into "
	+ "his eyes.");
	add_act("emote studies a " + "@@monocle_it@@" + " with his thick, "
	+ "monacular device.");
	add_act("asay inq May I help you find what you seek?");
	add_act("asay helpful Looking for the perfect stone for that special "
	+ "someone?");
	add_act("asay wear In the beginning things were not quite as they are "
	+ "now.");
	add_act("emote looks confused as he rummages slowly through his "
	+ "pockets.");
	add_act("emote raises his bushy, white eyebrows as he places his hand "
	+ "over his pocket.");
	add_act("ponder what Enjasa is doing with her life.");
	add_act("emote coughs raspily.");
	add_act("emote rubs his eyes in an attempt to wipe away his weariness.");
    
    set_cact_time(10);
	add_act("@@my_cacts");

	set_all_hitloc_unarmed(60);

	set_stats(({ 50, 50, 100, 50, 50, 50}));

	set_skill(SS_UNARM_COMBAT, 50);
	set_skill(SS_DEFENCE,      65);
	set_skill(SS_AWARENESS,    50);
	add_prop(NPC_I_NO_RUN_AWAY, 1);
	add_prop(LIVE_I_ATTACK_THIEF, my_steal);

	set_alignment(700);
	set_knight_prestige(-10);

	set_alarm(1.0, 0.0, arm_me);
}

string
def_answer()
{
	command("asay formal Well, have a look around, please.");
	return "";
}

void
arm_me()
{
	MONEY_MAKE_PC(random(3))->move(TO);
	MONEY_MAKE_GC(24 + random(37))->move(TO);
}

string
monocle_it()
{
	string gem;

	gem = one_of_list(({"small, yellow diamond",
	  "long, thin emerald", "glossy, white pearl", "rough, red garnet",
	  "long crystal", "dark, green jadestone", "red ruby",
	  "pale, blue opal", "orange-red flamestone"}));

	return gem;
}

string
my_cacts()
{
    add_cact("emote reaches for something beneath the counter.\nHe cries:  "
	+ "Let's see how they like the breath of the green dragon!");
	add_cact("asay question Oh, Paladine, no!  Why?!?");
	add_cact("shout Guards!  What... what is happening?!?");
	add_cact("emote cries out:  Oh gods help me!  Help!");
	add_cact("emote sputters feebly.");
}

void
attacked_by(object ob)
{
	object jshop = E(TO);

	if (random(2) == 1)
		command("shout You think I can't afford to have you killed?!?");
	
	ob->add_prop(LIVE_I_ATTACKED_PAL_JEWELER, 1);

	jshop->rescue_employer_room(ob);

    ::attacked_by(ob);
}

int
my_steal()
{
	string tname = L(TP->query_name());
	object mystore = E(TO);

	TP->add_prop(LIVE_I_ATTACKED_PAL_JEWELER, 1);

	command("shout Guards!  A thief!");
	mystore->react_steal(tname);

	return 0;
}
