/*
 * /d/Gondor/anorien/cairandros/obj/dicecup.c
 *
 * Dice in a cup, presumably soldiers gamble with them
 *
 * Varian - March, 2020
 *
 */

#pragma strict_types

#include "../../defs.h"
#include <stdproperties.h>
#include <macros.h>
#include "/d/Gondor/met_defs.h"

inherit "/std/object";

int do_getem(string str);

string *markings = ({"tree", "star", "crown", "sword", "coin", "rod"});

#define MARK    one_of_list(markings)

public void
create_object()
{
	set_name("_die_5_");
	add_name( ({"mark", "_mark"}) );

	set_short("" + MARK + "");
}


public int
do_getem(string str)
{
    notify_fail("What?\n");
    
    if((str != "_mark" && str != "mark"))
    return 0;

	write("You put your dice back into the leather cup.\n");
    say(QCTNAME(TP) + " gathers the dice and puts them back in " +
    	"the cup.\n");
    set_alarm(0.1,0.0, &remove_object());
    return 1;
}

public void
init()
{   
    ::init();
    add_action(do_getem, "gutem");
}