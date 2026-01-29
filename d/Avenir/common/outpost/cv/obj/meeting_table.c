// /d/Avenir/common/outpost/cv/obj/meeting table.c
// This file is copied from 
// file name:	/d/Avenir/union/obj/table_s.c
// created by:  Lilith, Jan 2022
// purpose:	    Table for the meting room.
#pragma strict_types

inherit "/std/container";

#include "/d/Avenir/common/outpost/outpost.h"
#include <files.h>
#include <macros.h>
#include <cmdparse.h>
#include <composite.h>
#include <filter_funs.h>
#include <stdproperties.h>

public void
reset_container(void)
{
    object obj;
    obj = clone_object(BAZAAR + "museum/obj/coffee");
	obj->move(TO, 1);
	obj->set_heap_size(5 +random(3));
    obj = clone_object(CITY + "obj/food/iced_coffee");
    obj->move(TO, 1);
	obj->set_heap_size(4 +random(4));

}

public void
create_container(void)
{
    if (!IS_CLONE)
	return;

    reset_euid();

    set_name("table");
    add_name(({"_coven_meeting_table", "slab"}));
    set_adj(({"massive","rectangular"}));
    set_short("massive slab table");
    set_long("This table was made from a slab of creamy limestone "+
	"quarried from a wall nearby. It is stacked on another, smaller "+
	"block. The surface has a textured, leathery look and feel to it. "+
	"A statuary fountain rests on the tabletop. ");

    add_prop(CONT_I_MAX_WEIGHT, 50000);
    add_prop(CONT_I_MAX_VOLUME, 50000);
    add_prop(CONT_I_WEIGHT, 500);
    add_prop(CONT_I_VOLUME, 500);
    add_prop(OBJ_I_VALUE, 500);
    add_prop(CONT_I_ATTACH, 1);
    add_prop(CONT_I_RIGID, 1);
    add_prop(OBJ_M_NO_GET, "It cannot be moved.\n");

    // Don't want it to show up in room desc.
    set_no_show_composite(1);
	reset_container();
}

public int
food_drink(object item)
{
    if (IS_FOOD_OBJECT(item))
	return 1;

    if (IS_DRINK_OBJECT(item))
	return 1;

    return 0;
}

public int
do_serve(string str)
{
    if (!strlen(str))
	return NF("Serve what?\n");

    object *iarr, *larr, *oarr = all_inventory();

    if (!sizeof(oarr))
	return NF("There is nothing on the table to serve!\n");

    if (!parse_command(str, oarr, "%i 'to' [the] %s", iarr, str))
	return NF("Serve what to whom?\n");

    iarr = NORMAL_ACCESS(iarr, "food_drink", this_object());

    if (!sizeof(iarr))
    {
	write("What are you trying to serve?\n");
	return 1;
    }

    oarr = FILTER_OTHER_LIVE(all_inventory(environment()));

    if (!strlen(str) || !sizeof(oarr) ||
	!parse_command(str, oarr, "%l", larr) ||
	!sizeof(larr = NORMAL_ACCESS(larr, 0, 0)))
    {
	write("Whom are you trying to serve?\n");
	return 1;
    }

    if (sizeof(larr) != 1)
    {
	write("You may only serve one individual at a time.\n");
	return 1;
    }

    oarr = filter(iarr, &->move(larr[0]));

    if (sizeof(iarr -= oarr))
    {
	if (sizeof(iarr) > 1 || iarr[0]->num_heap() > 1)
	    str = "them";
	else
	    str = "it";

	write("You pick up "+ COMPOSITE_DEAD(iarr) +" from the "+
	    short() +" and serve "+ str +" to "+
	    larr[0]->query_the_name(TP) +".\n");
	larr[0]->catch_msg(QCTNAME(TP) +" picks up "+ QCOMPDEAD +
	    " from the "+ short() +" and serves "+ str +" to you.\n");
	say(QCTNAME(TP) +" picks up "+ QCOMPDEAD +" from the "+
	    short() +" and serves "+ str +" to "+ QTNAME(larr[0]) +
	    ".\n", ({ this_player(), larr[0] }));
    }

    if (sizeof(oarr))
    {
	write("You were unable to serve "+ COMPOSITE_DEAD(oarr) +
	    " to "+ larr[0]->query_the_name(TP) +".\n");
    }

    return 1;
}

public void
init(void)
{
    ::init();
    add_action(do_serve, "serve");
}
