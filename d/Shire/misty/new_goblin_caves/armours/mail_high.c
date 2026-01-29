#pragma save_binary

inherit "/std/armour";

#include <wa_types.h>
#include <formulas.h>
#include "/d/Shire/sys/defs.h"

#define ARMOUR_CLASS 33+random(5)

void
create_armour()
{
    set_name("mail");
    add_name("platemail");

    set_adj("steel");
    set_adj("black");

    set_short("black steel platemail");
    set_pshort("black steel platemails");

    set_long("This mail, used by a goblin, is of very good quality. "+
      "It is doubtful that it was made by goblins. "+
      "Probably they have it taken it from some unfortunate adventurer.\n");

    set_ac(ARMOUR_CLASS);
    set_at(A_BODY);
    set_am( ({ 2, 2, -4 }) );

    add_prop(OBJ_I_WEIGHT, 10000);
    add_prop(OBJ_I_VOLUME, 4000);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(ARMOUR_CLASS) + random(201) - 100);
}

string
query_recover()
{
    return MASTER + ":" + query_arm_recover();
}

void
init_recover(string arg)
{
    init_arm_recover(arg);
}
