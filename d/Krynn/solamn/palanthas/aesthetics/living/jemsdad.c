/* 
 * Poor family member in houses around Jems Court
 * in the Aesthetics quarter of Palanthas.
 *
 * Mortis 09.2006
 *
 */

#include "../../local.h"
#include <macros.h>
#include <money.h>
#include <ss_types.h>
#include <wa_types.h>
#include <formulas.h>
#include <language.h>

// Three types:  man, woman, child
#define WHAT_BRIX_AM_I		"_what_brix_citizen_am_i"
// Dozens of occupations listed in jemsdad.
#define WHAT_OCCU_AM_I		"_what_palanthas_occupation_am_i"

inherit BCITIZEN;

/*prototype*/
string my_short();
string my_title();
void arm_me();

int gender = G_MALE;
string adj1 = one_of_list(({"thin", "hollow-cheeked", "weary", "strong",
		"hard-working", "smiling", "proud", "tall", "short", "solemn"})),
	   adj2 = one_of_list(({"bearded", "side-burned", "simply-dressed",
		"pony-tailed", "short-haired", "moustachioed", "clean-cut",
		"nervous", "tanned", "pale", "clean-shaven"})),
	   myname = one_of_list(({"krig", "mick", "ayb", "arkod", "belgen",
	   "cam", "denin", "eyric", "ferdinus", "gaorg", "henrus", "ikrador",
	   "jo", "kardamis", "luongo", "nygus", "ophen", "parly", "qvis",
	   "robis", "stefyn", "tem", "ungrou", "vidius", "willis", "yon"})),
	   myshort, mytitle, myocc;

void
create_brix_citizen()
{
    seteuid(getuid(TO));

	myshort = my_short();
	mytitle = my_title();

	set_name(myname);
	add_name(({"man", "_brix_citizen"}));
	set_adj(adj1);
	add_adj(({adj2}));
	set_gender(gender);
	set_short(myshort);
	set_long("Dressed in simple, worn clothing, this " + adj1 + " " + adj2
	+ " man rests proudly in his home.\n");
	set_race_name("human");
	set_title(mytitle);
	
	set_skill(SS_DEFENCE,      10);
	set_skill(SS_UNARM_COMBAT,  5);
	set_skill(SS_AWARENESS,     5);
	set_skill(SS_WEP_CLUB,     10);
	set_skill(SS_WEP_KNIFE,     5);

	set_stats((({22, 14, 30, 17, 19, 18})), 50);

	set_size_descs("tall", "lean");
	set_appearance(1);

	set_alignment(600);
	set_knight_prestige(-5);
	set_introduce(1);
	add_prop(WHAT_BRIX_AM_I, "man");
	add_prop(WHAT_OCCU_AM_I, myocc);

    set_default_answer("@@def_answer");
	add_ask(({"city", "palanthas"}), "asay thoughtful Life is fair in the "
	+ "city for the most part.  The marble city is the queen of cities, a "
	+ "very beautiful place to live even if this isn't the best "
	+ "neighborhood.", 1);
	add_ask(({"neighborhood", "hood", "court", "jems", "jems court"}),
	"asay sullen The court, though regal generations ago, is over packed "
	+ "with crumbling tenements and lorded over by a gang.", 1);
	add_ask(({"gang", "brix"}), "asay nervous The Brix gang runs the back "
	+ "alleys of the court.  Their leader has made a headquarters there, "
	+ "and I also hear they run onjat games in the tunnels.", 1);
	add_ask(({"leader", "headquarter", "headquarters"}), "asay specul "
	+ "I've heard it's in the east end, but you don't want to go there "
	+ "unless you're looking for trouble.  We don't even see the constable "
	+ "around here.", 1);
	add_ask(({"onjat", "gambling", "game", "games"}), "asay uncomfort "
	+ "They say the Brix gang runs onjat games in the tunnels of the back "
	+ "alleys, but I don't go there.  My family and I don't want trouble.",
	1);
	add_ask(({"tunnel", "tunnels", "sewer", "sewers"}), "asay uninterest "
	+ "There are tunnel access points to the underground sewers all over "
	+ "the city.  It's said there's one in the back alleys of the court.", 1);
	add_ask(myocc, "asay sober It's what I do.", 1);

	set_alarm(1.0, 0.0, arm_me);
}

string
my_short()
{
	string gend = "male";

	if (gender == G_FEMALE)
		gend = "female";

	myshort = adj1 + " " + adj2 + " man";
	return myshort;
}

string
my_title()
{
	string via = one_of_list(({"Jems court", "Jems court", "Aesthetics row",
	"Darborough street", "Palanthas circle", "Old Circle", "the aesthetics "
	+ "quarter", "Qualus court", "Vingaard road", "Knights High road",
	"Stone street", "Marbled way", "Brownbrick"}));
	myocc = one_of_list(({"baker", "cook", "fletcher", "cobbler's assistant",
	"smith's apprentice", "blacksmith", "lumberjack", "peat dryer",
	"locksmith's apprentice", "stable man", "street cleaner", "hawker",
	"tailor", "teamster", "roadman", "fishmonger", "fisherman", "crabber",
	"miner", "mason", "stonecutter", "smelter", "unemployed citizen"}));

	mytitle = "the " + myocc + " of " + via;
	return mytitle;
}

string
def_answer()
{
	command("emote peers about in concern.");
    command("asay tight We don't want any trouble here.");
    return "";
}

void
arm_me()
{
	if (random(3) == 1)
		MONEY_MAKE_SC(random(5))->move(TO);

	MONEY_MAKE_CC(12 + random(20))->move(TO);
}
