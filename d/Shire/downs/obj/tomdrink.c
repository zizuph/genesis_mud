/*
 * Withywindle water. This water is used by Tom Bombadill to 
 * heal himself when attacked. It's enchated water from the 
 * Withywindle river, and is based on the orc drink of the orcs 
 * from Moria. Good aligned creatures, except for mebbe gobbos, 
 * will be healed from it whereas evil cratures will be poisoned.
 * Thanks to Rogon for the original code!
 * -- Finwe, January 2001
 */

#include "defs.h"
#include <stdproperties.h>
#include <composite.h>
#include <poison_types.h>

inherit "/std/drink";

#define MANA_DROP_EVIL 200
#define HEAL_EVIL      30

#define MANA_DROP_GOOD  100
#define HEAL_GOOD       350

create_drink()
{
    set_soft_amount(330);// A small bottle containing 0.33l.
    set_name("vial");
    add_name(({"_withy_water_", "liquid", "water", "drink"}));

    add_adj(({"sparkling", "clear"}));
    set_short("vial of sparkling water");
    set_pshort("vials of sparking water");
    set_long("This is a vial of sparkling water. The water is " +
        "crystal clear and has a slight effervescent quality to " +
        "it that hint of earth and water.\n");
    add_prop(OBJ_I_VALUE,  10+random(10));
    add_prop(OBJ_M_NO_SELL,0);

}

public void 
special_effect(int num)
{
    object poison, *poisons = ({});
    string race;
    int i;

    race = TP->query_race();
// if player isn't goblin, and good aligned, and not undead, 
// then they can drink the water
    if ((race == "goblin") && 
        (TP->query_alignment() <= -150) &&
        (player->query_prop(LIVE_I_UNDEAD))
    {
	    i = -1;
	    while (++i < num)
	    {
		//   FIXEUID add by Igneous
		    FIXEUID;
		    poison = clone_object("/std/poison_effect");
		    poison -> set_interval(20);
		    poison -> set_time(500);
		    poison -> set_damage(({POISON_FATIGUE, 100, POISON_HP, 30}));
		    poison -> set_poison_type("shire_withy_water");
		    poison -> move(TP, 1);
		    poisons += ({ poison });
		    TP->add_mana(-MANA_DROP_EVIL);
	    }
	    else
	    {
		TP->add_mana(-MANA_DROP_EVIL);
		TP->heal_hp(HEAL_EVIL);
	    }
	}
	if (sizeof(poisons)) 
    {
	    write("You suddenly feel ill. You have been poisoned!\n");
	    say(QCTNAME(TP) + " breathes heavily realizing that " + 
	      HE_SHE(TP) + " has been poisoned!\n");
	    poisons -> start_poison();
	}
    }
    else
    {
	TP->add_mana(-num*MANA_DROP_GOOD);
	TP->heal_hp(num*HEAL_GOOD);
    }
}
