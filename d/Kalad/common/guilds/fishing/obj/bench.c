/*
 *  /w/cedivar/fishing/obj/bench.c
 *
 *  Pier Bench
 *
 *  Created June 2018, Cedivar
 */

#pragma strict_types

#include "/w/cedivar/fishing/defs.h"
#include <macros.h>
#include <cmdparse.h>
#include <stdproperties.h>

inherit "/std/object";

string sit_bench(string str);
string stand_bench(string str);

void
create_object()
{
	set_name("bench");
	add_name("benches");
	set_adj("wooden");
	set_short("wooden bench");
	set_long("Very simple in design these benches are not only very "
	+ "sturdy looking but practical as well. Other than a bit "
	+ "of trash beneath there is nothing noteworthy about it.\n");

    add_prop(OBJ_M_NO_GET, "It is very well secured to the pier.\n");
}

public void
init()
{
	::init();
	add_action(sit_bench, "sit");
	add_action(stand_bench, "stand");
}

int
sit_bench(string str)
{
	write("You sit down on the bench.\n");
	say(QCTNAME(this_player()) + "sits down on the bench.\n");
	return 1;
}

int
stand_bench(string str)
{
	write("You stand up from the bench.\n");
	say(QCTNAME(this_player()) + "stands up from the bench.\n");
	return 1;
}