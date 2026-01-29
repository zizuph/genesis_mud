/*
 * /d/Gondor/lebennin/sirith/farms/obj/pfork.c
 * a simple pitchfork
 *
 * Copyright (C) 1997 by Nancy L. Mintz (Gnadnar)
 *
 */

#pragma strict_types

inherit "/std/weapon";

#include <wa_types.h>		/* for W_POLEARM, W_IMPALE, etc	*/
#include <stdproperties.h>		/* for OBJ_I_WEIGHT, etc	*/
#include <formulas.h>			/* for F_VALUE_WEAPON		*/
#include "/d/Gondor/defs.h"

public void	create_weapon();

/*
 * Function name:	create_weapon
 * Description	:	set up the pitchfork
 */
public void
create_weapon()
{
    set_name("pitchfork");
    add_name( ({ "fork" }) );
    set_short("pitchfork"); 
    set_long(BSN("The pitchfork has a three-pronged head set on a "+
	"long wooden handle."));

    /* this is a "found" weapon, so if i am reading /doc/man/general/weapon
     * correctly, it can't have WC > 10. i'm assuming not so great for
     * to-hit, but if you do manage to hit, then penetration is pretty good
     */
    set_default_weapon(7, 10, W_POLEARM, W_IMPALE , W_BOTH, 0);
    
    add_prop(OBJ_I_VOLUME, 1000); /* slightly bigger than gondor staff */
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(7,10)+random(50)-25);
} /* create_weapon */
