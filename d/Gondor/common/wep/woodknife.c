/*
 * /d/Gondor/common/wep/woodknife.c
 */

#pragma strict_types

inherit "/std/weapon";

#include <formulas.h>
#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>

public void	create_weapon();

public void
create_weapon()
{
    set_name("knife");
    set_pname("knives");
    add_pname("knifes");
    set_short("small forester's knife");
    set_pshort("small forester's knives");
    set_adj( ({ "small", "forester's" }) );
    set_long(break_string(
	"The handle of the small forester's knife is some kind of horn, "+
	"polished and carved into the shape of a deer's head and inlaid "+
	"with glittering onyx eyes. The blade is quite sharp, and "+
	"inscribed with a twisting vine design, done in a  "+
	"spidery etching.", 75) + "\n");
    
    set_default_weapon(10, 10, W_KNIFE, W_SLASH, W_ANYH, 0);
    add_prop(OBJ_I_VALUE, (F_VALUE_WEAPON(10, 10) + random(40) - 20));
} /* create_weapon */
