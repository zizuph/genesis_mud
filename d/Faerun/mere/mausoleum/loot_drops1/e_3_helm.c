/*  /d/Ravenloft/droptables/fos_drops/e_fos_helm.c
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
    set_name("helm");
    set_adj("shadowy");
    add_adj("steel");

	set_short("shadowy steel helm");
	set_pshort("shadowy steel helms");

    set_long("After examining the helm, you see its actually "
	+"quite a mastercraft. The front of the helmet is almost "
	+"closed completely. Only a thin bright blue line goes "
	+"across its facemask. The sides are padded with iron "
	+"pieces, ribboned together to make scales. On each scale there "
	+"is a little symbol of a snoflake. The helmet shines in a "
	+"blackish unnatural color.\n");
	
	add_item(({ "line", "small line", "bright line", "small blue line", 
	"blue line", "bright blue line",}), "A small bright blue line runs "
	+"down the center of the facemask. It shimmers slightly and is rather "
	+"difficult to focus on.\n");
	
	add_item(({ "scale", "scales", "iron", "pieces", "iron pieces",
	"padded iron", "ribbons", "iron ribbons","snowflakes", "snowflake"}), 
	"Iron pieces are ribboned together created the illusion of scales from "
	+"an ancient predatory beast. Upon each of the scales is emblazoned a "
	+"small snowflake. The snowflake shimmers with a faint blue light and "
	+"seems to represent something that is lost.\n");

	set_default_armour(FOS_E_FOS_HELM_AC, A_HEAD, 0, this_object());

	add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1);

	add_prop(MAGIC_AM_MAGIC, ({ 40, "enchantment" }));

	add_prop(MAGIC_AM_ID_INFO, ({ "This armour is enchanted to give "
		+ "better protection.\n",1, }));

	add_prop(OBJ_S_WIZINFO, "This is an Epic armour dropping from monsters in "
		+ "the Forest of Shadows, Ravenloft. "
		+ "It is enchanted to offer better ac.\n");

    add_prop(OBJ_I_VALUE, FOS_E_FOS_HELM_VALUE);
	add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(FOS_E_FOS_HELM_AC, A_HEAD));
	add_prop(OBJ_I_VOLUME, FOS_E_FOS_HELM_VOLUME);
}


