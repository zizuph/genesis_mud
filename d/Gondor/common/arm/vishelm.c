/*
 *	/d/Gondor/common/arm/vishelm.c
 *
 *	The Helm of the Hawk.
 *
 *	Advanced magical helmet for use in Genesis
 *	by Xeros of GondorMud 22 Nov 1993
 *      Minor bugfix with the extra skill 2002
 *
 *  Fixed MAGIC_AM_ID_INFO a bit to be a more of 
 *  a telling of properties, not a list.
 *             Toby, 30 Jan 2007
 *  Updated OBJ_S_WIZINFO. Anyone can wear the helm regardless of alignment
 *  - Finwe, December 2018
 */
#pragma strict_types
inherit "/std/armour.c";
inherit "/lib/keep.c";

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <wa_types.h>

#include "/d/Gondor/defs.h"

int added_skill;

void
create_armour()
{
    set_name("helmet");
    set_pname("helmets");
    add_pname("helms");
    add_name("helm");
    set_adj("great");
    set_short("great helm of the hawk");
    set_long("Formed of a midnight black metal, this "+short()+" has a "+
        "visor crafted of a clear, pale blue material permanently fused "+
        "to the metal sides just in front of the ear guards. The metal is "+ 
        "engraved and sculpted to look much like feathers, and the visor "+ 
        "is pointed, covering the top half of the face, giving the helmet "+
        "the appearance of being a hawk's head.\n");
    set_ac(32);
    set_am(({1,1-2}));
    set_at(A_HEAD | A_NECK);
    set_af(TO);
    add_prop(OBJ_I_VOLUME,350);
    add_prop(OBJ_I_WEIGHT,2500+random(1000));
    add_prop(OBJ_I_VALUE,500+random(200));
    add_prop(OBJ_I_IS_MAGIC_ARMOUR,1);
    add_prop(MAGIC_AM_MAGIC,({70,"enchantment"}));
    add_prop(MAGIC_AM_ID_INFO,({
        "The "+short()+" radiates a strong aura of enchantment. ",1,
        "It provides good protection from light-based magical attacks. ",20,
        "The magic of the helm will work only if the wearer follows the " +
            "paths of the gods of westernesse. ", 40,
        "Furthermore it enhances the wearer's awareness, and allows for " +
            "night-vision. ",60,
        "\n",1}) );
    add_prop(MAGIC_I_RES_LIGHT, 75);
    add_prop(OBJ_S_WIZINFO,"This helmet increases a wearer's awareness by 10 "
      + "+ 1/5 of the wearer's current skill level. It also adds "
      + "LIVE_I_SEE_DARK by a power of 1. "
      + "The helm is part of the heirlooms "
      + "of the House of Hurin and players who solve the quest to retrieve "
      + "the Battle Standard of the Witchking can get it once.\n");
}

public mixed
wear(object arm)
{
    object  tp = TP;

    added_skill = -1;

    added_skill = (10 + ((tp->query_skill(SS_AWARENESS))/5));
    if ((tp->query_skill(SS_AWARENESS) + added_skill) > 100)
    {
        added_skill = (100 - (tp->query_skill(SS_AWARENESS)));
    }
    tp->set_skill_extra(SS_AWARENESS,(tp->query_skill_extra(SS_AWARENESS) + added_skill));
    tp->add_prop(LIVE_I_SEE_DARK, tp->query_prop(LIVE_I_SEE_DARK) + 1);

    tp->add_magic_effect(TO);

    WRITE("You slide the "+short()+" over your head and neck. The world comes "+
        "into sharper focus as you look through the visor.\n");
    SAY(" pulls the "+short()+" over "+POSSESSIVE(tp)+" head.");      
    return 1;
}

public mixed
remove(object arm)
{
    object  tp = query_worn();

    if (added_skill < 0)
        return 0;

    if (!living(tp))
        return 0;

    tp->set_skill_extra(SS_AWARENESS, (tp->query_skill_extra(SS_AWARENESS) - added_skill));
    tp->add_prop(LIVE_I_SEE_DARK, tp->query_prop(LIVE_I_SEE_DARK) - 1);
    tp->remove_magic_effect(TO);
    WRITE("You tug the "+short()+" off your head. The world seems a little "+
    "bit fuzzier now.\n");
    SAY(" tugs the "+short()+" off "+POSSESSIVE(tp)+" head.");
    return 1;
}

mixed
query_magic_protection(string prop, object who = previous_object())
{
    if (who == query_worn())
    {
        if (prop == MAGIC_I_RES_LIGHT)
            return ({ 40, 1 });
    }

    return ::query_magic_protection(prop, who);
}

