/* -*- Mode: C -*-
 *
 * obj/cargo.c
 *
 * A crate of cargo.
 */
inherit "/std/object";

#include "../defs.h"

#include <stdproperties.h>

#define CARGO      ({ "apples", "bananas", "dried fish", "clothes", \
                      "fresh meat", "oranges", "pineapples", "carrots", \
                      "peaches", "potatoes", "leather", "dried meat", \
					  "pears", "figs", "wool", "pottery", "salt", \
					  "feather", "grapes", "wheat", "barley", "oat", \
					  "peaches", "olives", "almonds", "ham", "cutton", \
					  "hops" })

string cargo;

void
create_object()
{
    cargo = one_of_list(CARGO);

    set_short("wooden crate of "+cargo);
    set_pshort("wooden crates of "+cargo);
    set_name("crate");
    add_name("cargo");
	add_name("_dol_amroth_cargo");
    set_long("A crate of cargo. It is filled of "+cargo+".\n");

    add_prop(OBJ_I_WEIGHT, 10000);
    add_prop(OBJ_I_VOLUME, 10000);
    add_prop(OBJ_I_VALUE, 10000 + random(1000));
    add_prop(OBJ_M_NO_SELL, "No use in selling this, better deliver it to a " +
	     "warehouse somewhere.\n");
}

string query_cargo() { return cargo; }
