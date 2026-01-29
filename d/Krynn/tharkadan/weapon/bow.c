/* bow.c
 * A shortbow used by hobgoblin trackers.
 * Arman 2017
 */

#pragma strict_types

#include <stdproperties.h>
#include <macros.h>
#include <formulas.h>
#include "/d/Krynn/common/defs.h"
#include "../local.h"

inherit "/std/bow";

public void
create_bow()
{
    set_adj(({"blackwood", "black", "short"}));
    add_name("shortbow");
    set_short("blackwood shortbow");
    set_long("This crude shortbow is made of blackwood found in the " +
        "Great Moor bordering Kern, and is a popular bow of choice by " +
        "goblins and hobgoblins alike.\n"); 

    add_prop(OBJ_I_WEIGHT, 900);
    add_prop(OBJ_I_VOLUME, 3250);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(35, 35));

    set_hit(35);
    set_pen(35);
    
    seteuid(getuid(TO));
}


