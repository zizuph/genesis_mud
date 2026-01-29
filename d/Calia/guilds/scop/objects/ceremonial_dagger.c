
/*
 * ceremonial_dagger.c
 *
 * A ceremonial_dagger for cutting leftovers for the Spirit Circle of Psuchae
 * Found in the temple study, hanging on a rack on the wall.
 * Copyright (C): Jaacar, August 1st, 2003
 *
 */


inherit "/std/weapon";

#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"
#include SPIRIT_HEADER

void
create_weapon() 
{
    set_name("dagger");
    set_pname("daggers");
    add_name("_spirit_ceremonial_dagger_");
    set_adj("ceremonial");
    add_adj("sharp");
    set_short("sharp ceremonial dagger");
    set_long("This is a ceremonial dagger. It is "+
		"very sharp and is used to cut body parts from "+
        "corpses. The handle of the dagger is covered "+
		"in gold and has the symbol of Psuchae on it.\n");
    set_default_weapon(10, 10, W_KNIFE, W_SLASH, W_ANYH);
    add_prop(OBJ_I_VOLUME,450);
    add_prop(OBJ_I_WEIGHT,1400);
    add_prop(OBJ_M_NO_SELL,1);
    add_prop(OBJ_I_NO_STEAL,1);
    add_prop(SPIRIT_CUTTING_KNIFE,1);
}

