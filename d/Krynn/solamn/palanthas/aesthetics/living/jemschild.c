/*
 * Poor family member in houses around Jems Court
 * in the Aesthetics quarter of Palanthas.
 *
 * Mortis 09.2006
 *
 */

/* Navarre August 28th 2011, fixed typo in my_short() function.
 * gender == G_FEMALE, should be gender = G_FEMALE.
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

int gender;
string adj1 = one_of_list(({"thin", "rosy-cheeked", "skinny", "cheery",
		"young", "smiling", "baby-faced", "lanky", "short", "dirty-nosed"})),
	   adj2 = one_of_list(({"little", "chubby", "simply-dressed",
		"pony-tailed", "short-haired", "long-haired", "humming",
		"fearful", "smooth-skinned", "pale", "rough-skinned"})),
	   myshort, myname;

void
create_brix_citizen()
{
    seteuid(getuid(TO));

    myshort = my_short();

    set_name(myname);
    add_name(({"child", "_brix_citizen"}));
    set_adj(adj1);
    add_adj(({adj2}));
    set_short(myshort);
    set_gender(gender);
    set_long("Dressed in simple, worn clothing, this " + adj1 + " " + adj2
      + " " + myname + " plays around the house.\n");
    set_race_name("human");
    
    set_skill(SS_AWARENESS,     3);

    set_stats((({10, 12, 15, 12, 10, 10})), 30);
    set_size_descs("short", "lean");
    set_appearance(2);

    set_alignment(600);
    set_knight_prestige(-6);

    add_prop(WHAT_BRIX_AM_I, "child");
    add_prop(WHAT_OCCU_AM_I, "child");

    set_default_answer("@@def_answer");
    add_ask(({"play", "game"}), "asay happi Ok, let's play a game, poo-poo "
      + "face!", 1);
}

string
my_short()
{
	if (random(2) == 1)
	{
		myname = "boy";
		gender = G_MALE;
	}
	else
	{
		myname = "girl";
		gender = G_FEMALE;
	}

	myshort = adj1 + " " + adj2 + " " + myname;
	return myshort;
}

string
def_answer()
{
    command("asay question Are you a ka-ka poo-poo?");
    return "";
}
