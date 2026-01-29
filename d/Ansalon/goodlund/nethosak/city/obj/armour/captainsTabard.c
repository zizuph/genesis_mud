inherit "/std/armour";
#include <wa_types.h>
#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>


void
create_armour()
{
    set_name("tabard");
    set_ac(20);
    set_at(A_ROBE);
    set_am( ({ 5, 5, 5 }) );
    set_adj("silver-blue");
    add_adj("imperial");
    set_short("imperial silver-blue tabard");
    set_pshort("imperial silver-blue tabards");
    set_long("This is one of the imperial tabards found "+
             "only in the city of Nethosak, and worn by "+
             "the imperial guards there. This tabard has "+
             "a large sign of a clenched fist on the back. "+
             "The tabard has been dyed blue, and the "+
             "different layers of wool has been sewed "+
             "together, making it look like a very formal "+
             "piece of equipment. Thin silver threads have "+
             "been weaved into the wool giving the impression "+
             "that his tabard is quite unique, worn "+
             "by a captain or perhaps even a minotaur Lord.\n");

   add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1);
   add_prop(MAGIC_AM_MAGIC, ({20, "enchantment"}));
   add_prop(MAGIC_AM_ID_INFO,
      ({"The armour is enchanted.\n", 5,
	"Centuries ago, a high priest enchanted this "+
        "tabard so that it can protect the wearer "+
        "against some of the blows from weapons, the "+
        "enchantment also decreases the general weight "+
        "of the armour, making it very light.\n", 50}));
    add_prop(OBJ_I_WEIGHT, 1000);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(20));
}


