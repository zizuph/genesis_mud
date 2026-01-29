/*
 * OBJ + wardrobe2.c
 *
 * Varian - Oct 2021
 *
 */

#pragma strict_types
#pragma save_binary 

#include <stdproperties.h>
#include <macros.h>
#include <cmdparse.h>
#include <formulas.h>
#include <composite.h>

inherit "/d/Genesis/specials/guilds/objs/describable_rack";
inherit "/d/Genesis/specials/lib/item_recovery_lib";

public void hook_list_commands(object for_obj);

public void
create_rack()
{
    set_adj("painted");
    add_adj("wooden");
    set_name("wardrobe");

    set_short("painted wooden wardrobe");
    set_long("This lovely looking wardrobe has been carved from " +
        "some carefully sanded wood. It has been painted lovingly " +
        "with such intricacy, that the leaves and flowers look " +
        "almost alive.\nThis looks like a good place to store your " +
        "items.\n\n\n");

    add_prop(CONT_I_MAX_WEIGHT, 50000);
    add_prop(CONT_I_MAX_VOLUME, 50000);
    add_prop(CONT_I_WEIGHT, 5000);
    add_prop(CONT_I_VOLUME, 5000);
}

public void
hook_list_commands(object for_obj)
{
    for_obj->catch_tell(
        "   <list wardrobe>     - See items stored inside.\n" +
        "   <list [item name]>  - Displays only items of that\n" +
        "                         specific name inside the wardrobe\n" +
        "   <kick wardrobe>     - A swift kick should empty all of\n" +
        "                         the non-saving items from the\n" +
        "                         wardrobe.\n");
}