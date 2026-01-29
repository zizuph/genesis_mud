/*
 *  faerun/underdark/upper/menzo/melee/arm/s_bracers.c
 *
 *  A students chainmail in Underdark
 *
 *  Created by Midnight, 15-4-2004
 */

#include <formulas.h>
#include <wa_types.h>
#include <stdproperties.h>
#include "/d/Faerun/defs.h"
#include "defs.h"

inherit FAERUN_ARM_BASE;

#define AC 20

void create_faerun_armour()
{
    set_name("bracers");
    set_adj( "adamantine" );
    set_adj( "dark" );
    set_short("dark adamantine bracers");
    set_long("These bracers are constructed of adamantine, " +
             "an alloy of adamantite. The solid metal is  " +
             "perfectly crafted to provide protection for " +
             "the arms. The colour is " +
             "completely matted, so the metal has no shine to it. " +
             "Along the edges, a black leather padding " +
             "has been attached to the bracers to make them more " +
             "comfortable to wear.\n");
    


    set_ac(AC + random(5));
    set_at(A_ARMS);

    add_prop(OBJ_I_WEIGHT, 5000);
}
