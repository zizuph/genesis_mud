/*
 *  faerun/underdark/upper/menzo/melee/arm/shield.c
 *
 *  Face mask in Melee-magthere
 *
 *  Created by Midnight, 15-4-2004
 */

#include <formulas.h>
#include <wa_types.h>
#include <stdproperties.h>
#include "/d/Faerun/defs.h"
#include "defs.h"

inherit FAERUN_ARM_BASE;

#define AC 15

void create_faerun_armour()
{

    set_name("shield");
    set_adj( "mithril" );
    set_adj( "ornamented" );
    set_short("ornamented mithril shield");
    set_long("This is quite an unusual shield for being in drow possesion, " +
             "since it seems to be of typical duargar origin. " +
             "It must have been taken during on of the drow raids on " +
             "the duargar.\n");

    set_ac(AC + random(5));
    set_at(A_SHIELD);

    add_prop(OBJ_I_WEIGHT, 7500);

}