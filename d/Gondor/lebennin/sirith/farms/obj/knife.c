/*
 * /d/Gondor/lebennin/sirith/farms/obj/knife.c
 *
 * Copyright (C) 1997 by Nancy L. Mintz (Gnadnar)
 */

inherit "/std/weapon";
inherit "/lib/keep";

#include <formulas.h>		/* for F_VALUE_WEAPON	*/
#include <stdproperties.h>	/* for OBJ_I_*		*/
#include <wa_types.h>		/* for W_KNIFE, etc	*/

public void	create_weapon();

/*
 * Function name:	create_weapon
 * Description	:	set up the knife
 */
public void
create_weapon()
{
    set_name("knife");
    set_pname( ({ "knives", "weapons" }) );
    set_short("pruning knife");
    set_pshort("pruning knives");
    set_adj("pruning");
    set_long("The pruning knife has a sharp curved blade. Its wooden "+
	"handle is worn smooth with use.\n");
    set_default_weapon(10, 10, W_KNIFE, W_SLASH, W_ANYH, 0);
    add_prop(OBJ_I_VALUE, (F_VALUE_WEAPON(10, 10) + random(40)));
} /* create_weapon */
