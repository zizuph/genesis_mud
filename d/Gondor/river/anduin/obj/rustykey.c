/*
 * /d/Gondor/river/anduin/carrock2lorien/obj/rustykey.c
 *
 * a useless key you might find buried ...
 */

#pragma strict_types

inherit "/std/key";

#include <stdproperties.h>

public void	create_key();


/*
 * Function name:	create_key
 * Description	:	set up the key
 */
public void
create_key()
{
    ::create_key();
    set_adj( ({ "large", "rusty" }) );
    set_long(break_string("The large key is badly rusted. "+
	"It is doubtful it will work any more.", 75)+"\n");
    set_key("_useless_key");
    add_prop(OBJ_I_WEIGHT, 170);
    add_prop(OBJ_I_VOLUME, 30);
    add_prop(OBJ_I_VALUE, 0);
} /* create_key */
