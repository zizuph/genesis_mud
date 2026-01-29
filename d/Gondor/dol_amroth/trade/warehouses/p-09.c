/* -*- Mode: C -*-
 *
 * trade/warehouses/p-09.c
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

/* Prototypes */
void      add_cargo();

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
	     "the walls there are many heights of shelves, and " +
	     "there are trade goods in crates, barrels and bulk in all " +
	     "the shelves. Some of the shelves are labelled. An " +
	     "intendant stands in the middle of the room shouting " +
	     "orders to people and making notes in a book. " +
	     "You might pick up a crate from one of the ships " +
	     "and <deliver> it here for a small fee.\n");

    nr = 8;
    cargo = allocate(nr);
    reset_room();
	
	add_item( ({ "shelf", "shelves" }), "Many heights of shelves.\n");

    add_cargo();
    add_cargo();
    add_cargo();

    clone_object(DOL_OBJ+"doors/p-09-door")->move(this_object());
}

int
deliver(string arg)
{
    object player = this_player();
    object crate, *temp_ob;

    if (arg == "crate" || arg == "cargo")
    {
        //find the crate in the inventory
        temp_ob = FIND_STR_IN_OBJECT("cargo", player);
	if (sizeof(temp_ob))
	    crate = temp_ob[0];

	if (!crate || crate == 0)
	{
	    notify_fail("You have no crates, please pick up one first.\n");
	    return 0;
	}
	if (crate->query_prop("_crate_is_delivered") == 1)
	{
	    notify_fail("This crate is already delivered, please don't " +
		"try to rip me of!\n");
	    return 0;
	}
	player->catch_tell("You deliver the crate to the intendant, who " +
	    "gives you some coins in return.\n");
	say(QCTNAME(player) + " delivers a crate to the intendant, who " +
	    "gives " + player->query_objective() + " some coins in return.\n",
	    player);
	crate->add_prop("_crate_is_delivered", 1);
	crate->add_prop(OBJ_M_NO_GET, "Only the right-full owner can claim " +
	    "the crates.\n");
	crate->move(this_object());
	o = MONEY_MAKE_CC(random(10) + 10);
	o->move(player);
	player->add_exp_general(50);
	return 1;
    }

    notify_fail("Deliver what?\n");
    return 0;
}

void
init()
{
    ::init();
    add_action(deliver, "deliver");
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
add_cargo()
{
    o = clone_object(DOL_OBJ + "cargo");
    tell_room(this_object(), "A man delivers a crate of " +
	      o->query_cargo() + " and leaves.\n", 0);
    o->add_prop("_crate_is_delivered", 1);
    o->add_prop(OBJ_M_NO_GET, "Only the right-full owner can claim the " +
	"crates.\n");
    o->move(this_object());

    return;
}

void
reset_room()
{
    int i;
 	
	object *cargo = filter(all_inventory(this_object()),&->id("_dol_amroth_cargo"));

    i = sizeof(cargo) - 1;

    if (!present("_dol_amroth_cargo"))
    {
        add_cargo();
    }

    set_alarm(8.0, 0.0, &add_cargo());

    if (random(8) == 1)
        set_alarm(4.0, 0.0, &add_cargo());

    if (i > nr)
        set_alarm(10.0, 0.0, &remove_cargo());

    if ( i > (nr * 2))
        set_alarm(2.0, 0.0, &remove_cargo());

    if ((i > ( nr / 2)) || random(6) == 1)
        set_alarm(12.0, 0.0, &remove_cargo());

    if (present("_dol_amroth_cargo") && random(4) == 1)
        set_alarm(6.0, 0.0, &remove_cargo());

}
