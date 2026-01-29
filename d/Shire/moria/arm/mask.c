/*
 * Durin's phoenix mask. A helm shaped like a phoenix. It makes the wearer
 * more percievable towards invisible things, but it lowers the players
 * Dexterity a slight tad.
 */

inherit "/std/armour";

#include "/d/Shire/common/defs.h"
#include <formulas.h>
#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>

object wearer;

create_armour()
{
	set_name("mask");
	add_name("helm");
	set_pname("masks");
	add_pname("helms");
	set_adj("phoenix");
	set_short("phoenix mask");
	set_pshort("phoenix masks");
	set_long("This mask, or helm has the the shape of a phoenix, a "+
		"semi-mythical creature. It belongs to one of the dwarven "+
		"kings in the line of Durin, and used to be stored in the Great "+
		"Armoury of Moria, in the seventh deep. It is made of Mithril, "+
		"like most Royal Dwarvish armour is.\n");
	set_ac(40);
	set_at(A_HEAD);
	set_am(({ 2, 1, -1}));
	set_af(TO);

	add_prop(OBJ_I_WEIGHT, 1345 + random (500));
	add_prop(OBJ_I_VALUE, (12*12*12*3 + random(300) - random(400)));
	add_prop(OBJ_I_VOLUME, 700);
	add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1);
	add_prop(MAGIC_AM_MAGIC, ({20, "enchantment" }));
    add_prop(MAGIC_AM_ID_INFO,
    ({	"The mask seems to be magically enchanted.\n",3,
        "The mask makes the wearer able to percieve invisible "+
	  "objects and living.\n",30
    }));
}

wear(object to)
{
    wearer = TP;
    wearer->add_prop(LIVE_I_SEE_INVIS, 1);
}

remove(object to)
{
    wearer = TP;
    wearer->remove_prop(LIVE_I_SEE_INVIS);
    wearer = 0;
}

int
query_recover()
{
    return 0;
}
