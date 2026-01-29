/**
 * Navarre December 22nd 2007.
 * Removed add_name("small") per bug report.
 * Small should only be an adj not a name.
 */

inherit "/std/weapon";
inherit "/lib/keep";
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <formulas.h>
#include <options.h>
#include <ss_types.h>
#include <filter_funs.h>
#include <files.h>
#include "/d/Ansalon/common/defs.h"

#define HIT 35
#define PEN 35

create_weapon()
{
    set_name("tree");
    add_name("club");
    set_adj("oak");
    add_adj("small");
    set_short("small oak tree");
    set_long("This is a young oak tree, some of the leaves and small "+
             "branches has been cut off, making it into a crude but "+
             "lethal club.\n");

    set_hit(HIT);
    set_pen(PEN);
    set_wt(W_CLUB);
    set_dt(W_BLUDGEON);
    set_hands(W_BOTH);
    add_prop(OBJ_M_NO_SELL, 1);
    add_prop(OBJ_M_NO_BUY,  1);
    add_prop(OBJ_I_VOLUME, 30000);
    add_prop(OBJ_I_WEIGHT, 30000);
    set_likely_dull(0);
}

