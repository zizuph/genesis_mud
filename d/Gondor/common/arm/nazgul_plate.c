/*
 *      /d/Gondor/common/arm/nazgul_plate.c
 *      
 *      The platemail of the nazgul.
 *
 *      Fixed magic resistance.
 *      Olorin, 1-dec-1995
 *
 *      Fixed weight and wizinfor on resistances.
 *      Toby, 13-feb-2007
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
    set_name(({"platemail", "mail", "plate", }));
    set_pname("platemails");
    add_pname("mails");
    add_pname("plates");
    set_adj(({"black", "plate", }));
    set_short("black platemail");
    set_pshort("black platemails");
    set_long("The black platemail is made from the skin of a Sea-drake!\n");
    set_default_armour(60, A_BODY, 0, TO);
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(60, A_BODY) );
    add_prop(OBJ_I_VOLUME, 2500);
    add_prop(OBJ_M_NO_BUY,1);
    add_prop(OBJ_I_VALUE,F_VALUE_ARMOUR(60) + random(500) + 500);
    add_prop(MAGIC_I_RES_MAGIC,  50);
    add_prop(MAGIC_I_RES_FIRE,  100);
    add_prop(MAGIC_AM_MAGIC,({75,"abjuration"}));
    add_prop(MAGIC_AM_ID_INFO,({
      "This plate armour is magically crafted from the skin of a Sea-drake!\n", 10,
      "It will protect the wearer against fiery magic.\n",75, }));
    add_prop(OBJ_S_WIZINFO,
        "The platemail of the nazgul /d/Gondor/common/npc/blackrider.\n"
      + "Magical resistance MAGIC  50, additive,\n"
      + "                   FIRE  100, additive.\n");
    
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
          + "of lightning hit your body.\n"
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
        case MAGIC_I_RES_MAGIC: return ({ 20, 1});
        case MAGIC_I_RES_FIRE:  return ({ 20, 1});
        }
    }
    return ::query_magic_protection(prop, for_what);
}

