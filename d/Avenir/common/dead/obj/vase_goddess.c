

inherit "/std/container";
inherit "/lib/keep";
#include "../dead.h"
#include <macros.h>
#include <composite.h>
#include <stdproperties.h>


public void
create_container()
{
    reset_euid();

    set_name("bowl");
    add_name(({ "skull", "cup", "vase" ,}));
    set_short("@@empty_str@@crystalline skull@@full_str@@");
    set_long("It is a flower bowl made from the dome of a very large skull. "+
	    "It has been decorated in swirling knot-designs using platinum and "+
        "gold. This skull flower bowl has a crystalline look to it, and "+
		"seems to glow faintly with "+
		"Source-light.\n");

    set_adj(({"flower", "skull", "polished", "crystalline"}));

    add_prop(OBJ_I_VOLUME, 5000);
    add_prop(OBJ_I_WEIGHT, 5000);
    add_prop(OBJ_I_VALUE, 1500);

    add_prop(CONT_I_RIGID, 1);
    add_prop(CONT_I_MAX_VOLUME, 6000);
    add_prop(CONT_I_MAX_WEIGHT, 6000);
}

public string
empty_str(void)
{
    if (!sizeof(all_inventory()))
	return "empty ";
    else
	return "";
}

public string
full_str(void)
{
    object *flowers = filter(all_inventory(), &->id("flower"));

    if (!sizeof(flowers))
	return "";

    if (sizeof(flowers) > 2)
	return " filled with flowers";

    return " containing " + COMPOSITE_DEAD(flowers);
}
