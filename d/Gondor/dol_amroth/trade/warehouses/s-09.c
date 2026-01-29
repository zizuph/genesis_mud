/* -*- Mode: C -*-
 *
 * trade/warehouses/s-09.c
 *
 * By Skippern 20(c)01
 *
 * A warehouse.
 */
#include "../../defs.h"

#include <cmdparse.h>
#include <macros.h>
#include <money.h>
#include <stdproperties.h>

inherit DOL_STD + "inside.c";

/* Global variables */
object    o, *cargo, room_ob = this_object();
int       nr;

/*
 * Function name:    create_inside()
 * Description  :    Creates the inside room.
 */
public void
create_inside()
{
    set_short("inside a warehouse");
    set_long("You are now inside one of the warehouses in Dol Amroth. " +
             "The room is large and it is high up to the roof. Along " +
             "the walls there are many heights of shelves. Some of the " +
	     "shelves are labeled, but they are all empty.\n");

    nr = 8;
    cargo = allocate(nr);
    reset_room();

    clone_object(DOL_OBJ+"doors/s-09-door")->move(this_object());
}

mixed
remove_cargo()
{
    int i;
	
	object *cargo = filter(all_inventory(this_object()),&->id("_dol_amroth_cargo"));

    i = sizeof(cargo) - 1;
    o = cargo[random(i)];
    tell_room(this_object(), "A man collects a crate of " +
	      o->query_cargo() + " and leaves.\n", 0);
    o->remove_object();

    return;
}

void
reset_room()
{
    if (present("cargo"))
        remove_cargo();

}
