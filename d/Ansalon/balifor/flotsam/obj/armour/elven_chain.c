/* Modified 26-Sep-97 by Ashlar because the extra skill levels were not
   compatible with other skill-enhancing objects */

/* Navarre April 5th 2010, updated weight to 7kg as per AoB's request. */

inherit "/std/armour";
inherit "/lib/keep";
#include <stdproperties.h>
#include <wa_types.h>
#include <ss_types.h>
#include <formulas.h>
#include <macros.h>
#include "/d/Ansalon/common/defs.h"

#define ARMOUR_CLASS 47

object wearer;

void
create_armour()
{
    set_name("chainmail");
    set_adj("chain");
    add_adj("elven");

    set_short("elven chainmail");
    set_pshort("elven chainmails");
    set_long("This suit of chainmail is made of the finest " +
      "quality steel by an elven armourer. It looks like it " +
      "is well-kept, and also is surprisingly light.\n");

    set_ac(ARMOUR_CLASS);
    set_at(A_BODY);
    set_af(TO);

    add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1);
    add_prop(MAGIC_AM_ID_INFO,
      ({"As elves see magic differently to humans, this " +
	"item does not radiate a great deal of magic, thus hard " +
	"to detect. Still, this armours subtilities do not fool " +
	"you, and you notice that this armours magic comes from " +
	"its forging by a skilled elven armourer. Its very nature " +
	"makes sneaking and hiding easier while wearing it.\n",70}));
    add_prop(MAGIC_AM_MAGIC,({10,"enchantment"}));
    add_prop(OBJ_I_WEIGHT, 7000);
    add_prop(OBJ_I_VOLUME, 2500);
    add_prop(OBJ_I_VALUE,F_VALUE_ARMOUR(ARMOUR_CLASS));
}

mixed
wear(object what)
{
    TP->set_skill_extra(SS_SNEAK, TP->query_skill_extra(SS_SNEAK) + 8);
    TP->set_skill_extra(SS_HIDE, TP->query_skill_extra(SS_HIDE) + 8);

    wearer = TP;
    return 0;
}
mixed
remove(object what)
{
    wearer->set_skill_extra(SS_SNEAK, TP->query_skill_extra(SS_SNEAK) -8);
    wearer->set_skill_extra(SS_HIDE, TP->query_skill_extra(SS_HIDE) -8);

    wearer = 0;
    return 0;
}
