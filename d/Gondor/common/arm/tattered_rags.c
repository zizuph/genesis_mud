/*  Magic cloak coded by Arren, July 94 */
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
    set_name("cloak");
    add_name("rags");
    set_pname("cloaks");
    set_adj("tattered");
    add_adj(({ "dirty", "filthy" }));
    set_short("tattered rags");
    set_pshort("tattered rags");
    set_long(BSN(
        "The tattered rags were once richly embroidered, but are now "
      + "only in some shreds that somehow keep from falling apart. "
      + "What is left of the embroidery tells that the pattern must "
      + "have been intricate, some golden and silver threads bear "
      + "witness to the care by which it was done."));

    set_default_armour(3, A_ROBE, ({ 0, 0, 0 }), TO);

    add_prop(MAGIC_AM_MAGIC,({ 12, "abjuration" }));
    add_prop(MAGIC_AM_ID_INFO,({ 
    "The tattered rags seems to be magical.\n",1,
    "The tattered rags will protect you from magical fire.\n",17 }));
    add_prop(OBJ_S_WIZINFO, BSN(
    "The tattered rags will give MAGIC_I_RES_FIRE, 10. "+
    "to the wearer. "+
    "It is worn by the /d/Gondor/common/npc/barrow_wight.c."));
    add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1);
    add_prop(MAGIC_I_RES_FIRE, 50);

    add_prop(OBJ_I_WEIGHT,F_WEIGHT_DEFAULT_ARMOUR(3, A_ROBE));
    add_prop(OBJ_I_VOLUME, 400);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(3) + random(50));
}

public mixed
wear(object obj)
{
    object  tp = ENV(TO);

    if ((tp != TP) || (TO != obj))
        return -1;

    if (living(tp))
        tp->add_magic_effect(TO);
    return 0;
}

public mixed
remove(object obj)
{
    object  tp = TO->query_worn();

    if ((tp != TP) || (TO != obj))
        return -1;

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

