/*
 * Based on the trashcan in Hobbiton, this is a classier disposal bin within
 * which players may destroy items. Props to Finwe, 5.2004
 *
 * Mortis 9.2014
 */


#pragma save_binary
#pragma strict_types

#include <stdproperties.h>
#include <macros.h>
#include <composite.h>
#include <filter_funs.h>
#include "../local.h"

inherit "/std/container";

void
create_container()
{
    set_name(({"bin"}));
    set_adj("disposal");
    add_adj("marble");
    set_short("marble disposal bin");
    set_long("A beautifully polished, enclosed bin of thick, translucent white "
    + "marble, these containers are one of the reasons the city of Palanthas "
    + "is so clean. You may use it to dispose of trash or other items for "
    + "which you have no further use.\n");

    /* Some properties of this disposal bin */
    add_prop(OBJ_I_NO_GET, 1);          /* Not gettable       */
    add_prop(CONT_I_IN,1);              /* It's a container!  */
    add_prop(CONT_I_RIGID,1);           /* A rigid object     */
    add_prop(CONT_I_TRANSP,0);          /* Not transparant    */
    add_prop(CONT_I_MAX_VOLUME,200000); /* Can contain 200 L  */
    add_prop(CONT_I_MAX_WEIGHT,200000); /* Can contain 200 Kg */

    add_prop(OBJ_S_WIZINFO, "A marble disposal bin used in Palanthas. It "
    + "will destroy anything placed inside after a set time unless it is "
    + "removed quickly.\n");

}

public void
dump_trash(object ob)
{
    // Only removes object if it hasn't been removed from the bin.
    if (present(ob, TO))
    {
        ob->remove_object();
        tell_room(E(TO), "There is a brief flash of light from within the "
        + "marble disposal bin.\n");
    }
}


mixed enter_inv(object ob, object from)
{
   ::enter_inv(ob, from);

   if(living(ob)) return;

// dumps trash 
   set_alarm(10.0, 0.0, &dump_trash(ob));
}
