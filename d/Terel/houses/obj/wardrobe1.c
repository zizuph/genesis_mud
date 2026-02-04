/*
 * HOBJ + wardrobe_h1.c
 *
 * Based on Varian's wardrobe in the Genesis Houses dir.
 *
 * Lilith, Feb 2022
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
    set_adj("tall");
    add_adj("floor-to-ceiling");
    set_name("wardrobe");
    set_short("floor-to-ceiling wardrobe");
    set_long("This wardrobe has folding pine doors. "+
      "Behind the doors are shelves and pegs for storing clothes " +
      "and valuables.\n\n");

    add_prop(CONT_I_MAX_WEIGHT, 50000);
    add_prop(CONT_I_MAX_VOLUME, 50000);
    add_prop(CONT_I_WEIGHT, 5000);
    add_prop(CONT_I_VOLUME, 5000);
	
	set_no_show_composite(1);
	
	add_item(({"door", "folding door", "doors", "folding doors"}),
        "Each door is made of two smaller doors that hinge together "+
        "and open and close something like an accordian.\n");
	add_cmd_item(({"door", "folding door", "doors", "folding doors"}),
		({"slide", "move", "push", "open"}),
        "The doors slide open smoothly, giving you a better view of the "+
		"contents of the wardrobe.\n");
		
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
