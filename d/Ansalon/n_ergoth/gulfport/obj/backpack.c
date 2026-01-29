/* Backpack for VK, based on Maniac's Calian Backpack. */
/* Morrigan and Teth, Jan/Feb 97 */
/*
 * Copytweaked for Gulport, Northern Ergoth
 * Tibbit, 1 May 1998
 */

#pragma save_binary

inherit "/d/Genesis/std/wearable_pack";
inherit "/lib/keep"; 

#include <stdproperties.h>
#include <macros.h>
#include <composite.h>
#include "/d/Krynn/common/defs.h"

object this;

void
create_wearable_pack()
{
    set_name("backpack");
    set_pname("backpacks");
    set_short("black leather backpack");
    set_pshort("black leather backpacks");
    add_name("pack");
    set_adj(({"black", "leather"}));
    set_long("This is an ordinary backpack of fine leather. Packs " +
        "like this are crafted by the citizens of "+
        "Northern Ergoth, and sold all over "+
        "northern Ansalon.  "+
        "You may <fill> and <empty> the backpack "+
        "as you wish.\n");

    set_mass_storage(1); 

    set_keep(1); 

    add_prop(CONT_I_WEIGHT, 4500); 	/* grams */
    add_prop(CONT_I_MAX_WEIGHT, 150000); /* grams */
    add_prop(CONT_I_VOLUME, 8000); 	/* ml */
    add_prop(CONT_I_MAX_VOLUME, 150000); /* ml */

    add_prop(OBJ_I_VALUE, 450); 		/* Worth 450 cc */

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

