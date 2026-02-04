/*
 * File: caisson.c
 * Description: An ornamented sash with a wide pouch
 * Date: 03/16/03
 *
 *  Modified: 18 June 2003, by Bleys
 *      - Added pname to prevent multiples appearing as
 *          "black silken sash (open)s"
 *
 */

#include "/d/Terel/include/Terel.h"
#include <wa_types.h>

inherit "/d/Genesis/std/wearable_pack";
inherit "/lib/keep";

public void
create_wearable_pack()
{
    ::create_wearable_pack();
    set_name("caisson");
    add_name(({"sash", "pouch", "pouch-sash"}));
    add_adj(({"black", "silken"}));
    set_short("black silken sash");
    set_pshort("black silken sashes");
    set_long("The black silken sash is ornamented with a shimmering " +
             "print of leaves falling in unseen space. Lacking " +
             "symmetry, each leaf print falls to its own gravity as the " +
             "outline draws itself out in the light. Folded into the " +
             "front lining, a long pouch is hidden to hold small " +
             "tools and collectibles. The silk is known to originate " +
             "from the region of northern Terel.\n");

    add_prop(CONT_I_WEIGHT, 100);             /* grams */
    add_prop(CONT_I_MAX_WEIGHT, 50000);       /* grams */
    add_prop(CONT_I_VOLUME, 4000);            /* ml */
    add_prop(CONT_I_MAX_VOLUME, 50000);       /* ml */
    add_prop(CONT_I_HOLDS_COMPONENTS, 1);
    add_prop(OBJ_I_VALUE, 650);               /* Worth 650 cc */ 

    set_keep(1);
    set_mass_storage(1);
    set_slots(A_WAIST);
    set_layers(2);
    set_looseness(2);
}

string
query_recover()
{
    return MASTER + ":" + query_container_recover() + query_keep_recover();
}

public void
init_recover(string arg)
{
    init_container_recover(arg);
    init_keep_recover(arg); 
}
