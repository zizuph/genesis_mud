/*
 *      /d/Gondor/common/arm/nazgul_helm.c
 *
 *      The helm of the nazgul.
 *
 *      Fixed magic resistance.
 *      Olorin, 1-Dec-1995
 */
#pragma strict_types
inherit "/std/armour.c";

#include <formulas.h>
#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>

#include "/d/Gondor/defs.h"

void
create_armour()
{
    set_name(({"helm", "helmet" }));
    set_pname("helms");
    add_pname("helmets");
    set_short("black plate helm");
    set_pshort("black plate helms");
    set_adj(({"plate", "black", }));
    set_long(BSN("This is a helm of strange shape: It is high-crowned, "
      + "with long cheek-guards close-fitting to the face of the "
      + "wearer. The black helm is made of the scales of a Sea-drake's "
      + "skin."));
    set_default_armour(60, A_HEAD, ({ 0, 0, 0, 0}), TO);
    add_prop(OBJ_I_WEIGHT, 2900);
    add_prop(OBJ_I_VOLUME,  680);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(60) + random(500) + 500);
    add_prop(OBJ_M_NO_BUY, 1);
    add_prop(MAGIC_I_RES_MAGIC,  80);
    add_prop(MAGIC_I_RES_LIFE,   50);
    add_prop(MAGIC_I_RES_WATER, 100);
    add_prop(MAGIC_AM_MAGIC,(({60, "abjuration"})));
    add_prop(MAGIC_AM_ID_INFO,({
    BSN("This helm is treated with magic to give better protection "+
      "of your head, even against magic!"), 10,
    BSN("The powerful magic in this helm will protect you against the element of life!"),50,
    BSN("The helm helps the wearer to resist magic calling on the power of water."),70 }));
    add_prop(OBJ_S_WIZINFO, "The helm of the nazgul (/d/Gondor/common/npc/blackrider).\n"
      + "Magical protection for MAGIC, LIFE, WATER.\n");
}

public mixed
wear(object obj)
{
    object  tp = ENV(TO);

    if (!living(tp))
        return 0;

    if (tp->query_alignment() > 0)
    {
        tp->add_mana(-200);
        tp->add_panic(50);
        return "When you try to wear the "+short()+" you feel as if a bolt "
          + "of lightning hit your head.\n"
          + "You cannot wear the "+short()+".\n";
    }

    tp->add_magic_effect(TO);
    return 0;
}

public mixed
remove(object obj)
{
    object  tp = TO->query_worn();

    if (!living(tp))
        return 0;

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
        case MAGIC_I_RES_MAGIC: return ({ 25, 1});
        case MAGIC_I_RES_LIFE:  return ({ 20, 1});
        case MAGIC_I_RES_WATER: return ({ 20, 1});
        }
    }
    return ::query_magic_protection(prop, for_what);
}

