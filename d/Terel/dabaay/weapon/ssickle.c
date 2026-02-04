/*
 *  ssickle.c
 *
 *  A sickle-shaped dagger
 *
 *  Goldberry January, 2000
 *  
 * Revisions:
 *     Lilith Feb 2022: made a spell enhancer.
 */

#include "/d/Terel/include/Terel.h"
inherit STDWEAPON;
inherit "/d/Genesis/specials/new/lib/spell_enhancer";
#include <macros.h>
#include <wa_types.h>
#include <formulas.h>

void
create_weapon()
{
    set_name(({"dagger"}));
    add_name("sickle-shaped dagger");
    set_adj("sickle-shaped");
    set_short("sickle-shaped dagger");
    set_pshort("sickle-shaped daggers");
    set_long("A finely-crafted dagger with a sickle-shaped blade.\n");

    set_magic_spellpower(35);
    set_default_weapon(25,35,W_KNIFE,W_SLASH|W_IMPALE,W_ANYH,TO);
    add_prop(OBJ_I_VOLUME,query_prop(OBJ_I_WEIGHT)/5);
    add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(24,31)-random(25));
    add_prop(MAGIC_AM_MAGIC, ({ 40, "enchantment" }));
    add_prop(MAGIC_AM_ID_INFO,
        ({"The "+short()+" is exceptionally sharp.\n",20}));
    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);

}

