/*
 * OBJ + pel_wardrobe1.c
 *
 * Varian - Aug 2021
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
    set_adj("carved");
    add_adj("wooden");
    set_name("wardrobe");

    set_short("carved wooden wardrobe");
    set_long("Reaching up all the way to the ceiling, " +
      "this wardrobe is a beautiful piece of furniture. " +
      "Delicate images of vines and flowers have been " +
      "carved into the dark brown wood, so detailed and " +
      "intricate that they feel alive.\nThis looks like " +
      "a good place to store your items.\n\n\n");

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
        "   <kick wardrobe>     - A swift kick should empty all of the\n" +
        "                         the non-saving items from the\n" +
        "                         wardrobe.\n");
}