/*
 * A chain necklace
 * -- Finwe, February 2018
 */

#pragma save_binary;

inherit "/std/object";
inherit "/lib/wearable_item";

#include "/d/Shire/sys/defs.h"
#include <wa_types.h>


#define ITEM_NAME   "_chain_necklace"
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

