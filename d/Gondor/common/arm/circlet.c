/*  Armour coded by Arren, July 94 */
#pragma strict_types
inherit "/std/armour";

#include <formulas.h>
#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>
#include "/d/Gondor/defs.h"

void
create_armour()
{
    set_name(({"circlet", "crown", }));
    set_pname("circlets");
    add_pname("crowns");
    set_adj(({"silver", "amber", }));
    set_short("silver circlet");
    set_pshort("silver circlets");
    set_long("A circlet of interlaced silver with an amber stone set "+
    "into it. The amber has been smoothly polished. You can feel the "+
    "care and skill that went into making it.\n");

    set_default_armour(7, A_HEAD, ({ -1, 2, -1}), TO);

    add_prop(MAGIC_AM_MAGIC,({ 14, "abjuration" }));
    add_prop(MAGIC_AM_ID_INFO,({
    "The silver circlet seems to be magical.\n",1,
    "The silver circlet will protect you from magical fire.\n",17 }));
    add_prop(OBJ_S_WIZINFO, 
    "The silver circle will give MAGIC_I_RES_FIRE, 10. "+
    "to the wearer. "+
    "It is worn by the /d/Gondor/common/npc/barrow_wight.c.\n");
    add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1);

    add_prop(MAGIC_I_RES_FIRE, 40);
    add_prop(OBJ_I_WEIGHT,F_WEIGHT_DEFAULT_ARMOUR(9, A_HEAD) + 250);
    add_prop(OBJ_I_VOLUME, 200);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(18) + random(50));
}

public mixed
wear(object obj)
{
    object  tp = ENV(TO);

    if (living(tp))
        tp->add_magic_effect(TO);
    return 0;
}

public mixed
remove(object obj)
{
    object  tp = TO->query_worn();

    if (living(tp))
        tp->remove_magic_effect(TO);
    return 0;
}

mixed
query_magic_protection(string prop, object for_what = previous_object())
{
    object  tp = TO->query_worn();

    if (for_what == tp)
    {
        switch (prop)
        {
        case MAGIC_I_RES_FIRE:  return ({ 10, 1});
        }
    }
    return ::query_magic_protection(prop, for_what);
}

