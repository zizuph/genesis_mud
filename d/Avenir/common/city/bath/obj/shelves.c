#pragma strict_types
/*
 * ~/shelves.c
 *
 * Generic Shelves for the bath.
 *
 * Revisions:
 *   Lucius, Aug 2016: Code Cleanups.
 *
 */
inherit "/std/container";

#include "../bath.h"
#include <stdproperties.h>


public void
fill_shelf(void)
{
    object ob;

    // Empty the shelf
    all_inventory()->remove_object();

    // Fill the shelf
    ob = clone_object(BATHOB +"tray");
    ob->fill_tray();
    ob->move(this_object(), 1);

    ob = clone_object(BATHOB +"towel");
    ob->set_heap_size(4);
    ob->move(this_object(), 1);

    ob = clone_object(BATHOB +"soap");
    ob->set_heap_size(4);
    ob->move(this_object(), 1);
}

public void 
create_container(void)
{
    setuid();
    seteuid(getuid());

    set_name(({"shelf", "ledge", "niche", "_ave_bath_shelf"}));
    set_long("It is a simple shelf, more of a niche, cut into the " +
	"stone of the wall.\n");

    add_prop(CONT_I_RIGID, 1);
    remove_prop(CONT_I_TRANSP);

    add_prop(CONT_I_MAX_WEIGHT, 10000);
    add_prop(CONT_I_MAX_VOLUME, 10000);
    add_prop(OBJ_I_WEIGHT, 5000);
    add_prop(OBJ_I_VOLUME, 5000);
    add_prop(OBJ_M_NO_GET, "They are far too big.\n");

    set_no_show_composite(1);
}
