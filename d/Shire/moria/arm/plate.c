/*
 * Durin's mithril coat. The coat which was originaly crafted for
 * King Durin the 7'th. It is worn over your shoulders, and it protects
 * A_BODY, A_ARMS. It is magical mithril, very light, and gives protection
 * against fire, acid and electricity. The coat can only be worn by 
 * small people, like gnomes, hobbits and dwarves. (Might change)
 * It drains a little mana when you wear it. It is enchanted, and it 
 * gives a little extra protection against slashing and impaling arms.
 *
 * The wearer will lower his dexterity when this plate is worn
 * and i will lower it with about 1/10 of his total dex.
 */

inherit "/std/armour";

#include "/d/Shire/common/defs.h"
#include <formulas.h>
#include <wa_types.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>

#define OK_RACES ({ "gnomes", "hobbits", "dwarves" })
#define OK_ADJS  ({ "very small", "small" , "tiny", "skinny" })
#define GEM_TYPES ({ "ruby", "saphire", "ametyst" })
#define DEX_LOWER 30

mapping resistance;

int polished, dexlower;

#define ARMOUR_AC 39

create_armour()
{
	set_name("platemail");
	add_name(({"mail", "plate", "armour"}));
	set_pname("platemails");
	add_pname(({"mails", "plates", "armours"}));
	set_adj("@@my_adj@@");
	set_short("@@my_short@@");
	set_long("@@long_desc@@");
	set_ac(ARMOUR_AC);
	set_at(A_BODY | A_ARMS);
	//        Impale, slash, bludgeon
	set_am(({    3,     2,      -5   }));
	set_af(TO);

	add_prop(OBJ_I_WEIGHT, 4500 + random(500)); // 4.5 Kg's + random(500) 
												// since it is mithril.
	add_prop(OBJ_I_VALUE, (12*12*12*20) - random(600));
	add_prop(OBJ_I_VOLUME, 8000); // 8 Liters
/* Magical properties. Wizinfo/identify info/macigtypes/strength of magic. */
	add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1); // It is magical.
	add_prop(MAGIC_AM_MAGIC, ({40, "enchantment", 60,"spell-resistance" }));
	add_prop(MAGIC_AM_ID_INFO,
	({
		"This seems like a mighty platemail!\n", 1,
		"It protects your body and arms.\n", 4,
		"It is made of mithril and is enchanted. Only Dwarves, Hobbits and "+
		"Gnomes are able to use it.\n", 10,
		"It protects against fire, acid and electricity.\n", 40
	}));

	add_item(({"runes", "inscription", "text"}), "@@exa_runes@@");

    resistance = ([ MAGIC_I_RES_FIRE : 40,
		MAGIC_I_RES_ACID : 50,
		MAGIC_I_RES_MAGIC : 30 ]);

	polished = 0;

}

int *
query_slots()
{
	return ({ A_L_ARM, A_R_ARM, A_BODY });
}

int
query_magic_protection(mixed prop, object for_who)
{
	if (for_who == TO)
	return ::query_magic_protection(prop, for_who);
	else
	return resistance[prop];
}

int
wear(object to)
{
	object tp = ENV(to);

	if ((tp->query_race() != "hobbit") && 
		(tp->query_race() != "gnome") &&
		(tp->query_race() != "dwarf"))
	{
		NF("The platemail does not seem to fit you.\n");
		return 0;
	}

	if (tp->query_npc())
		dexlower = 20;
	else
		dexlower = 1 + random(DEX_LOWER);

	tp->add_magic_effect(to);
    write("You wear the "+short()+" around your shoulders.\n");
	ADD_STAT(tp,SS_DEX, dexlower);
	return 1;
}

int
remove(object to)
{
	object tp = query_worn();
	tp->remove_magic_effect(to);
	ADD_STAT(tp,SS_DEX, -dexlower);
	
}

string
exa_runes()
{
	if (polished && (ENV(TO)->query_skill(SS_LANGUAGE) > 50 || 
		ENV(TO)->query_race() == "dwarf"))
	return "The runes say: Durin's Platemail.\n";
	else
	return "You cannot seem to understand them.\n";
}
string
long_desc()
{
	object tp = ENV(TO);
    string text;

	if (polished)
	text =
		"This is a mithril platemail crafted by dwarves of Moria. It is "+
		"constructed with several layers of mithril, thus together giving "+
		"good protection. There is some words inscribed into the breast of the "+
		"plate. On the chest there are several holes, where there most likely "+
		"used to be gems inserted.\n";
	else
	text = 
		"This is a mighty coat of some unknown material, which is all "+
		"covered with blood. It appears to cover the body and arms of the "+
		"wearer. There is some inscription on the breast of the plate, but "+
		"it seems impossible to decipher it, as the blood is in the way. "+
		"It might help to clean it up a bit.\n";

	if (tp->query_race() == "dwarf")
	text += "You recognise this as one of the finest armours ever made. "+
		"Durin's Platemail. Forged in the depths of Moria by the most "+
		"skilled smiths ever to live.\n";

	return text;

}

void
init()
{
	::init();
	add_action("do_polish", "clean");
	add_action("do_connect", "connect");
}

string
my_short()
{
	if (polished)
		return "durin's platemail";
	else
		return "blood-stained platemail";
}

string
my_adj()
{
	if (polished)
		return "durins";
	else return "blood-stained";
}

int
do_polish(string str)
{
	NF("Clean what?\n");
    if (!str)
		return 0;

	NF("Clean what?The plate perhaps?\n");
    if (str != "plate" && str != "platemail")
		return 0;

	NF("The plate has already been cleaned and polished!\n");
	if (polished)
		return 0;

	write("You start to polish and clean the platemail.\n");
    set_alarm(7.0,0.0, "polish_more");

	return 1;
}

void
polish_more()
{
	write("As you wipe away the last piece of blood from the plate you "+
		"discover that this is truly a piece of craftmanship.\n");
	polished = 1;
	TO->set_ac(55);
}

query_recover()
{
    return 0;
}
