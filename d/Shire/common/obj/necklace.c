/*
 * A chain necklace
 * -- Finwe, July 2002
 */

#pragma save_binary;

inherit "/std/object";
inherit "/lib/wearable_item";

#include <ss_types.h>
#include <formulas.h>
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include "/d/Shire/sys/defs.h"

void
create_object()
{
    set_name("necklace");
    add_name("beautiful twisted necklace");
    add_name("twisted necklace");
    add_name("beautiful necklace");

    set_short("beautiful twisted necklace");
    set_long("This is a "+short()+" made of a strand of gold and another " +
        "strand of silver. They are delicately twisted together, forming " +
        "an unusual yet beautiful necklace.\n");
    set_slots(A_NECK);
    set_layers(0);
    set_looseness(5);

    add_prop(OBJ_I_VALUE, 275);
    add_prop(OBJ_I_VOLUME, 20);
    add_prop(OBJ_I_WEIGHT, 25);
}


public void
leave_env(object env, object to)
{
    ::leave_env(env, to);
    wearable_item_leave_env(env, to);
}

string query_auto_load() { return MASTER + ":"; }

public string query_recover() { return 0; }


