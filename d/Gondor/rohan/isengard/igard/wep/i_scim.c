/*
 *  IGARD_ARM + "i_scim.c"
 *  Standard Isengard Club
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
    set_name("scimitar");
    add_name("sword");
    set_pname("scimitars");
    add_pname("swords");
    set_adj("serrated");
    add_adj("iron");
    set_short("serrated iron scimitar");
    set_pshort("serrated iron scimitars");
    set_long("From the marks on its hilt, this scimitar was forged in the "
        + "smithies of Isengard. It has a rusted blade with a saw-toothed "
        + "edge, designed to shred internal organs as it passes through.\n");
    add_item(({"hilt", "mark", "marks"}), "The hilt on the serrated iron "
        + "scimitar bears the mark of the White Hand of Isengard.\n");
    set_default_weapon(18, 12, W_SWORD, W_SLASH | W_IMPALE, W_NONE, 0);
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_WEAPON(12, W_SWORD) + random(101));
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 4);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(18, 12) + random(37));
}
