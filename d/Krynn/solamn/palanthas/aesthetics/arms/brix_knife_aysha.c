/*
 * Infected knife used by Aysha of the Brix behind Jems court
 * in the Aesthetics quarter of Palanthas.
 *
 * Mortis 05.2006
 *
 */

inherit "/std/weapon";
inherit "/lib/keep";

#include "../../local.h"
#include <wa_types.h>
#include <macros.h>

#define INFECT_FILE		MONKS + "obj/brix_infection"

static int infections_left = 3;

create_weapon()
{
    seteuid(getuid(TO));

	set_name("longknife");
	add_name("knife");
	set_adj("rusty");
	add_adj(({"wicked", "long"}));
	set_short("rusty wicked longknife");
	set_long("@@my_long");

	set_hit(17);
	set_pen(14);
	set_wt(W_KNIFE);
	set_dt(W_IMPALE | W_SLASH);
	set_hands(W_ANYH);
}

string
my_long()
{
	string mylong = "Though once a gleaming grensh knife of the sort "
	+ "favoured by blood sea pirates, this curving blade has been "
	+ "compromised by spots of rust on its sides and wavy-sharpened "
	+ "edge.";
	
	if (infections_left <= 0)
		return mylong + "\n";

	if (infections_left >= 3)
		return mylong + "  Several globs of nasty, greyish-green grime "
		+ "clot its blade.\n";

	if (infections_left == 2)
		return mylong + "  A few globs of nasty, greyish-green grime "
		+ "clot its blade.\n";

	if (infections_left == 1)
		return mylong + "  One or two globs of nasty, greyish-green grime "
		+ "clot its blade.\n";
}

public varargs int
did_hit(int aid, string hdesc, int phurt, object enemy, int dt, int
phit)
{
	string howhit = "stab", howhit2 = "into", iwho = QTNAME(enemy),
		myshort = short();
	object infection, iwield = query_wielded();

	if (phurt <= 1)
        return 0;

	if (infections_left <= 0)
		return 0;

	infections_left--;

	infection = clone_object(INFECT_FILE);
	infection->move(enemy);
	infection->start_poison();

	log_file("curses", enemy->query_name() + " was infected with "
	+ infection->query_poison_type() + " by " + query_wielded()->query_name()
	+ ", using a " + short() + ". " + ctime(time()) + ".\n");

	if (dt == W_SLASH)
	{
		howhit = "slice";
		howhit2 = "across";
	}

	iwield->catch_msg("You " + howhit + " your " + myshort + " " + howhit2
	+ " the " + hdesc + " of " + iwho + " leaving grime and rust behind "
	+ "in the wound.\n");
	enemy->catch_msg(QCTNAME(iwield) + " " + howhit + "s " + HIS(iwield)
	+ " " + myshort + " " + howhit2 + " your " + hdesc + " leaving grime and "
	+ "rust behind in the wound.\n");

	return 0;
}

public string
query_recover()
{
    return MASTER + ":" + query_wep_recover() + "#p_u#" + infections_left;
}

public void
init_recover(string arg)
{
    init_wep_recover(arg);
    sscanf(arg, "%s#p_u#%d", infections_left);

	switch (infections_left)
	{
		case "0":
			infections_left = 0;
			break;
		case "1":
			infections_left = 1;
			break;
		case "2":
			infections_left = 2;
			break;
		default:
			infections_left = 3;
			break;
	
	}
}

public void
set_doses(int i)
{
    infections_left = i;
}

public int query_doses()
{
	return infections_left;
}
