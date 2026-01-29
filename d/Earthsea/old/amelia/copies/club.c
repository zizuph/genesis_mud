/* a club for fallogre McCram june/97 */
inherit "/std/weapon";

#include "/sys/stdproperties.h"
#include "/sys/wa_types.h"
#include "/sys/formulas.h"
#include "/sys/macros.h"

#define WEAPON_HIT 30
#define WEAPON_PEN 40
#define TP   this_player()

void
create_weapon()
{
	set_name("branch");
	set_pname("branches");
	add_name("club");

	set_adj("knarled");

	set_short("knarled branch");

	set_long(break_string("Torn from right next to the " +
		"trunk of a tree, this thick branch has become " +
		"knarled and battered from use. The stumps of " +
		"smaller branches create spikes sticking out from " +
		"the sides." +
                "\n", 75));

	set_hit(WEAPON_HIT);
	set_pen(WEAPON_PEN);
	set_wt(W_CLUB);
	set_dt(W_BLUDGEON);
	set_hands(W_BOTH);

	add_prop(OBJ_I_WEIGHT, 16000);
	add_prop(OBJ_I_VOLUME, 10000);
        add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(5,5));
}

mixed
wield(object ob)
{
	if(this_player()->query_base_stat(SS_STR) < 60)
	{
		return "You don't have the strength to control " +
		   "the branch as a weapon.\n";
	}
	else
	{
		write("You take a firm grip on the branch.\n");
		return 1;
	}
}

mixed
unwield(object what)
{
	write("You let the branch drop from your hands.\n");
	return 1;
}

int
did_hit(int aid, string hdesc, int phurt,
		object enemy, int dt, int phit, int dam)
{

	::did_hit();

	if((!(random(5))) && (dam >= 0))
	{
		switch(random(6)+1)
		{
			case 1:
				write("A chip of bark flies off the branch.\n");
				break;
			case 2:
				write("Splinters from the branch spray out.\n");
				break;
			case 3:
				write("A knob on the branch cracks off.\n");
				break;
			case 4:
				write("The very end of the branch " +
					"makes a large crack.\n");
				break;
			case 5:
				write("The whole branch shivers.\n");
				break;
			case 6:
				write("A round of bark strips away " +
					"from the branch.\n");
		}
	}

	return 0;
}

/*
 * In order to make your weapon recover through a reboot, just add the
 * following code to it and don't forget to #include <macros.h> like I
 * did on top.
 */

string
query_recover()
{
    return MASTER + ":" + query_wep_recover();
}

void
init_recover(string arg)
{
    init_wep_recover(arg);
}
