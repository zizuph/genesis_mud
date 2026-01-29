inherit "/std/armour";
inherit "/lib/keep";
#include <stdproperties.h>
#include <wa_types.h>
#include <ss_types.h>
#include <formulas.h>
#include <macros.h>
#include "/d/Ansalon/common/defs.h"

#define ARMOUR_CLASS 38

void
create_armour()
{
    set_name("mail");
    add_name("serpent-mail");
    add_adj("serpent");

    set_short("serpent-mail");
    set_pshort("serpent-mails");
    set_long("This suit of mail is made of the scales from " +
      "a great sea-serpent by sea-elf armourers. It is " +
      "extremely light however offers good protection.\n");

    set_ac(ARMOUR_CLASS);
    set_at(A_BODY);

    add_prop(OBJ_I_WEIGHT, 1500);
    add_prop(OBJ_I_VOLUME, 2500);
    add_prop(OBJ_I_VALUE,F_VALUE_ARMOUR(ARMOUR_CLASS));
}
