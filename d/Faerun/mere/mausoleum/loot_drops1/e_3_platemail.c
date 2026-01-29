/*  /d/Ravenloft/droptables/fos_drops/e_fos_platemail.c
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
    set_name("platemail");
    set_adj("shadowy");
    add_adj("steel");

	set_short("shadowy steel platemail");
	set_pshort("shadowy steel platemail");

    set_long("After examining the platemail you notice it's "
	+"not just a regular platemail. The front is curved "
	+"slightly to deflect blows. In the center of the platemail "
	+"a bright blut thin line runs down, from top to bottom. The "
	+"side and back pieces are all in a unnatural blackish color. The "
	+"inside is laced with a strange fabric, that is cold to the"
	+"touch. Looking at this armour almost hyptnozises "
	+"you. Strange dark dreams begin to appear in your "
	+"mind...\n");
	
	add_item(({ "line", "small line", "bright line", "small blue line", 
	"blue line", "bright blue line",}), "A small bright blue line runs "
	+"down the center of the platemail. It shimmers slightly and is rather "
	+"difficult to focus on.\n");
	
	add_item(({"fabric", "strange fabric", "lace", "laced fabric"}),"An "
	+"odd looking fabric lines the inside of this armour. It radiates "
	+"cold and is slightly painful to touch. It has no colour, at least "
	+"none that can be described, and it seems to shift and fold in upon "
	+"itself.\n");
	
	add_item(({"back piece", "side piece", "pieces", "side pieces",
	"back pieces", "unnatural blackish color","blackish color",
	"black color"}),"The side and back pieces of this platemail are a "
	+"different color than the rest of it. The black seems as though it "
	+"has been corrupted or changed, it is wholly unnatural and out of "
	+"place.\n");

	set_default_armour(FOS_E_FOS_PLATEMAIL_AC, A_BODY, 0, this_object());

	add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1);

	add_prop(MAGIC_AM_MAGIC, ({ 40, "enchantment" }));

	add_prop(MAGIC_AM_ID_INFO, ({ "This armour is enchanted to give "
		+ "better protection.\n",1, }));

	add_prop(OBJ_S_WIZINFO, "This is an Epic armour dropping from monsters in "
		+ "the Forest of Shadows, Ravenloft. "
		+ "It is enchanted to offer better ac.\n");

    add_prop(OBJ_I_VALUE, FOS_E_FOS_PLATEMAIL_VALUE);
	add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(FOS_E_FOS_PLATEMAIL_AC, A_BODY));
	add_prop(OBJ_I_VOLUME, FOS_E_FOS_PLATEMAIL_VOLUME);
}


