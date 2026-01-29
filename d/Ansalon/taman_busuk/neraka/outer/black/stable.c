/* Ashlar, 25 Jul 97 */

#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>
#include <money.h>
#include <cmdparse.h>
#include <composite.h>

inherit OUTER_IN;


#define STABLE_INTERNAL	NOUTER+"black/stable2"
mapping gHorse = ([ ]);

void
create_neraka_room()
{

    set_short("the Black Ship Inn");
	set_short("a stable");

	set_long("You are standing in a well-kept stable in Neraka. " +
		"A sign hangs on one wall, and there is an exit " +
		"leading out to a yard to the northwest. The floor " +
		"is covered with straw, and you can hear horses snorting.\n");
	
	add_item("sign","@@read_sign");
	add_cmd_item("sign","read","@@read_sign");

    add_item_inside();

	add_prop(ROOM_I_ALLOW_STEED,1);

	add_exit(NOUTER+"black/yard","northwest");

}

string
read_sign()
{
	return "For one silver coin, you may " +
	"<stable> your horse here, and <fetch> it later at " +
	"your leisure.\n";
}


int
do_stable(string arg)
{
	object *horses;
	string pn;
	NF("Stable what? Your horse perhaps?\n");
	if (!stringp(arg))
		return 0;
	horses = FIND_STR_IN_OBJECT(arg, TO);
	if (!sizeof(horses))
		return 0;
	NF("You can only stable one horse at a time.\n");
	if (sizeof(horses)>1)
		return 0;

	NF("You can only stable horses here!\n");
	if (!horses[0]->id("horse"))
		return 0;

	pn = TP->query_real_name();
	if (!pointerp(gHorse[pn]))
		gHorse += ([ pn : horses ]);
	else
		gHorse[pn] += horses;
	horses[0]->move_living("M",STABLE_INTERNAL);

	tell_room(TO, QCTNAME(TP) + " pays the stablehand, and he " +
	"leads the " + horses[0]->short() + " away.\n", TP);
	write("You pay the stablehand, and he leads the " +
		horses[0]->short() + " away.\n");
	return 1;
}

int
do_fetch(string arg)
{
	object *horses;
	string pn;
	int i;

	NF("Fetch what? Your horse perhaps?\n");
	if (!stringp(arg))
		return 0;

	if ((arg!="horse") && (arg!="my horse") && 
		(arg!="horses") && (arg!="my horses"))
	{
		return 0;
	}

	pn = TP->query_real_name();
	if (!pointerp(gHorse[pn]))
	{
		NF("But you have no horse stabled here.\n");
		return 0;
	}
	horses = gHorse[pn];
	for(i=0;i<sizeof(horses);i++)
		horses[i]->move_living("M",TO);
	tell_room(TO,"The stablehand fetches " +
	COMPOSITE_LIVE(horses) + ".\n");
	return 1;
}

void
init()
{
    ::init(); /* Since it's a room this must be done. */
	add_action(do_stable, "stable");
	add_action(do_fetch, "fetch");
}


