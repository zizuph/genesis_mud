/*
 * File: elven_sleeves.c
 * Elven sleeves, worn by Qualinesti elves.
 *
 * Blizzard, 02/2003
 */

inherit "/std/armour";

#include <macros.h>
#include <wa_types.h>
#include <stdproperties.h>
#include "/d/Krynn/common/defs.h"

void
create_armour()
{
    set_name("sleeves");
    set_short("pair of banded leather sleeves");
    set_pshort("pairs of banded leather sleeves");
    set_adj("banded");
    add_adj("leather");
    add_adj("armour");
    set_long("It is a pair of fine leather sleeves. Being very light " +
        "and flexible they do not prevent your moves while fighting but " +
        "still provide quite good protection to your arms.\n");
    
    set_ac(30);    
    set_at(A_ARMS);
    set_am( ({-1, 2, -1}) ); 
    
    add_prop(OBJ_I_VOLUME, 500);
    add_prop(OBJ_I_WEIGHT, 800);
    add_prop(OBJ_I_VALUE, 500);
}

