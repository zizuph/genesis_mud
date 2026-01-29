/* This wagon is for NPC use only (at least at the moment) */

inherit "/std/container";

#include "/d/Krynn/common/defs.h"
#include "../local.h"
#include <stdproperties.h>
#include <macros.h>

int i;
string *dest, *from, *file;
object rubble;

create_container()
{
    int j;

    set_name("wagon");
    set_adj("gnomish");
    add_adj("mining");
    set_short("mining wagon");
    set_long(BS("A very useful device for easy transport of heavy stuff. It "
	+ "runs on iron tracks in the ground. It has a control panel set to "
	+ "one side and a little chimney on the other. It is huge and very "
	+ "heavy.", 70));

    add_prop(OBJ_M_NO_GET, "The mining wagon is too heavy.\n");
    add_prop(CONT_I_VOLUME, 60000);
    add_prop(OBJ_I_VALUE, 5000);
    add_prop(CONT_I_MAX_WEIGHT, 250000);
    add_prop(CONT_I_MAX_VOLUME, 400000);

    add_item(({"panel", "control panel"}), "You see several buttons "
	+ "and some little lights .\n");
    add_cmd_item("button", "press", "@@button_press");
    add_item("chimney", "A bit of smoke is coming from the chimney.\n");

    dest = ({"north","east","east","east","north","north","south","south"});
     dest += ({"west","west","west","south"});
    from = ({"","south","west","west","west","south","south","north","north"});
     from += ({"east","east","east","north"});
    file = ({"", "5","4","3","2","1","","1","2","3","4","5",""});
    for (j = 1; j < 12; j++)
	{
	file[j] = TDIR + "corridor" + file[j] + ".c";
	}
    file[6]  = TDIR + "binroom.c";
    file[0] = TDIR + "explosroom.c";
    file[12]  = file[0];

    seteuid(getuid());

    ::create_container();
}

string
button_press()
{
    TP->catch_msg("You press a button and a red light starts to flash.\n"
	+ "Then a whistle blows alarmingly.\n"
	+ "Otherwise nothing happens.\n");
    tell_room(E(TO), QCTNAME(TP) + " does something to the control panel "
	+ "and a whistle blows alarmingly.\n", TP);
    return "";
}

/* called from explosroom.c */

void
w_run_init()
{
	object gnome;
	gnome = present("exgnome", E(TO));
	if(!gnome)
		return;
	tell_room(find_object(file[i]), BS(QCTNAME(gnome) + " collects "
		+ "some loose rubble and blown away parts from the "
		+ "machine, which " + PRONOUN(gnome) + " puts into the "
		+ "wagon. " + C(PRONOUN(gnome)) + " then does "
		+ "something to its control panel. Several lights start "
		+ "to flash there.", 70));

	remove_item("chimney");
	add_item("chimney", "A lot of steam is coming from it.\n");

	rubble = clone_object(OBJ + "rubble.c");
	rubble->move(TO, 1);
	set_alarm(10.0, -1.0, "w_run");
}

w_run()
{
	tell_room(find_object(file[i]), BS("Producing a lot of noise and a "
		+ "considerable amount of steam, the wagon rumbles " 
		+ dest[i] + "wards.", 70));
	i++;
	move(file[i]);
	tell_room(find_object(file[i]), "A mining wagon rumbles in from "
				+ "the " + from[i] + ".\n");
	if (i == 6)       {set_alarm(10.0, -1.0, "do_empty");}
	else if (i < 12)  {set_alarm(10.0, -1.0, "w_run");}
	if (i == 12)      {i = 0;}
}

void do_empty()
{
	int j;
	object *wginv, rub;

	rubble->remove_object();
	wginv = all_inventory(TO);
	tell_room(find_object(file[6]), BS("The wagon shakes, rattles "
		+ "and drops its contents, mainly a heap of garbage, "
		+ "onto the floor.", 70));
	for (j = 0; j < sizeof(wginv); j++)
		wginv[j]->move (E(TO));
	rub = present("rubble", E(TO));
	rub->new_rubble();  /* Now one can find 2 questitems for the 
				sign-quest in the rubble. */

	set_alarm(10.0, -1.0, "w_run");
}
