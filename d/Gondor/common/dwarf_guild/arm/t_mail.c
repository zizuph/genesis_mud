/*
 * /d/Gondor/common/dwarf_guild/arm/t_mail.c
 *
 * This mail is used by the trainer in the dwarven race guild.
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
    set_name("mail");

    set_adj("plated");
    set_adj("steel");
    set_adj("black");

    set_short("black steel plated mail");
    set_pshort("black steel plated mails");

    set_long(BSN("This mail is made of two steel plates, covering your " +
        "front and back, linked to two steel plates covering your sides. " +
        "Behind the plates is layer of leather for comfort. The steel " +
        "plates are forged in a special way to make it black and very " +
        "strong."));

    set_ac(ARMOUR_CLASS);
    set_at(A_BODY);
    set_am( ({ 2, 2, -4 }) );

    add_prop(OBJ_I_WEIGHT, 10000);
    add_prop(OBJ_I_VOLUME, 4000);
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
