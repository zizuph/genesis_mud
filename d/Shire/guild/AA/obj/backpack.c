#pragma save_binary
#pragma strict_types

inherit "/d/Genesis/std/wearable_pack";
inherit "/lib/keep";

#include <stdproperties.h>
#include <macros.h>
#include <composite.h>
#include "../guild.h"

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

string
adjust_strips()
{
  say(QCTNAME(TP)+" adjusts strips on "+HIS(TP)+" rucksack.\n");
  return "You adjust strips on the rucksack.\n";
}

void
create_wearable_pack()
{
    set_name("rucksack");
    set_pname("rucksacks");
    set_short("big rucksack");
    set_pshort("big rucksacks");
    set_adj(({"large","big"}));
    set_long("This is a big rucksack. Wide adjustable strips make it " +
      "comfortable to wear on the back. " +
      "You may <fill> and <empty> the rucksack as you wish.\n");

    set_mass_storage(1); 

    set_keep(1); 

    add_prop(CONT_I_WEIGHT, 4500); 	/* grams */
    add_prop(CONT_I_MAX_WEIGHT, 150000); /* grams */
    add_prop(CONT_I_VOLUME, 8000); 	/* ml */
    add_prop(CONT_I_MAX_VOLUME, 150000); /* ml */

    add_prop(OBJ_I_VALUE, 450); 		/* Worth 450 cc */

    add_item("strips","They are adjustable to fit any stature.\n");
    add_cmd_item("strips","adjust",adjust_strips); 
}
