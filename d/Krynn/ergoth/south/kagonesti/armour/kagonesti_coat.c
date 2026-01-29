#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>

inherit "/std/armour";

#define FIRST_ADJ	({ "decorated", "fringed", "painted", "feathered" })
#define SECOND_ADJ	({ "leather", "elk-skin", "Kagonesti", "bear-skin", \
                    "hardened"})
#define KAG_SYMBOLS	({ "brown feather", "green and gold tree", \
        			"blue phoenix", "silver flute" })
#define KAG_LOC		({ "right breast", "left breast", "waist", "back" })



void create_armour()
{
    int ac;
    string first = one_of_list(FIRST_ADJ),
           second = one_of_list(SECOND_ADJ);
    
    set_name("coat");
    set_adj(({first, second}));
    set_short(first + " " + second + " coat");
    set_long("This is a Kagonesti coat, used for protection in battle and "
	+ "the wilderness. It is made from a tanned animal hide and "
	+ "skillfully hardened to increase protection without completely "
	+ "sacrificing dexterity. It is decorated with fringe, symbols, and "
	+ "feathers.\n");
    add_item("fringe", "The fringe on the coat is made from wooden beads that"
	+ " have been stringed to form colorful patterns. The Kagonesti "
	+ "believe they ward off evil spirits.\n");
    add_item("symbols", "The coat is decorated with several symbols. There is"
	+ " a large " + one_of_list(KAG_SYMBOLS) + " painted on the "
	+ one_of_list(KAG_LOC)	+ " of the coat.\n");
    add_item("feathers", "The coat has several feathers sewn in at strategic "
        + "locations. Kagonesti lore holds that features bestow good "
	+ "fortune.\n");    

    ac = random(10);
    set_ac(6 + ac);
    set_at(A_BODY);
    set_am(({0, 1, -1}));
    add_prop(OBJ_I_VOLUME, 8000);
    add_prop(OBJ_I_WEIGHT, ac*225);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(ac));
}
