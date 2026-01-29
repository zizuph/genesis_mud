#pragma strict_types;

inherit "/std/weapon";
inherit "/lib/keep";
inherit "/d/Genesis/specials/new/lib/spell_enhancer";

#include <wa_types.h>
#include "/sys/global/cmdparse.c"
#include "/sys/ss_types.h"
#include <stdproperties.h>
#include <macros.h>
#include <formulas.h>
#include <filter_funs.h>

void
create_weapon()
{
    set_name("hoopak");
    set_adj("kender");
    add_name("staff"); 
    set_short("kender hoopak (acrobatic)");
    set_pshort("kender hoopaks  (acrobatic)");
    set_long("Test Hoopak");
    set_default_weapon(40,40,W_POLEARM, W_BLUDGEON | W_IMPALE, W_ANYH);

    // This value will affect spell damage for spellcasters.
    set_magic_spellpower(40);

    add_prop(OBJ_I_AIDS_ACROBATIC, 100);
    add_prop(OBJ_I_VOLUME, 250);
    add_prop(OBJ_I_WEIGHT, 500);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(20,9) + random(40)); 
}

void 
appraise_object(int num)
{
    ::appraise_object(num);
    write(item_spellpower_desc());
}

string 
stat_object() 
{
    return ::stat_object() + stat_object_spellpower();
}
