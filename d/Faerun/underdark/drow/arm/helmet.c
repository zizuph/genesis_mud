/*
 *  faerun/underdark/upper/menzo/melee/arm/helmet.c
 *
 *  Helmet worn by a master in Melee-magthere
 *
 *  Created by Midnight, 16-4-2004
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
    set_name("helmet");
    set_adj( "black" );
    set_adj( "mithril-spiked" );
    set_long("This helmet is made of adamantine, which " +
             "is an alloy of adamantite. The metal has been " +
             "blackened to a deep black matted hue. " +
             "Sharp mithril spikes points outwards in a row, " +
             "which runs from the forehead all the way down " +
             "to the neck.\n");
    set_short("black mithril-spiked helmet");

    set_ac(AC + random(5));
    set_at(A_HEAD);

    add_prop(OBJ_I_WEIGHT, 500);
}