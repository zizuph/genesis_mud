/* Kitiara's lost glove. One of the spell components
	for the sabre quest. */
/* Created by Macker 04/11/95 */
inherit "/std/armour.c";
#include "/d/Krynn/common/defs.h"
#include <macros.h>
#include "/sys/wa_types.h";


create_armour() {
        add_adj("blue");
        add_adj("leather");
        set_name("glove");
	add_name("sabre_quest_ob4");
	add_name("sabre_quest_item");
        set_pname("gloves");
        set_long("This is the lost blue leather glove of Dragon Highlord " +
                "Kitiara. You sure wish you could wield a blade " +
                "the way the hand which was once in this glove did. Perhaps " +
                "some of the skill will rub off on you. Too bad it doesn't fit.\n");
	set_ac(0);
	set_at(A_L_HAND);
	set_af(TO);
	set_likely_break(0);
        add_prop(OBJ_I_VOLUME, 1000);
        add_prop(OBJ_I_WEIGHT, 1000);
}


mixed
wear()
{
	write("The " + query_short() + " doesn't fit.\n");
	say(QCTNAME(TP) + " tries to wear a " + query_short() +
		" but it doesn't fit " + OBJECTIVE(TP) + ".\n");
	return -1;
}
	        



