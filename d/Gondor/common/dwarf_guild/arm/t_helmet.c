/*
 * /d/Gondor/common/dwarf_guild/arm/t_helmet.c
 *
 * This helmet is worn by the trainer in the dwarven race guild.
 *
 * /Mercade, 7 January 1994
 *
 * Revision history:
 */

#pragma save_binary

inherit "/std/armour";

#include <formulas.h>
#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>
#include "/d/Gondor/defs.h"
#include "../dwarf.h"

#define ARMOUR_CLASS 30

void
create_armour()
{
    set_name("helmet");
    add_name("helm");

    set_adj("black");
    set_adj("steel");
    set_adj("visored");

    set_short("black steel visored helmet");
    set_pshort("black steel visored helmets");
    set_long(BSN("This is a big and protective helmet. It is made of steel " +
        "plates and has a visor to protect your face. The steel is forged " +
        "in a special way to make it black and very strong."));

    set_ac(ARMOUR_CLASS);
    set_at(A_HEAD);
    set_am( ({ 1, -2, 1 }) );

    add_prop(OBJ_I_WEIGHT, 3000);
    add_prop(OBJ_I_VOLUME, 380);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(ARMOUR_CLASS) + random(201) - 100);
}

string
query_recover()
{
    return MASTER + ":" + query_arm_recover();
}

void
init_recover(string arg)
{
    init_arm_recover(arg);
}