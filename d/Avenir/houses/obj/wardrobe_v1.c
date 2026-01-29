/*
 * HOBJ + wardrobe_v1.c
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
    set_long("This wardrobe has kesoit sliding panels painted in gold-leaf. "+
      "Behind the panels are shelves and pegs for storing clothes " +
      "and valuables.\n\n");

    add_prop(CONT_I_MAX_WEIGHT, 50000);
    add_prop(CONT_I_MAX_VOLUME, 50000);
    add_prop(CONT_I_WEIGHT, 5000);
    add_prop(CONT_I_VOLUME, 5000);
	
	set_no_show_composite(1);
	
	add_item(({"panel", "panels", "kesoit panels", "painted panels",
	    "gold-leaf", "sliding panel", "sliding panels"}),
        "The panels are made of kesoit wood that have been painted in "+
        "a labyrinthine pattern in gold-leaf.\n");
	add_cmd_item(({"panel", "panels", "kesoit panels", "painted panels",
	    "gold-leaf", "sliding panel", "sliding panels"}), 
		({"slide", "move", "push"}),
        "The panel slides smoothly, giving you a better view of the "+
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