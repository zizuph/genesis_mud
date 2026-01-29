
inherit "/std/weapon";
inherit "/lib/keep";
#include "/sys/stdproperties.h"
#include "/sys/wa_types.h"
#include "/sys/formulas.h"
#include "/sys/macros.h"
#include <ss_types.h>
#include <filter_funs.h>
#include "/d/Ansalon/common/defs.h"

#define WEAPON_HIT 45
#define WEAPON_PEN 50


void
create_weapon()
{
    set_name("battleaxe");
    add_name("axe");
    add_adj("ancient");
    add_adj("dwarven");
    set_short("ancient dwarven battleaxe");
    set_long("This dwarven battleaxe is a large one-" +
        "handed axe of an ancient design not seen since " +
        "the mystical days of the Age of Dreams. Runes " +
        "heavily decorate the head of this axe, and a feeling " +
        "of power radiates strongly from them.\n");
    set_hit(WEAPON_HIT);
    set_pen(WEAPON_PEN);
    set_wt(W_AXE);
    set_dt(W_SLASH);
    set_hands(W_ANYH);
    add_prop(OBJ_M_NO_SELL,"The shopkeeper cannot afford to buy " +
      "the magical weapon. You will have to keep hold of it.\n");
    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
    add_prop(MAGIC_AM_MAGIC,({70,"enchantment"}));
    add_prop(MAGIC_AM_ID_INFO, ({"This battleaxe was forged long " +
      "ago by dwarven smiths and blessed by priests of Reorx under " +
      "the glow of his red star during the Age of Dreams. As far as " +
      "weapons go, this one is extremely heavily enchanted, with the " +
      "ability to hit and do damage well beyond even the finest forged " +
      "weapons. Many heroes have carried this axe, the latest of which " +
      "was the dwarven hero Teregul Skybolt of the hill dwarves.\n", 50}));

    add_prop(OBJ_I_WEIGHT, 16000);
    add_prop(OBJ_I_VOLUME, 4000);
    add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(WEAPON_HIT,WEAPON_PEN));

}

