/*
 *  IGARD_ARM + "i_shank.c"
 *  Shank wielded by Isengard prisoners.
 *    Modified from: /d/Gondor/common/wep/orcscim.c
 *    Last modified by Alto, 11 October 2001
 *
 */

#pragma strict_types

inherit "/std/weapon.c";
inherit "/lib/keep.c";

#include "/sys/stdproperties.h"
#include "/sys/wa_types.h"
#include "/sys/formulas.h"
#include "/sys/macros.h"
#include "/d/Gondor/defs.h"
#include "../igard_defs.h"

public void
create_weapon() 
{
    set_name("shank");
    add_name("knife");
    set_pname("shanks");
    add_pname("knives");
    set_adj("crude");
    add_adj("pointed");
    set_short("crude pointed shank");
    set_pshort("crude pointed shanks");
    set_long("This knife was made from crude materials, most likely "
        + "obtained surreptitiously by a prisoner. It has a handle made "
        + "of some unknown spongy material and a single pointed spike. "
        + "While other weapons may be more refined in appearance, the "
        + "shank will poke holes in vital places with equal efficiency.\n");
    set_default_weapon(18, 12, W_KNIFE, W_SLASH | W_IMPALE, W_NONE, 0);
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_WEAPON(12, W_KNIFE) + random(101));
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 4);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(18, 12) + random(37));
}
