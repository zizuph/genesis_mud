/* Shamelessly stolen from the backpack in Kalaman */

inherit "/d/Genesis/std/wearable_pack";
inherit "/lib/keep";

#include <stdproperties.h>
#include <macros.h>
#include <composite.h>
#include "/d/Ansalon/common/defs.h"

void
create_wearable_pack()
{
    set_name("backpack");
    set_pname("backpacks");
    set_short("black canvas backpack");
    set_pshort("black canvas backpacks");
    add_name("pack");
    set_adj(({"deep-black","deep", "black","canvas"}));
    set_long("This is a black backpack of canvas. It is stamped " +
    "with a crescent moon sigil. You may <fill> and <empty> the " +
    "backpack as you wish.\n");

    set_mass_storage(1); 

    set_keep(1); 

    add_prop(CONT_I_WEIGHT, 4500);      /* grams */
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
