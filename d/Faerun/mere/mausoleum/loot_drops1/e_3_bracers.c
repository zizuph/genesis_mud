/*  /d/Ravenloft/droptables/fos_drops/e_fos_bracers.c
 *
 *  Epic armouritem. Drops from monsters in the
 *  Forest of Shadows.
 *
 *  This is an armour set-piece of a particulary suit
 *  of armour.
 *
 *  Nerull, 2015
 *
 */

inherit "/std/armour";
#include "../defs.h";
#include "/d/Ravenloft/defs/magicalitems_stats.h"
#include <stdproperties.h>
#include <macros.h>
#include <wa_types.h>

void
create_armour()
{
    set_name("bracers");
    set_adj("shadowy");
    add_adj("steel");

	set_short("shadowy steel bracers");
	set_pshort("shadowy steel bracers");

    set_long("After examining the bracers you "
	+"see that these bracers are not any thing common from "
	+"these parts. They hail from far darker areas. They are "
	+"spiked and a small bright blue line runs down the center "
	+"of the bracers. Wearing them requires no straps, as the "
	+"bracers simply slides on and sits. They are light and "
	+"cold to touch.\n");
	
	add_item(({ "line", "small line", "bright line", "small blue line", 
	"blue line", "bright blue line",}), "A small bright blue line runs "
	+"down the center of the bracers. It shimmers slightly and is rather "
	+"difficult to focus on.\n");
	
	add_item(({ "spikes", "seven spikes", "spike"}), "Small spikes line "
	+"the bracers at various intervals. They make this armour not only "
	+"protective but likely rather painful to someone striking it as well.\n");

	set_default_armour(FOS_E_FOS_BRACERS_AC, A_ARMS, 0, this_object());

	add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1);

	add_prop(MAGIC_AM_MAGIC, ({ 40, "enchantment" }));

	add_prop(MAGIC_AM_ID_INFO, ({ "This armour is enchanted to give "
		+ "better protection.\n",1, }));

	add_prop(OBJ_S_WIZINFO, "This is an Epic armour dropping from monsters in "
		+ "the Forest of Shadows, Ravenloft. "
		+ "It is enchanted to offer better ac.\n");

    add_prop(OBJ_I_VALUE, FOS_E_FOS_BRACERS_VALUE);
	add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(FOS_E_FOS_BRACERS_AC, A_ARMS));
	add_prop(OBJ_I_VOLUME, FOS_E_FOS_BRACERS_VOLUME);
}


