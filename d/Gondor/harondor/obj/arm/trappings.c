/*
 * The trappings worn by the oliphaunts of Harad.
 * Serif, August 2001.
 */

#pragma strict_types

inherit "/std/armour";

#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>
#include "/d/Gondor/defs.h"

void
create_armour()
{
    set_name("trapping");
    set_pname("trappings");
    add_adj("scarlet");
    add_adj("gold");
    add_adj("oliphaunt");
    set_short("trapping of scarlet and gold");
    set_pshort("trappings of scarlet and gold");
    set_long("This is the ornamental trapping worn by an oliphaunt "
        + "on its way to battle. It is crafted of leather cords binding "
        + "scarlet fabric and gold ornaments together, and is designed to "
        + "drape the head and back of an oliphaunt.\n");
    set_adj(({"leather", "ornamental"}));

    set_ac(10);
    set_at(A_HEAD | A_BACK | A_NECK | A_EARS);
    set_af(TO);

    add_prop(OBJ_I_VALUE, (1700 + random(100)));
    add_prop(OBJ_I_WEIGHT, (11000 + random(1000)));
    add_prop(OBJ_I_VOLUME, (query_prop(OBJ_I_WEIGHT) / 2) * 3);

    add_item(({"fabric", "scarlet fabric", "strips"}), "Strips of scarlet "
        + "fabric are tied into the leather of the trapping, making a "
        + "bright and lively effect.\n"); 
    add_item(({"gold", "ornaments", "gold ornaments"}), "Gold ornaments "
        + "are woven into the scarlet fabric and leather of the trapping, "
        + "swaying and gleaming when the trapping moves.\n");
    add_item(({"leather", "cords", "leather cords"}), "Leather cords make up "
        + "the bulk of the trapping, supplying strength to the item while "
        + "securing the scarlet fabric and gold ornaments.\n");
}

public int
wear(object arm)
{
    if (TP->query_name() != "Oliphaunt")
    {
        write("The " + short() + " is much too big for you!\n");
        say(QCTNAME(TP) + " flounders around awkwardly while trying to wear "
            + "a huge " + short() + ", but only manages to get tangled up "
            + "and look foolish.\n"); 
        return -1;
    }
    else
    {
        say("A haradrim throws a " +TO->query_short()+ " over "
            +QTNAME(TP)+"'s head and back.\n");
        return 1;
    }
}