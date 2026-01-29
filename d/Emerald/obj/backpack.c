/*  coded by Amelia, 7/97 
 * Modified by Marisol, (09/02/98)
 */

inherit "/d/Genesis/std/wearable_pack.c";
inherit "/lib/keep.c";

#include <cmdparse.h>
#include <composite.h>
#include <language.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>




void
create_wearable_pack()
{
    set_keep();
    set_mass_storage(1);
    set_name("backpack");
    add_name("equipment");
    add_name("pack");
    add_pname("backpacks");
    add_pname("packs");
    add_adj("leather");
    add_adj("tan");
    set_short("tan leather backpack");
    set_pshort("tan leather backpacks");
    set_long("This backpack is made with the best sheep leather "+
        "from the village of Ovejuno. The leather is soft and "+
        "sturdy, just perfect for carrying various items on the road. "+
        "For ideas of how to use this backpack check the "+
        "<help backpack> for commands.\n");

    add_prop(OBJ_I_VALUE, 200);
    add_prop(CONT_I_MAX_WEIGHT, 150000);
    add_prop(CONT_I_MAX_VOLUME, 150000);
    add_prop(CONT_I_REDUCE_WEIGHT, 125);
    add_prop(CONT_I_REDUCE_VOLUME, 125);
    add_prop(CONT_I_WEIGHT, 1600);
    add_prop(CONT_I_VOLUME, 1800);
    add_prop(OBJ_I_LIGHT, 0);
}

string
query_recover()
{
    return MASTER + ":" + query_container_recover();
}

void
init_recover(string args)
{
    init_container_recover(args);
}

int
help_backpack(string str)
{
    object bearer = this_player();
    object this = this_object();

    if (id(str))
    {
	if (present(this, bearer))
	{
        bearer->catch_msg("You can <fill backpack> "+
            "and <empty backpack>, as well as <wear backpack> and "+
            "<remove backpack>.\n");
	    return 1;
	}
    }
    return 0;
}

void
init()
{
    ::init();
    add_action(&help_backpack(), "help");
}
