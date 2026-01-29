inherit "/std/armour";
#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>
#include <ss_types.h>
#include "/d/Ansalon/common/defs.h"

inherit "/lib/keep";

#define ARMOUR_CLASS 1

void
create_armour()
{
    set_name("gloves");
    set_pname("gloves");
    set_adj("black");
    add_adj("leather");
    set_short("pair of black leather gloves");
    set_pshort("pairs of black leather gloves");
    set_long("This is a pair of fine gloves of very thin and supple " +
      "leather.\n");
    add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1);
    add_prop(MAGIC_AM_ID_INFO,
      ({"This pair of gloves is no different from any other normal pair of " +
	"gloves except in the hands of a thief. These gloves have been enchanted " +
	"to improve the thieves skills that involve his hands, namely pick pockets, " +
	"picking of locks, removing of traps and backstabbing.\n",50}));
    add_prop(MAGIC_AM_MAGIC,({25,"enchantment"}));

    set_ac(ARMOUR_CLASS);
    set_at(A_HANDS);
    set_af(TO);

    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 80);
    add_prop(OBJ_I_VALUE,F_VALUE_ARMOUR(ARMOUR_CLASS) + 1000);
}

mixed
wear(object what)
{
    TP->set_skill_extra(SS_OPEN_LOCK, (TP->query_skill_extra(SS_OPEN_LOCK) + 
        10));  /*Open locks +10 to skill */
    TP->set_skill_extra(SS_PICK_POCKET, 
        (TP->query_skill_extra(SS_PICK_POCKET) + 10));   /*Pick pockets +10 */
    TP->set_skill_extra(SS_FR_TRAP, 
        (TP->query_skill_extra(SS_FR_TRAP) + 10)); /*Find-remove traps +10 */
    TP->set_skill_extra(SS_BACKSTAB, 
        (TP->query_skill_extra(SS_BACKSTAB) + 5)); /*Backstab + 5*/
    return 0;
}

mixed
remove(object what)
{
    TP->set_skill_extra(SS_OPEN_LOCK, 
        (TP->query_skill_extra(SS_OPEN_LOCK) - 10));
    TP->set_skill_extra(SS_PICK_POCKET,
        (TP->query_skill_extra(SS_PICK_POCKET) - 10));
    TP->set_skill_extra(SS_FR_TRAP,
        (TP->query_skill_extra(SS_FR_TRAP) - 10));
    TP->set_skill_extra(SS_BACKSTAB,
        (TP->query_skill_extra(SS_BACKSTAB) - 5));
    return 0;
}
