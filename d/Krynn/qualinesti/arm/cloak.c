/* 
 * File: cloak.c
 * A cloak, worn by elves in Qualinesti.
 *
 * Blizzard, 02/2003
 */
 
inherit "std/armour.c";

#include <wa_types.h>
#include <macros.h>
#include <formulas.h>
#include "/d/Krynn/common/defs.h"

string   *adj_list = ({ "grey", "smooth", "green", "brown", "dark-brown",
                        "dark-green" });
string   adj;

void
create_armour()
{
    adj = adj_list[random(sizeof(adj_list))];
    
    set_name("cloak");
    set_short(adj + " elven cloak");
    set_pshort(adj + " elven cloaks");
    set_adj(adj);
    add_adj( "elven" );
    set_ac(10);
    set_at(A_ROBE);
    set_af(TO);
    set_long("This lightweight cloak is made of a smooth, close-knit " +
        "cloth. It shifts and shimmers, and blends into the " +
        "surroundings, helping the wearer avoid detection. A small " +
        "silver clasp in the shape of a leaf holds it closed at the " +
        "throat.\n");    
/* Since such cloaks are commonly used by elves, I do not make it add extra
   hide skill. But let the player think it does. */

    add_prop(OBJ_I_WEIGHT, 900);
    add_prop(OBJ_I_VOLUME, 1000);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(10) + random(300) + 500);
}

public int
wear(object what)
{
    TP->catch_msg("You wear the " + short() + ", which makes you blend into " +
        "the surrounding area.\n"); 
    say(QCTNAME(TP) + " wears the " + short() + ".\n");
    
    return 1;
}
