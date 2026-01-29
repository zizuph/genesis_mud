/*
 *  party_cracker.c
 *  Cloned by the party_room.c when someone buys a cracker.
 *  It is bloody noisy, so limit the sale!
 */
inherit "/std/object";

#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/sys/cmdparse.h"
#include "party.h"

void do_pang();

int number_of_alarms = 0;

void
create_object()
{
    set_name(({"cracker", "firecracker", "string"}));
    set_pname(({"crackers", "firecrackers", "strings"}));
    set_short("string of firecrackers");
    set_pshort("strings of firecrackers");
    set_long("You can light the string at the end.\n");
    add_prop(OBJ_I_WEIGHT, 400);
    add_prop(OBJ_I_VOLUME, 1000);
    add_prop(OBJ_I_VALUE, 100);
    add_prop(OBJ_M_NO_GET, "@@check_lit");
}

mixed
check_lit()
{
    if (!number_of_alarms)
	return 0;
    return "Are you crazy???\n";
}

void
init()
{
    ::init();

    if (this_player() != environment())
	return;
    add_action("do_light", "light");
}

int
do_light(string str)
{
    object *obs;
    string txt;

    notify_fail("Light what?\n");

    if (!str)
	return 0;

    obs = FIND_STR_IN_OBJECT(str, this_player());

    if (!obs || !sizeof(obs) || obs[0] != this_object())
	return 0;

    write("You light the string of firecrackers and wait for what will "
	+ "happen.\n");
    say(QCTNAME(this_player()) + " lights a string of firecrackers!!!\n");
    this_object()->move(environment(this_player()));
    number_of_alarms = 5 + random(20);
    set_alarm(itof(5 + random(4)), 0.0, &do_pang());
    return 1;
}

void
do_pang()
{
    string txt;

    switch (random(5))
    {
    case 0:
	txt = "PANG!";
	break;
    case 1:
	txt = "PANG! PANG!";
	break;
    case 2:
	txt = "PLOFFF PANG! PANG! PANG!";
	break;
    case 3:
	txt = "PANG! PANG! PENG! PANG!";
	break;
    case 4:
	txt = "PANG! PANG! PANG! PANG - PANG!!! PANG!";
	break;
    }

    if (environment())
	tell_room(environment(), txt + "\n");

    number_of_alarms--;

    if (!number_of_alarms)
    {
	remove_object();
	return;
    }
    set_alarm(itof(1 + random(4)), 0.0, &do_pang());
}
