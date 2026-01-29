/*
 * Fatigue poison dagger used occasionally by Kirk,
 * leader of the Brix gang on Jems Court in the
 * aesthetics quarter of Palanthas.
 *
 * Mortis 06.2006
 * 
 */

inherit "/std/weapon.c";
inherit "/lib/keep.c";

#include <stdproperties.h>
#include <wa_types.h>
#include <ss_types.h>
#include <formulas.h>
#include <macros.h>
#include <poison_types.h>
#include "../../local.h"

// Prototypes
void add_the_crust();

static int poisons_left = 3;

void
create_weapon()
{
    seteuid(getuid(TO));

	set_name("knife");
	add_name("knife");
	set_adj("grensh");
	add_adj(({"black-handled", "black", "handled"}));
	set_short("black-handled grensh knife");
	set_long("@@my_long");
	
	add_the_crust();

	set_hit(14);
	set_pen(20);
	set_wt(W_KNIFE);
	set_dt(W_IMPALE | W_SLASH);
	set_hands(W_ANYH);
}

string
my_long()
{
	string mylong = "With a wavy-sharpened edge to its curving blade, this "
	+ "grensh knife is the sort favoured by blood sea pirates.  Almost large "
	+ "enough to be a short sword, it appears capable of deep wounds";
	
	if (poisons_left <= 0)
		return mylong + ".\n";

	if (poisons_left >= 3)
		return mylong + ", and its wavy edge is coated in a thick, dark "
		+ "brown crust.\n";

	if (poisons_left == 2)
		return mylong + ", and its wavy edge is coated in a thin, dark "
		+ "brown crust.\n";

	if (poisons_left == 1)
		return mylong + ", and upon its wavy edge are a few spots of dark "
		+ "brown crust.\n";
}

void
add_the_crust()
{
	switch (poisons_left)
	{
		case 3:
			add_item("crust", "The wavy edge of the grensh knife has been "
			+ "coated with a thick, dark brown crust that appears to have "
			+ "been brushed on when still a viscous resin.\n");
			break;
		case 2:
			add_item("crust", "The wavy edge of the grensh knife has been "
			+ "coated with a thin, dark brown crust that appears to have "
			+ "been brushed on when still a viscous resin.\n");
			break;
		case 1:
			add_item("crust", "The wavy edge of the grensh knife has been "
			+ "coated with a thin, dark brown crust that appears to have "
			+ "been brushed on when still a viscous resin.  Most of it has "
			+ "been wiped off except a few spots here and there.\n");
			break;
		default:
			break;
	}
}

public varargs int
did_hit(int aid, string hdesc, int phurt, object enemy, int dt, int phit)
{
	int duration = 300 + random(61);
	string howhit = "stab", howhit2 = "into", iwho = QTNAME(enemy),
		myshort = short();
	object my_poison, iwield = query_wielded();

	if (phurt <= 1)
        return 0;

	if (poisons_left <= 0)
		return 0;

	poisons_left--;
	remove_item("crust");
	add_the_crust();

	my_poison = clone_object("/std/poison_effect");
	my_poison->set_time(duration);
	my_poison->set_interval(19);
	my_poison->set_strength(57);
	my_poison->set_damage(({POISON_FATIGUE, 107}));
	my_poison->move(enemy);
	my_poison->start_poison();

	log_file("curses", enemy->query_name() + " was poisoned with "
	+ my_poison->query_poison_type() + " by " + query_wielded()->query_name()
	+ ", using a " + short() + ". " + ctime(time()) + ".\n");

	if (dt == W_SLASH)
	{
		howhit = "slice";
		howhit2 = "across";
	}

	iwield->catch_msg("You " + howhit + " your " + myshort + " " + howhit2
	+ " the " + hdesc + " of " + iwho + " leaving a bit of dark brown resin "
	+ "behind in the wound.\n");
	enemy->catch_msg(QCTNAME(iwield) + " " + howhit + "s " + HIS(iwield)
	+ " " + myshort + " " + howhit2 + " your " + hdesc + " leaving a bit of "
	+ "dark brown resin behind in the wound.\n");

	return 0;
}

public string
query_recover()
{
    return MASTER + ":" + query_wep_recover() + "#p_u#" + poisons_left;
}

public void
init_recover(string arg)
{
    init_wep_recover(arg);
    sscanf(arg, "%s#p_u#%d", poisons_left);

	switch (poisons_left)
	{
		case "0":
			poisons_left = 0;
			break;
		case "1":
			poisons_left = 1;
			break;
		case "2":
			poisons_left = 2;
			break;
		default:
			poisons_left = 3;
			break;
	
	}
}

int
query_doses()
{
	return poisons_left;
}
