inherit "/std/weapon";
inherit "/lib/keep";

#include <ss_types.h>
#include <wa_types.h>
#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>
#include "/d/Ansalon/common/defs.h"

#define HIT 45
#define PEN 50

void
create_weapon()
{
    set_name("soulsplitter");
    add_name("axe");
    add_adj("double-bladed");
    add_adj("flawless");
    set_short("flawless double-bladed axe");
    set_long("This is a simply made axe with a black iron haft approximately " +
        "four feet in length and wrapped in leather, capped with a massive " +
        "double-bladed axe head of rare star metal that shines with a golden " +
        "light. It is unmarred by scratches, dents, or even dust. Symbols " +
        "have been carved along the haft.\n");

    add_item(({"ancient symbols","symbols"}), "@@read_runes");
    add_cmd_item(({"ancient symbols","symbols"}), "read", "@@read_runes2");

    set_hit(HIT);
    set_pen(PEN);
    set_wt(W_AXE);
    set_hands(W_RIGHT);
    set_dt(W_SLASH);

   set_likely_dull(1);
   set_likely_break(1);
   set_likely_corr(1);

    set_wf(TO);
    add_prop(OBJ_M_NO_BUY, 1);
    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
    add_prop(MAGIC_AM_ID_INFO,
      ({"This axe is 'Soulsplitter', forged by the centaur chieftain Peldarin " +
        "thousands of years ago from the metal of a fallen star.\n", 5,
	"The axe is incredibly powerful, being able to cut through armour as if " +
        "it wasn't even there, and could cleave through a huge stone in a single " +
        "blow.\n", 25, 
        "This weapon dulls incredibly slowly, and glows still with the " +
        "celestial fires of the shooting star it was made from.\n", 55 }));
    add_prop(MAGIC_AM_MAGIC,({40,"enchantment"}));
    add_prop(OBJ_S_WIZINFO, "This axe is a right-handed 45/50 weapon that glows " +
        "with a +2 light value. It is wielded by a hobgoblin boss with a clone " +
        "unique of 10 (/d/Ansalon/silvanesti/new_kurinost/living/razogh.c). " +
        "It wears considerably slower than normal weapons.\n");
    add_prop(OBJ_I_VOLUME, 5200);
    add_prop(OBJ_I_WEIGHT, 7000);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(45,50) + 500 + random(500)); 
    add_prop(OBJ_I_LIGHT,LIGHT_PASSIVE_RARE);
}


int
read_runes2()
{
    if(TP->query_skill(SS_LANGUAGE) < 40)
    {
	write("The symbols seem to be centaur in nature and are beyond your " +
            "understanding. You are unable to work out what they mean.\n");
	return 1;
    }
    write("The symbols were used thousands of years ago and are centaur in nature. " +
        "They translate to mean 'Soulsplitter'.\n");
    return 1;
}

string
read_runes()
{
    if(TP->query_skill(SS_LANGUAGE) < 40)
    {
	return "The symbols seem to be centaur in nature and are beyond your " +
            "understanding. You are unable to work out what they mean.\n";
    }
    return "The symbols were used thousands of years ago and are centaur in nature. " +
        "They translate to mean 'Soulsplitter'.\n";
}


void
wield_message(object wielder)
{
    wielder->catch_tell("The haft of your " +short()+ " feels unusually warm " +
        "in your hand as you grip it.\n");

}

mixed
wield(object what)
{
    set_alarm(1.0, 0.0, &wield_message(TP));
    return 0;
}

int
set_dull(int du)
{
    if (!random(3))
    {
        return 1;
    }

    return 0;
}
