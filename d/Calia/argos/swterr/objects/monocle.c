/*
 *  /d/Calia/argos/swterr/objects/monocle.c
 *
 *  Gold Moncole
 *
 *  Created Aug 2021, Greneth
 */
                                                                                
inherit "/std/armour";
#include "/d/Calia/abbrev.h"
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>

void
create_armour()
{
    ::create_armour();
    set_name("monocle");
    set_adj("gold");
    set_af(TO);
    set_short("gold monocle");
    set_long("A small round monocle with a thin piece of "
	+ "glass set inside of it. A lengthy well woven chain "
	+ "is attached to the side and has a small clasp at the "
	+ "end.\n");
    set_ac(0);
    set_at(A_EYES);
    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 100);
}

mixed
wear(object arm)
{  
    say(QCTNAME(TP) + " attaches the monocle to their eye.\n");
    write("You attach the monocle to your eye.\n");
	return 1;
}



mixed
remove(object arm)
{
    if (!objectp(query_worn()))
        return 0;
	
    say(QCTNAME(TP) + " removes the monocle from their eye.\n");
    write("You remove the monocle from your eye.\n");
    return 1;
}