/*
 *  faerun/underdark/upper/menzo/melee/arm/m_greaves.c
 *
 *  A masters greaves in Melee-magthere
 *
 *  Created by Midnight, 16-4-2004
 */

#include <formulas.h>
#include <wa_types.h>
#include <stdproperties.h>
#include "/d/Faerun/defs.h"
#include "defs.h"

inherit FAERUN_ARM_BASE;

#define AC 30

void create_faerun_armour()
{
    set_name("greaves");
    set_adj( "adamantine" );
    set_adj( "decorated" );

    set_long("These greaves are made of dark adamantine, " +
             "an alloy of adamantite. They look rather " +
             "comfortable, since they have a soft black " +
             "leather padding underneath the metal. " +
             "Exquisite decorations of spiderwebs has been " +
             "crafted with great precision into the dark metal. "+
             "The metal is dark and has been matted by daily use.\n");
    set_short("decorated adamantine greaves");

    set_ac(AC + random(5));
    set_at(A_LEGS);

    add_prop(OBJ_I_WEIGHT, 5000);
}