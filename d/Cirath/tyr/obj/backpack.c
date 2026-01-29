#pragma save_binary

inherit "/d/Genesis/std/wearable_pack";
inherit "/lib/keep";

#include <stdproperties.h>
#include <macros.h>
#include <composite.h>
#include "/d/Cirath/common/defs.h"


void
create_wearable_pack()
{
    set_name("backpack");
    set_pname("backpacks");
    set_short("hide backpack");
    set_pshort("hide backpacks");
    set_adj("hide");
    set_long("Constructed from a piece of leathery beast hide, this "
    	+"pack has been made to endure the rugged conditions of the "
    	+"Athasian wilderness.  The pack can hold a large amount of "
    	+"equipment, making it a good friend of the traveller.  The "
    	+"<fill> or <empty> commands can be used on this pack to make "
    	+"using it easier.\n");

    set_mass_storage(1);

    set_keep(1);

    add_prop(CONT_I_WEIGHT, 3500);      /* grams */
    add_prop(CONT_I_MAX_WEIGHT, 150000); /* grams */
    add_prop(CONT_I_VOLUME, 8000);      /* ml */
    add_prop(CONT_I_MAX_VOLUME, 150000); /* ml */

    add_prop(OBJ_I_VALUE, 450);                 /* Worth 450 cc */

}

string
query_recover()
{
    return MASTER + ":" + query_container_recover() + query_keep_recover();
}

void
init_recover(string arg)
{
    init_container_recover(arg);
    init_keep_recover(arg);
}

