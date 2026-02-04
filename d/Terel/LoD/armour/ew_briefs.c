/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * ew_briefs.c
 *
 * Mergula's battle briefs.
 *
 * Lilith, June 2008
 *
 */

#include <wa_types.h>
#include <ss_types.h>
#include "/d/Terel/include/Terel.h"

inherit STDARMOUR;
inherit "/lib/keep";

public void
create_terel_armour()
{
    set_name("briefs");
    set_short("pair of battle briefs");
    set_pshort("pairs of battle briefs");
    set_long("These are the types of briefs worn by gladiators, "+
        "wrestlers, and similar fighters who wear them for "+
        "freedom of movement and the opportunity to intimidate "+
        "oppononents with a fine display of bulging muscles. "+
        "A blackened steel belt is sewn into the waist, and "+
        "the buckle bears the inscription 'Mergula' on it.\n");
    add_adj(({"blackened", "steel", "battle", "mergula's", "megula"}));
    add_item(({"buckle"}),
        "The buckle is made of blackened steel. It bears the "+
        "word 'Mergula' on it.\n");

    set_default_armour(29, A_WAIST, 0, 0);
    set_keep(1);
    add_prop(OBJ_I_VALUE, 400);
}

